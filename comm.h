#pragma once
#define WIN32_LEAN_AND_MEAN

/*-------Windows-------*/
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <thread>
#include <vector>
#include <array>
#include <mutex>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <codecvt>
#include <algorithm>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <urlmon.h>
#include <mmsystem.h>


#include <psapi.h>
#include <winternl.h>

enum request_code : int
{
    read,
    write,
    base,
    pattern_scan,
    running
};

typedef struct kernel_request
{
    ULONG64 process_id;
    ULONG64 source_process_id;

    PVOID image_base;
    LPCSTR pattern;
    LPCSTR mask;
    bool should_rva;

    ULONG64 target_address;
    ULONG64 source_address;
    ULONG64 size;

    const char* module_name;

    void* output;

    request_code code;

}kernel_request, * pkernel_request;

class Driver
{
public:


    void* function_address = nullptr;
    __int64(__fastcall* function)(__int64, unsigned int);

    DWORD pid;

    bool driver_init()
    {
        LoadLibraryA(("user32.dll"));
        LoadLibraryA(("win32u.dll"));

        function_address = GetProcAddress(GetModuleHandleA(("win32u.dll")), ("NtMITPostThreadEventMessage")); //NtUserFunctionalizeDisplayConfig
        if (!function_address)
        {
            return false;
        }

        *(PVOID*)&function = function_address;
        return true;
    }

    DWORD GetProcessID(LPCWSTR process_name)
    {
        HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        DWORD process_id = NULL;

        if (handle == INVALID_HANDLE_VALUE)
            return process_id;

        PROCESSENTRY32W entry = { 0 };
        entry.dwSize = sizeof(PROCESSENTRY32W);

        if (Process32FirstW(handle, &entry)) {
            if (!_wcsicmp(process_name, entry.szExeFile))
            {
                process_id = entry.th32ProcessID;
            }
            else while (Process32NextW(handle, &entry))
            {
                if (!_wcsicmp(process_name, entry.szExeFile))
                {
                    process_id = entry.th32ProcessID;
                }
            }
        }
        CloseHandle(handle);
        return process_id;
    }

    ULONG64 GetBaseAddress(LPCSTR module_name)
    {
        if (module_name && pid)
        {
            kernel_request request = {};

            request.process_id = pid;
            request.module_name = module_name;
            request.code = request_code::base;

            function((__int64)&request, 0);
            return reinterpret_cast<ULONG64>(request.output);
        }
        return 0;
    }


    std::uintptr_t get_module(const wchar_t* name)
    {
        // Open the process with the specified process ID
        const auto handle = OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid);

        // Initialize variables for the memory scanning loop
        auto current = 0ull;
        auto mbi = MEMORY_BASIC_INFORMATION();

        // Loop through memory regions of the process
        while (VirtualQueryEx(handle, reinterpret_cast<void*>(current), &mbi, sizeof(MEMORY_BASIC_INFORMATION)))
        {
            // Check if the memory region is mapped or is an image
            if (mbi.Type == MEM_MAPPED || mbi.Type == MEM_IMAGE)
            {
                // Allocate a buffer to store the module name
                const auto buffer = malloc(1024);
                auto bytes = std::size_t();

                // Get the handle to the ntdll.dll module
                const static auto ntdll = GetModuleHandle("ntdll");

                // Get the address of the NtQueryVirtualMemory function
                const static auto nt_query_virtual_memory_fn =
                    reinterpret_cast<NTSTATUS(__stdcall*)(HANDLE, void*, std::int32_t, void*, std::size_t, std::size_t*)> (
                        GetProcAddress(ntdll, "NtQueryVirtualMemory"));




                // Call the NtQueryVirtualMemory function to get the module name
                if (nt_query_virtual_memory_fn(handle, mbi.BaseAddress, 2, buffer, 1024, &bytes) != 0 ||
                    !wcsstr(static_cast<UNICODE_STRING*>(buffer)->Buffer, name) ||
                    wcsstr(static_cast<UNICODE_STRING*>(buffer)->Buffer, L".mui"))
                {
                    // Free the buffer and continue to the next memory region
                    free(buffer);
                    goto skip;
                }

                // Free the buffer and close the handle to the process
                free(buffer);
                CloseHandle(handle);

                // Return the base address of the module
                return reinterpret_cast<std::uintptr_t>(mbi.BaseAddress);
            }

            // Go to the next memory region
        skip:
            current = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        }

        // Close the handle to the process and return 0 (module not found)
        CloseHandle(handle);
        return 0ull;
    }

    template<typename t> bool write(ULONG64 address, t value)
    {
        kernel_request request;

        request.code = request_code::write;
        request.process_id = pid;
        request.source_process_id = GetCurrentProcessId();
        request.source_address = (ULONG64)&value;
        request.target_address = address;
        request.size = sizeof(value);

        function((__int64)&request, 0);

        return true;
    }

    template<typename t> t readptr(ULONG64 address)
    {
        if (address)
        {
            kernel_request request;

            t buffer = {};

            request.code = request_code::read;
            request.process_id = pid;
            request.source_process_id = GetCurrentProcessId();
            request.source_address = address;
            request.target_address = (ULONG64)&buffer;
            request.size = sizeof(t);

            function((__int64)&request, 0);

            return buffer;
        }
        return t();
    }

    bool readEx(ULONG64 read_address, ULONG64 target_address, ULONG64 size)
    {
        kernel_request request;

        request.code = request_code::read;
        request.process_id = pid;
        request.source_process_id = GetCurrentProcessId();
        request.source_address = read_address;
        request.target_address = target_address;
        request.size = size;

        function((__int64)&request, 0);

        return true;
    }

    bool running()
    {
        kernel_request request;

        request.code = request_code::running;
        function((__int64)&request, 0);

        if ((int)request.output == 0x200)
        {
            return true;
        }

        return false;
    }


    std::string GetUnicodeString(uint64_t address, uint64_t string_length)
    {
        char16_t wcharTemp[64] = {};

        readEx((ULONG64)address, (ULONG64)&wcharTemp, string_length);
        std::string u8_conv = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(wcharTemp);

        return u8_conv;
    }

}driver;