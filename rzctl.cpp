#include <cstdint>
#include <iostream>
#include "nt.h"
#include "rzctl.h"

HANDLE hDevice = INVALID_HANDLE_VALUE;

bool rzctl::init()
{
    if (hDevice != INVALID_HANDLE_VALUE) {
        CloseHandle(hDevice);
    }
    
    std::wstring name;

    if (!nt::find_sym_link(L"\\GLOBAL??", L"RZCONTROL", name)) {
        return false;
    }

    std::wstring sym_link = L"\\\\?\\" + name;

    hDevice = CreateFileW(sym_link.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    return hDevice != INVALID_HANDLE_VALUE;
}

void rzctl::mouse_move(int x, int y, bool from_start_point)
{
    int max_val = 0;

    /*
    * To avoid errors, lets just fix the x and y :p
    */
    if (!from_start_point) {
        max_val = MAX_VAL;
        if (x < 1)
            x = 1;

        if (x > max_val) 
            x = max_val;

        if (y < 1)
            y = 1;

        if (y > max_val) 
            y = max_val;
    }

    /*
    * Hardcoded values copied from looking at buffer passed from "Razer Synapse Service.exe"
    */
    MOUSE_IOCTL_STRUCT ms = {
        0, InputType::MOUSE,
        max_val, MouseFlags::NONE,
        0,
        x, y,
        0
    };
    _impl_ioctl(&ms, sizeof(MOUSE_IOCTL_STRUCT));
}

void rzctl::mouse_click(int flags)
{
    auto _flags = static_cast<MouseFlags>(flags);
    MOUSE_IOCTL_STRUCT ms = {
        0, InputType::MOUSE,
        0, _flags,
        0, 
        0, 0, 
        0
    };
    _impl_ioctl(&ms, sizeof(MOUSE_IOCTL_STRUCT));
}

void rzctl::key_state(int16_t scan_code, int16_t key_state)
{
    KEYBOARD_IOCTL_STRUCT ks = {
        0, InputType::KEYBOARD,
        0, 
        scan_code, key_state,
        0, 
        0, 0, 
        0, 0
    };

    _impl_ioctl(&ks, sizeof(KEYBOARD_IOCTL_STRUCT));
}

void rzctl::_impl_ioctl(LPVOID in_buffer, DWORD in_buffer_size)
{
    if (in_buffer)
    {
        DWORD junk;

        BOOL bResult = DeviceIoControl(
            hDevice, IOCTL_MOUSE,
            in_buffer, in_buffer_size,
            NULL, 0,
            &junk, NULL
            );
        
        // Re-open handle incase of failure
        if (!bResult)
            init();
    }
}