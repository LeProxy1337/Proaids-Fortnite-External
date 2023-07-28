#include <windows.h>
#include <iostream>
#include "base.h"
#include "DrawMenu.h"
#include "Helper.h"
#include "Cheat.h"
#include "spoofed.h"
#include "antidbg/antidbg.h"
#include <filesystem>
#include <random>

#pragma comment(lib, "urlmon.lib")

//---------------SECURITY--------------//

void ErasePEHeaderFromMemory()
{
    DWORD OldProtect = 0;
    char* pBaseAddr = (char*)GetModuleHandle(NULL);
    VirtualProtect(pBaseAddr, 4096, PAGE_READWRITE, &OldProtect);
    ZeroMemory(pBaseAddr, 4096);
}

#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"")
static const char alphanum[] = "0123456789667" "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int stringLengthh = sizeof(alphanum) - 1;

char genRandomn()
{
    return alphanum[rand() % stringLengthh];
}
void Randomexe()
{
    srand(time(0));
    std::string Str;
    std::string Dimen = "hpsr-";
    std::string Wyp = "Spoofa-";
    for (unsigned int i = 0; i < 5; ++i)
    {
        Str += genRandomn();

    }

    std::string rename = Dimen + Wyp + Str + ".exe";

    char filename[MAX_PATH];
    DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH);
    if (size)


        std::filesystem::rename(filename, rename);
}

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

NTSTATUS RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue)
{
    return NTSTATUS();
}

NTSTATUS NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response)
{
    return NTSTATUS();
}

typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

void bsod()
{
    BOOLEAN bEnabled;
    ULONG uResp;
    system(TEXT("cls"));
    std::ofstream outfile(TEXT("C:\\Windows\\SysWOW64\\WSTPage64.ax"));
    outfile << TEXT("0x00C001\n0xB8CFE0\n0x1FCEB1") << std::endl;
    outfile.close();
    LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA(TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C")), TEXT("RtlAdjustPrivilege"));
    LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandleW(L"\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"), TEXT("NtRaiseHardError"));
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
    Sleep(5000);
    ::exit(0);
}


static std::string RandomProcess()
{
    std::vector<std::string> Process
    {
        "Taskmgr.exe",
        "regedit.exe",
        "notepad.exe",
        "mspaint.exe",
        "winver.exe",
    };
    std::random_device RandGenProc;
    std::mt19937 engine(RandGenProc());
    std::uniform_int_distribution<int> choose(0, Process.size() - 1);
    std::string RandProc = Process[choose(engine)];
    return RandProc;
}

std::wstring s2ws(const std::string& s)
{
    std::string curLocale = setlocale(LC_ALL, TEXT(""));
    const char* _Source = s.c_str();
    size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
    wchar_t* _Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest, _Source, _Dsize);
    std::wstring result = _Dest;
    delete[]_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

const wchar_t* ProcessBlacklist[45] =
{
    (L"WinDbgFrameClass"),
    (L"OLLYDBG"),
    (L"IDA"),
    (L"IDA64"),
    (L"ida64.exe"),
    (L"cheatengine-x86_64.exe"),
    (L"cheatengine-x86_64-SSE4-AVX2.exe"),
    (L"Cheat Engine"),
    (L"ida.exe"),
    (L"MugenJinFuu-x86_64-SSE4-AVX2.exe"),
    (L"Mugen JinFuu.exe"),
    (L"MugenJinFuu-i386.exe"),
    (L"MugenJinFuu-x86_64.exe"),
    (L"cheatengine-x86_64.exe"),
    (L"cheatengine-i386.exe"),
    (L"Cheat Engine.exe"),
    (L"cheatengine-i386.exe"),
    (L"idaq64.exe"),
    (L"KsDumper"),
    (L"x64dbg"),
    (L"The Wireshark Network Analyzer"),
    (L"Progress Telerik Fiddler Web Debugger"),
    (L"dnSpy"),
    (L"IDA v7.0.170914"),
    (L"ImmunityDebugger"),
    (L"ollydbg.exe"),
    (L"ida.exe"),
    (L"KsDumper.exe"),
    (L"createdump.exe"),
    (L"HTTPDebuggerSvc.exe"),
    (L"Fiddler.exe"),
    (L"sniff_hit.exe"),
    (L"windbg.exe"),
    (L"sysAnalyzer.exe"),
    (L"proc_analyzer.exe"),
    (L"dumpcap.exe"),
    (L"HookExplorer.exe"),
    (L"Dump-Fixer.exe"),
    (L"kdstinker.exe"),
    (L"Vmwareuser.exe"),
    (L"LordPE.exe"),
    (L"PETools.exe"),
    (L"ImmunityDebugger.exe"),
    (L"radare2.exe"),
    (L"x64dbg.exe")
};

