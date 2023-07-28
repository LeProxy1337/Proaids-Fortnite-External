#pragma once

#define IOCTL_MOUSE 0x88883020

#define MAX_VAL 65536
#include <cstdint>
#include <stdio.h>
#include <Windows.h>

enum class InputType {
    KEYBOARD = 1,
    MOUSE = 2
};

enum class MouseFlags {
    NONE =        0,
    LEFT_DOWN =   1 << 0,
    LEFT_UP =     1 << 1,
    RIGHT_DOWN =  1 << 2,
    RIGHT_UP =    1 << 3,
    MIDDLE_DOWN = 1 << 4,
    MIDDLE_UP =   1 << 5,
    MOUSE4_DOWN = 1 << 6,
    MOUSE4_UP =   1 << 7,
    MOUSE5_DOWN = 1 << 8,
    MOUSE5_UP =   1 << 9,
};

// Scancodes but this changes based on layout I think
enum class ScanCode : uint16_t {
    None = 0,
    Escape = 1,
    One = 2,
    Two = 3,
    Three = 4,
    Four = 5,
    Five = 6,
    Six = 7,
    Seven = 8,
    Eight = 9,
    Nine = 10,
    Zero = 11,
    DashUnderscore = 12,
    PlusEquals = 13,
    Backspace = 14,
    Tab = 15,
    Q = 16,
    W = 17,
    E = 18,
    R = 19,
    T = 20,
    Y = 21,
    U = 22,
    I = 23,
    O = 24,
    P = 25,
    OpenBracketBrace = 26,
    CloseBracketBrace = 27,
    Enter = 28,
    Control = 29,
    A = 30,
    S = 31,
    D = 32,
    F = 33,
    G = 34,
    H = 35,
    J = 36,
    K = 37,
    L = 38,
    SemicolonColon = 39,
    SingleDoubleQuote = 40,
    Tilde = 41,
    LeftShift = 42,
    BackslashPipe = 43,
    Z = 44,
    X = 45,
    C = 46,
    V = 47,
    B = 48,
    N = 49,
    M = 50,
    CommaLeftArrow = 51,
    PeriodRightArrow = 52,
    ForwardSlashQuestionMark = 53,
    RightShift = 54,
    RightAlt = 56,
    Space = 57,
    CapsLock = 58,
    F1 = 59,
    F2 = 60,
    F3 = 61,
    F4 = 62,
    F5 = 63,
    F6 = 64,
    F7 = 65,
    F8 = 66,
    F9 = 67,
    F10 = 68,
    F11 = 87,
    F12 = 88,
    Up = 72,
    Down = 80,
    Right = 77,
    Left = 75,
    Home = 71,
    End = 79,
    Delete = 83,
    PageUp = 73,
    PageDown = 81,
    Insert = 82,
    PrintScreen = 55, // And break key is 42
    NumLock = 69,
    ScrollLock = 70,
    Menu = 93,
    WindowsKey = 91,
    NumpadDivide = 53,
    NumpadAsterisk = 55,
    Numpad7 = 71,
    Numpad8 = 72,
    Numpad9 = 73,
    Numpad4 = 75,
    Numpad5 = 76,
    Numpad6 = 77,
    Numpad1 = 79,
    Numpad2 = 80,
    Numpad3 = 81,
    Numpad0 = 82,
    NumpadDelete = 83,
    NumpadEnter = 28,
    NumpadPlus = 78,
    NumpadMinus = 74,
};

class MOUSE_IOCTL_STRUCT
{
public:
    int32_t unknown0; //0x0000
    InputType input_type; //0x0004
    int32_t unknown1; //0x0008
    MouseFlags flags; //0x000C
    int32_t unknown2; //0x0010
    int32_t x; //0x0014
    int32_t y; //0x0018
    int32_t unknown3; //0x001C
}; //Size: 0x0020

class KEYBOARD_IOCTL_STRUCT 
{
public:
    int32_t unknown0; //0x0000
    InputType input_type; //0x0004
    int16_t unknown1; //0x0008
    int16_t scan_code; //0x000A
    int16_t state; //0x000c
    int16_t unknown3; //0x000E
    int32_t unknown2; //0x0010
    int32_t x; //0x0014
    int32_t y; //0x0018
    int32_t unknown4; //0x001C
}; //Size: 0x0020

namespace rzctl {
    /*
    * finds the symbolic link that contains name RZCONTROL and opens a handle to the respective device
    */
    __declspec(dllexport) bool init();

    /*
    * if going from point, x and y will be the offset from current mouse position
    * otherwise it will be a number in range of 1 to 65536, where 1, 1 is top left of screen
    * if using multiple monitors the input values remain the same, but outcome different, i just don't recommend bothering with this bs
    * note: x and/or y can not be 0 unless going from start point	
    */
    __declspec(dllexport) void mouse_move(int x, int y, bool from_start_point = true);
    __declspec(dllexport) void mouse_click(int flags);

    /* keyboard stuff */

    __declspec(dllexport) void key_state(int16_t scan_code, int16_t key_state);

    /*
    * communicates to the device
    */
    void _impl_ioctl(LPVOID in_buffer, DWORD in_buffer_size);
}