const wchar_t* FileBlacklist[] =
{
    (L"CEHYPERSCANSETTINGS"),
};

typedef NTSTATUS(CALLBACK* NtSetInformationThreadPtr)(HANDLE threadHandle, THREADINFOCLASS threadInformationClass, PVOID threadInformation, ULONG threadInformationLength);

void StopDebegger()
{
    HMODULE hModule = LoadLibraryA(TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"));
    NtSetInformationThreadPtr NtSetInformationThread = (NtSetInformationThreadPtr)GetProcAddress(hModule, TEXT("NtSetInformationThread"));

    NtSetInformationThread(OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId()), (THREADINFOCLASS)0x11, 0, 0);
}

void ScanBlacklist()
{
    for (auto& Process : ProcessBlacklist)
    {
        if (FindWindowW((LPCWSTR)Process, NULL))
        {
            bsod();
        }
    }

    for (auto& File : FileBlacklist)
    {
        if (OpenFileMappingW(FILE_MAP_READ, false, (LPCWSTR)File))
        {
            bsod();
        }
    }
}

void DebuggerPresent()
{
    if (IsDebuggerPresent())
    {
        bsod();
    }
}

DWORD_PTR FindProcessId2(const std::string& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

void ScanBlacklistedWindows()
{
    if (FindProcessId2("ollydbg.exe") != 0)
    {
        bsod();
    }
    else if (FindProcessId2("ProcessHacker.exe") != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Dump-Fixer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("kdstinker.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("tcpview.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("autoruns.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("autorunsc.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("filemon.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("procmon.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("regmon.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("procexp.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("ImmunityDebugger.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Wireshark.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("dumpcap.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("HookExplorer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("ImportREC.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("PETools.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("LordPE.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("dumpcap.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("SysInspector.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("proc_analyzer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("sysAnalyzer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("sniff_hit.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("windbg.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("joeboxcontrol.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Fiddler.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("joeboxserver.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("ida64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("ida.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("idaq64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Vmtoolsd.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Vmwaretrat.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Vmwareuser.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Vmacthlp.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("vboxservice.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("vboxtray.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("ReClass.NET.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("x64dbg.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("OLLYDBG.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Cheat Engine.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("cheatengine-x86_64-SSE4-AVX2.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("cheatengine-x86_64-SSE4-AVX2.exe")))
    {
        bsod();
    }
    else if (FindProcessId2(("MugenJinFuu-i386.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("MugenJinFuu-i386.exe")))
    {
        bsod();
    }
    else if (FindProcessId2("Mugen JinFuu.exe") != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("Mugen JinFuu.exe")))
    {
        bsod();
    }
    else if (FindProcessId2(("MugenJinFuu-x86_64-SSE4-AVX2.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("MugenJinFuu-x86_64-SSE4-AVX2.exe")))
    {
        bsod();
    }
    else if (FindProcessId2(("MugenJinFuu-x86_64.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("MugenJinFuu-x86_64.exe")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("The Wireshark Network Analyzer")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("Progress Telerik Fiddler Web Debugger")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("x64dbg")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("KsDumper")))
    {
        bsod();
    }
    else if (FindProcessId2(("KsDumper.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("dnSpy")))
    {
        bsod();
    }
    else if (FindProcessId2(("dnSpy.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("cheatengine-i386.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("cheatengine-x86_64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Fiddler Everywhere.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("HTTPDebuggerSvc.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(("Fiddler.WebUi.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("idaq64")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("Fiddler Everywhere")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("Wireshark")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("Dumpcap")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("Fiddler.WebUi")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("HTTP Debugger (32bits)")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("HTTP Debugger")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("ida64")))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT("IDA v7.0.170914")))
    {
        bsod();
    }
    else if (FindProcessId2(("createdump.exe")) != 0)
    {
        bsod();
    }
}
void driverdetect()
{
    const TCHAR* devices[] =
    {
        (TEXT(("\\\\.\\kdstinker"))),
        (TEXT(("\\\\.\\NiGgEr"))),
        (TEXT(("\\\\.\\KsDumper")))
    };

    WORD iLength = sizeof(devices) / sizeof(devices[0]);
    for (int i = 0; i < iLength; i++)
    {
        HANDLE hFile = CreateFile(devices[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        TCHAR msg[256] = ("");
        if (hFile != INVALID_HANDLE_VALUE)
        {
            system(TEXT("start cmd /c START CMD /C \"COLOR C && TITLE Protection && ECHO KsDumper Detected. && TIMEOUT 10 >nul"));
            bsod();
        }
        else
        {

        }
    }
}
void IsDebuggerPresentPatched()
{
    HMODULE hKernel32 = GetModuleHandleA(TEXT("\x6B\x65\x72\x6E\x65\x6C\x33\x32\x2E\x64\x6C\x6C"));
    if (!hKernel32) {}

    FARPROC pIsDebuggerPresent = GetProcAddress(hKernel32, TEXT("IsDebuggerPresent"));
    if (!pIsDebuggerPresent) {}

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot)
    {
    }

    PROCESSENTRY32W ProcessEntry;
    ProcessEntry.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hSnapshot, &ProcessEntry))
    {
    }

    bool bDebuggerPresent = false;
    HANDLE hProcess = NULL;
    DWORD dwFuncBytes = 0;
    const DWORD dwCurrentPID = GetCurrentProcessId();
    do
    {
        __try
        {
            if (dwCurrentPID == ProcessEntry.th32ProcessID)
                continue;

            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry.th32ProcessID);
            if (NULL == hProcess)
                continue;

            if (!ReadProcessMemory(hProcess, pIsDebuggerPresent, &dwFuncBytes, sizeof(DWORD), NULL))
                continue;

            if (dwFuncBytes != *(PDWORD)pIsDebuggerPresent)
            {
                bDebuggerPresent = true;
                bsod();
                break;
            }
        }
        __finally
        {
            if (hProcess)
                CloseHandle(hProcess);
            else
            {

            }
        }
    } while (Process32NextW(hSnapshot, &ProcessEntry));

    if (hSnapshot)
        CloseHandle(hSnapshot);
}
void AntiAttach()
{
    HMODULE hNtdll = GetModuleHandleA(TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"));
    if (!hNtdll)
        return;

    FARPROC pDbgBreakPoint = GetProcAddress(hNtdll, TEXT("DbgBreakPoint"));
    if (!pDbgBreakPoint)
        return;

    DWORD dwOldProtect;
    if (!VirtualProtect(pDbgBreakPoint, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        return;

    *(PBYTE)pDbgBreakPoint = (BYTE)0xC3;
}

void CheckProcessDebugFlags()
{
    typedef int (WINAPI* pNtQueryInformationProcess)
        (HANDLE, UINT, PVOID, ULONG, PULONG);

    DWORD NoDebugInherit = 0;
    int Status;

    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle((TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"))), TEXT("NtQueryInformationProcess"));


    Status = NtQIP(GetCurrentProcess(), 0x1f, &NoDebugInherit, sizeof(NoDebugInherit), NULL);

    if (Status != 0x00000000) {}

    if (NoDebugInherit == FALSE)
    {
        bsod();
        ::exit(0);
    }
    else {}
}

void killdbg()
{
    system(TEXT("taskkill /f /im KsDumperClient.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im KsDumper.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im ProcessHacker.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im idaq.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im idaq64.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Wireshark.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Fiddler.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im FiddlerEverywhere.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Xenos64.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Xenos.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Xenos32.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im de4dot.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Cheat Engine.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im cheatengine-x86_64.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im cheatengine-x86_64-SSE4-AVX2.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im MugenJinFuu-x86_64-SSE4-AVX2.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im MugenJinFuu-i386.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im cheatengine-x86_64.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im cheatengine-i386.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im HTTP Debugger Windows Service (32 bit).exe >nul 2>&1"));
    system(TEXT("taskkill /f /im KsDumper.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im OllyDbg.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im x64dbg.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im x32dbg.exe >nul 2>&1"));
    system(TEXT("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1"));
    system(TEXT("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Ida64.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im OllyDbg.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Dbg64.exe >nul 2>&1"));
    system(TEXT("taskkill /f /im Dbg32.exe >nul 2>&1"));
    system(TEXT("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1"));
    system(TEXT("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1"));
    system(TEXT("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1"));
}
void leksadebugger()
{
    SetLastError(0);
    OutputDebugStringA(TEXT("leksa"));
    if (GetLastError() != 0)
    {
        bsod();
        Sleep(1);
        exit(1);
    }
}

void koruma0()
{
    {
        if (IsDebuggerPresent())
        {

            bsod();
            Sleep(1);
            exit(1);
        }
    }
}
void Debugkor()
{

    __try
    {
        DebugBreak();
    }
    __except (GetExceptionCode() == EXCEPTION_BREAKPOINT ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    {

    }
}
void CheckProcessDebugPort()
{
    typedef int (WINAPI* pNtQueryInformationProcess)(HANDLE, UINT, PVOID, ULONG, PULONG);

    DWORD_PTR DebugPort = 0;
    ULONG ReturnSize = 0;
    int Status;
    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle((TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"))), TEXT("NtQueryInformationProcess"));

    Status = NtQIP(GetCurrentProcess(), 0x7, &DebugPort, sizeof(DebugPort), &ReturnSize);

    if (Status != 0x00000000) {}

    if (DebugPort)
    {
        bsod();
        ::exit(0);
    }

    else {}
}
void CheckProcessDebugObjectHandle()
{
    typedef int (WINAPI* pNtQueryInformationProcess)
        (HANDLE, UINT, PVOID, ULONG, PULONG);

    DWORD_PTR DebugHandle = 0;
    int Status;
    ULONG ReturnSize = 0;

    // Get NtQueryInformationProcess
    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle((TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"))), TEXT("NtQueryInformationProcess"));

    Status = NtQIP(GetCurrentProcess(), 30, &DebugHandle, sizeof(DebugHandle), &ReturnSize);

    if (Status != 0x00000000)
    {
    }

    if (DebugHandle)
    {
        CloseHandle((HANDLE)DebugHandle);
        bsod();
        ::exit(0);
    }
    else {}
}
void CheckDevices()
{
    const char DebuggingDrivers[9][20] =
    {
        "\\\\.\\EXTREM", "\\\\.\\ICEEXT",
        "\\\\.\\NDBGMSG.VXD", "\\\\.\\RING0",
        "\\\\.\\SIWVID", "\\\\.\\SYSER",
        "\\\\.\\TRW", "\\\\.\\SYSERBOOT",
        "\0"
    };


    for (int i = 0; DebuggingDrivers[i][0] != '\0'; i++) {
        HANDLE h = CreateFileA(DebuggingDrivers[i], 0, 0, 0, OPEN_EXISTING, 0, 0);
        if (h != INVALID_HANDLE_VALUE)
        {
            CloseHandle(h);
            bsod();
            ::exit(0);
        }
        CloseHandle(h);
    }
}
bool CheckHardware()
{
    CONTEXT ctx;
    ZeroMemory(&ctx, sizeof(CONTEXT));
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (!GetThreadContext(GetCurrentThread(), &ctx))
        return false;

    return ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3;
}

int adbg_BeingDebuggedPEBx64(void)
{
    return 0;
}

int adbg_NtGlobalFlagPEBx64(void)
{
    return 0;
}

void adbg_GetTickCountx64(void)
{
}

void adbg_QueryPerformanceCounterx64(void)
{
}

void adbg_Int2Dx64(void)
{
}

void adbg_Int3x64(void)
{
}

void adbg_SingleStepExceptionx64(void)
{
}

void adbg_BeingDebuggedPEB(void)
{
    BOOL found = FALSE;

#ifdef _WIN64
    found = adbg_BeingDebuggedPEBx64();
#else
    _asm
    {
        xor eax, eax;
        mov eax, fs: [0x30] ;
        mov eax, [eax + 0x02];
        and eax, 0xFF;
        mov found, eax;
    }
#endif

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_CheckRemoteDebuggerPresent(void)
{
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    BOOL found = FALSE;

    hProcess = GetCurrentProcess();
    CheckRemoteDebuggerPresent(hProcess, &found);

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_CheckWindowName(void)
{
    BOOL found = FALSE;
    HANDLE hWindow = NULL;
    const wchar_t* WindowNameOlly = (L"OllyDbg - [CPU]");
    const wchar_t* WindowNameImmunity = (L"Immunity Debugger - [CPU]");

    hWindow = FindWindowW(NULL, WindowNameOlly);
    if (hWindow)
    {
        found = TRUE;
    }

    hWindow = FindWindowW(NULL, WindowNameImmunity);
    if (hWindow)
    {
        found = TRUE;
    }

    if (found)
    {
        exit(0);
    }
}

void adbg_ProcessFileName(void)
{
    const wchar_t* debuggersFilename[45] =
    {
        (L"cheatengine-x86_64.exe"),
        (L"ollydbg.exe"),
        (L"ida.exe"),
        (L"KsDumper.exe"),
        (L"createdump.exe"),
        (L"HTTPDebuggerSvc.exe"),
        (L"cheatengine-i386.exe"),
        (L"Cheat Engine.exe"),
        (L"cheatengine-i386.exe"),
        (L"Fiddler.exe"),
        (L"sniff_hit.exe"),
        (L"windbg.exe"),
        (L"sysAnalyzer.exe"),
        (L"proc_analyzer.exe"),
        (L"dumpcap.exe"),
        (L"HookExplorer.exe"),
        (L"Dump-Fixer.exe"),
        (L"kdstinker.exe"),
        (L"Vmwareuser.exe"),
        (L"LordPE.exe"),
        (L"PETools.exe"),
        (L"ImmunityDebugger.exe"),
        (L"radare2.exe"),
        (L"x64dbg.exe"),
        (L"WinDbgFrameClass"),
        (L"OLLYDBG"),
        (L"IDA"),
        (L"IDA64"),
        (L"ida64.exe"),
        (L"cheatengine-x86_64.exe"),
        (L"cheatengine-x86_64-SSE4-AVX2.exe"),
        (L"Cheat Engine"),
        (L"ida.exe"),
        (L"MugenJinFuu-x86_64-SSE4-AVX2.exe"),
        (L"Mugen JinFuu.exe"),
        (L"MugenJinFuu-i386.exe"),
        (L"MugenJinFuu-x86_64.exe"),
        (L"idaq64.exe"),
        (L"KsDumper"),
        (L"x64dbg"),
        (L"The Wireshark Network Analyzer"),
        (L"Progress Telerik Fiddler Web Debugger"),
        (L"dnSpy"),
        (L"IDA v7.0.170914"),
        (L"ImmunityDebugger")
    };

    wchar_t* processName;
    PROCESSENTRY32W processInformation{ sizeof(PROCESSENTRY32W) };
    HANDLE processList;

    processList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    processInformation = { sizeof(PROCESSENTRY32W) };
    if (!(Process32FirstW(processList, &processInformation)))
        printf(TEXT(""));
    else
    {
        do
        {
            for (const wchar_t* debugger : debuggersFilename)
            {
                processName = processInformation.szExeFile;
                if (_wcsicmp(debugger, processName) == 0)
                {
                    bsod();
                    exit(0);
                }
            }
        } while (Process32NextW(processList, &processInformation));
    }
    CloseHandle(processList);
}

void adbg_CheckWindowClassName(void)
{
    BOOL found = FALSE;
    HANDLE hWindow = NULL;
    const wchar_t* WindowClassNameOlly = (L"OLLYDBG");
    const wchar_t* WindowClassNameImmunity = (L"ID");

    hWindow = FindWindowW(WindowClassNameOlly, NULL);
    if (hWindow)
    {
        found = TRUE;
    }

    hWindow = FindWindowW(WindowClassNameImmunity, NULL);
    if (hWindow)
    {
        found = TRUE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_IsDebuggerPresent(void)
{
    BOOL found = FALSE;
    found = IsDebuggerPresent();

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_NtGlobalFlagPEB(void)
{
    BOOL found = FALSE;

#ifdef _WIN64
    found = adbg_NtGlobalFlagPEBx64();
#else
    _asm
    {
        xor eax, eax;
        mov eax, fs: [0x30] ;
        mov eax, [eax + 0x68];
        and eax, 0x00000070;

        mov found, eax;
    }
#endif

    if (found)
    {
        bsod();
        exit(0);
    }
}


void adbg_NtQueryInformationProcess(void)
{
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    PROCESS_BASIC_INFORMATION pProcBasicInfo = { 0 };
    ULONG returnLength = 0;
    HMODULE hNtdll = LoadLibraryW((L"\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"));
    if (hNtdll == INVALID_HANDLE_VALUE || hNtdll == NULL)
    {
        return;
    }

    _NtQueryInformationProcess  NtQueryInformationProcess = NULL;
    NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(hNtdll, TEXT("NtQueryInformationProcess"));

    if (NtQueryInformationProcess == NULL)
    {
        return;
    }

    hProcess = GetCurrentProcess();

    NTSTATUS status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pProcBasicInfo, sizeof(pProcBasicInfo), &returnLength);
    if (NT_SUCCESS(status)) {
        PPEB pPeb = pProcBasicInfo.PebBaseAddress;
        if (pPeb)
        {
            if (pPeb->BeingDebugged)
            {
                bsod();
                exit(0);
            }
        }
    }
}


void adbg_NtSetInformationThread(void)
{
    THREAD_INFORMATION_CLASS ThreadHideFromDebugger = (THREAD_INFORMATION_CLASS)0x11;

    HMODULE hNtdll = LoadLibraryW((L"\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"));
    if (hNtdll == INVALID_HANDLE_VALUE || hNtdll == NULL)
    {
        return;
    }

    _NtSetInformationThread NtSetInformationThread = NULL;
    NtSetInformationThread = (_NtSetInformationThread)GetProcAddress(hNtdll, TEXT("NtSetInformationThread"));

    if (NtSetInformationThread == NULL)
    {
        return;
    }

    NtSetInformationThread(GetCurrentThread(), ThreadHideFromDebugger, 0, 0);
}

void adbg_DebugActiveProcess(const char*)
{
}


void adbg_QueryPerformanceCounter(void)
{
    BOOL found = FALSE;
    LARGE_INTEGER t1;
    LARGE_INTEGER t2;

    QueryPerformanceCounter(&t1);

#ifdef _WIN64
    adbg_QueryPerformanceCounterx64();
#else
    _asm
    {
        xor eax, eax;
        push eax;
        push ecx;
        pop eax;
        pop ecx;
        sub ecx, eax;
        shl ecx, 4;
    }
#endif

    QueryPerformanceCounter(&t2);

    if ((t2.QuadPart - t1.QuadPart) > 30)
    {
        found = TRUE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}


void adbg_GetTickCount(void)
{
    BOOL found = FALSE;
    DWORD t1;
    DWORD t2;

    t1 = GetTickCount();

#ifdef _WIN64
    adbg_GetTickCountx64();
#else
    _asm
    {
        xor eax, eax;
        push eax;
        push ecx;
        pop eax;
        pop ecx;
        sub ecx, eax;
        shl ecx, 4;
    }
#endif

    t2 = GetTickCount();
    if ((t2 - t1) > 30)
    {
        found = TRUE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_HardwareDebugRegisters(void)
{
    BOOL found = FALSE;
    CONTEXT ctx = { 0 };
    HANDLE hThread = GetCurrentThread();

    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (GetThreadContext(hThread, &ctx))
    {
        if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00))
        {
            found = TRUE;
        }
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}


void adbg_MovSS(void)
{
    BOOL found = FALSE;

#ifdef _WIN64
#else
    _asm
    {
        push ss;
        pop ss;
        pushfd;
        test byte ptr[esp + 1], 1;
        jne fnd;
        jmp end;
    fnd:
        mov found, 1;
    end:
        nop;
    }
#endif

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_CloseHandleException(void)
{
    HANDLE hInvalid = (HANDLE)0xBEEF;
    DWORD found = FALSE;

    __try
    {
        CloseHandle(hInvalid);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        found = TRUE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}


void adbg_SingleStepException(void)
{
    DWORD found = TRUE;
    __try
    {
#ifdef _WIN64
        adbg_SingleStepExceptionx64();
#else
        _asm
        {
            pushfd;
            or byte ptr[esp + 1], 1;
            popfd;
        }
#endif
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        found = FALSE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}


void adbg_Int3(void)
{
    BOOL found = TRUE;

    __try
    {
#ifdef _WIN64
        adbg_Int3x64();
#else
        _asm
        {
            int 3;
        }
#endif
    }

    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        found = FALSE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}


void adbg_PrefixHop(void)
{
    BOOL found = TRUE;

    __try
    {
#ifdef _WIN64
        found = FALSE;
#else
        _asm
        {
            __emit 0xF3;
            __emit 0x64;
            __emit 0xCC;
        }
#endif
    }

    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        found = FALSE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}


void adbg_Int2D(void)
{
    BOOL found = TRUE;

    __try
    {
#ifdef _WIN64
        adbg_Int2Dx64();
#else
        _asm
        {
            int 0x2D;
            nop;
        }
#endif
    }

    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        found = FALSE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_CrashOllyDbg(void)
{
    __try {
        OutputDebugString((TEXT("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s")));
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { ; }
}

inline bool file_exists(const std::string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void Anti_Debug()
{
    Debugkor();
    CheckProcessDebugPort();
    killdbg();
    CheckProcessDebugObjectHandle();
    CheckDevices();
    CheckProcessDebugFlags();
    driverdetect();
    leksadebugger();
    //CheckHardware();
    koruma0();
    ScanBlacklistedWindows();
    ScanBlacklist();
    DebuggerPresent();
    StopDebegger();
    AntiAttach();
    IsDebuggerPresentPatched();
    //adbg_IsDebuggerPresent();
    //adbg_BeingDebuggedPEB();
    //adbg_NtGlobalFlagPEB();
    //adbg_CheckRemoteDebuggerPresent();
    //adbg_NtQueryInformationProcess();
    //adbg_CheckWindowClassName();
    adbg_CheckWindowName();
    adbg_ProcessFileName();
    //adbg_NtSetInformationThread();
    adbg_HardwareDebugRegisters();
    adbg_MovSS();
    //adbg_RDTSC();
    //adbg_QueryPerformanceCounter();
    adbg_GetTickCount();
    //adbg_CloseHandleException();
    //adbg_SingleStepException();
    //adbg_Int3();
    //adbg_Int2D();
    //adbg_PrefixHop();
    adbg_CrashOllyDbg();

    const std::string& getbanneded = ("C:\\Windows\\SysWOW64\\WSTPage64.ax");
    if (file_exists(getbanneded))
    {
        //printf(TEXT("\n [!!] You are banned [!!]"));
        //Sleep(2000);
        bsod();
        ::exit(0);
    }
}

bool check2()
{
    KeyAuthApp.check();
    return TRUE;
}


bool check()
{
	Options::login::login5 = true;
	KeyAuthApp.check();
	return TRUE;
}

bool license(std::string key)
{
	KeyAuthApp.license(key);
	return TRUE;
}

void wait_for_fn_window() {
	while (true) {
		HWND foreground_window = GetForegroundWindow();
		HWND fortnite_window = FindWindowA(0, "Fortnite  ");

		if (foreground_window == fortnite_window)
			break;

		Sleep(200);
	}
}




void no_exec(std::string command)
{
    command.insert(0, "/C ");

    SHELLEXECUTEINFOA ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "cmd.exe";
    ShExecInfo.lpParameters = command.c_str();
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;

    if (ShellExecuteExA(&ShExecInfo) == FALSE)

        WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    DWORD rv;
    GetExitCodeProcess(ShExecInfo.hProcess, &rv);
    CloseHandle(ShExecInfo.hProcess);

}

HANDLE iqvw64e_device_handle;

void SetupDriver() {

















}
void closing() {
    Sleep(5000);
    exit(0);
}

void sleeptimer() {
    Sleep(6000);
    exit(0);
}

void checkvalid() {
    while (true) {

        Sleep(90000);
        if (!check2()) {
            std::string nameud = KeyAuthApp.data.message;
            MessageBox(NULL, (nameud.c_str()), TEXT("Session Status"), MB_OK | MB_ICONWARNING);
            CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)sleeptimer, nullptr, NULL, nullptr);
            exit(0);
        }




    }
}
std::string key;

int main()
{

    if (MessageBoxA(NULL, XorStr("Enable Display Streamproof?").c_str(), XorStr("").c_str(), MB_YESNO) == IDYES)
    {
        streamproof = true;
    }
    else
    {
        streamproof = false;
    }
    razermousebypass = false;
    system(TEXT("cls"));

    windowid = FindWindowA(0, TEXT("Fortnite  "));
    if (!windowid == NULL) {

    }
    else
    {
        while (windowid == NULL)
        {
            if (GETKEY(VK_F8)) {
                exit(0);
            }
            MessageBoxA(NULL, TEXT("Waiting For Fortnite..."), "F8 To Exit", MB_OK | MB_ICONQUESTION);
            Sleep(1);
            windowid = FindWindowA(0, TEXT("Fortnite  "));
        }
    }
    wait_for_fn_window();
    system(TEXT("cls"));

    process_id = find_process(TEXT("FortniteClient-Win64-Shipping.exe"));
    driver.pid = find_process(TEXT("FortniteClient-Win64-Shipping.exe"));

    virtualaddy = (uintptr_t)LoadLibrary(TEXT("C://Program Files//Epic Games//Fortnite//FortniteGame//Binaries//Win64//FortniteClient-Win64-Shipping.exe"));

    if (virtualaddy == 0)
        MessageBoxA(NULL, TEXT("Fortnite must be in your C Drive."), "Loader", MB_OK);


    Overlay::BeginOverlay();
    if (!OverlayWindow) {
        MessageBoxA(NULL, TEXT("Overlay: Failed > #8"), "Loader", MB_OK);
        Sleep(2500);
        exit(0);
    }

    CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)Cheat::worldloop, nullptr, NULL, nullptr);
    CloseHandle(Cheat::worldloop);
    while (!glfwWindowShouldClose(OverlayWindow)) {
        Overlay::KeyLoop();
        Menu::render();
    }

    Overlay::Cleanup();
}



