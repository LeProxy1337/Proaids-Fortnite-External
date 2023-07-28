#pragma once
#include <iostream>
#include <Windows.h>

BYTE NtUserSendInput_Bytes[30];
BYTE NtUserGetAsyncKeyState_Bytes[30];


BOOLEAN WINAPI Init()
{
	// windows 8.1 / windows 10
	LPVOID NtUserSendInput_Addr = GetProcAddress(GetModuleHandle(TEXT ("win32u")), TEXT ("NtUserSendInput"));
	if (!NtUserSendInput_Addr)
	{
		NtUserSendInput_Addr = GetProcAddress(GetModuleHandle(TEXT ("win32u")), TEXT ("NtUserSendInput"));
		if (!NtUserSendInput_Addr)
		{
			// Windows 7 or lower detected
			NtUserSendInput_Addr = GetProcAddress(GetModuleHandle(TEXT ("win32u")), TEXT ("SendInput"));
			if (!NtUserSendInput_Addr)
				return FALSE;
		}
	}

	// windows 8.1 / windows 10
	LPVOID NtUserGetAsyncKeyState_Addr = GetProcAddress(GetModuleHandle(TEXT ("win32u")), TEXT ("NtUserGetAsyncKeyState"));
	if (!NtUserGetAsyncKeyState_Addr)
	{
		NtUserGetAsyncKeyState_Addr = GetProcAddress(GetModuleHandle(TEXT ("win32u")), TEXT ("NtUserGetAsyncKeyState"));
		if (!NtUserGetAsyncKeyState_Addr)
		{
			// Windows 7 or lower detected
			NtUserGetAsyncKeyState_Addr = GetProcAddress(GetModuleHandle(TEXT ("win32u")), TEXT ("GetAsyncKeyState"));
			if (!NtUserGetAsyncKeyState_Addr)
				return FALSE;
		}
	}
	memcpy(NtUserSendInput_Bytes, NtUserSendInput_Addr, 30);
	memcpy(NtUserGetAsyncKeyState_Bytes, NtUserGetAsyncKeyState_Addr, 30);
	return TRUE;
}


BOOLEAN WINAPI NtUserSendInput(UINT cInputs, LPINPUT pInputs, int cbSize)
{
	LPVOID NtUserSendInput_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // allocate space for syscall
	if (!NtUserSendInput_Spoof)
		return FALSE;
	memcpy(NtUserSendInput_Spoof, NtUserSendInput_Bytes, 30); // copy syscall
	NTSTATUS Result = reinterpret_cast<NTSTATUS(NTAPI*)(UINT, LPINPUT, int)>(NtUserSendInput_Spoof)(cInputs, pInputs, cbSize); // calling spoofed function
	ZeroMemory(NtUserSendInput_Spoof, 0x1000); // clean address
	VirtualFree(NtUserSendInput_Spoof, 0, MEM_RELEASE); // free it
	return (Result > 0); // return the status
}


UINT WINAPI NtUserGetAsyncKeyState(UINT Key)
{
	LPVOID NtUserGetAsyncKeyState_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // allocate space for syscall
	if (!NtUserGetAsyncKeyState_Spoof)
		return FALSE;
	memcpy(NtUserGetAsyncKeyState_Spoof, NtUserGetAsyncKeyState_Bytes, 30); // copy syscall
	NTSTATUS Result = reinterpret_cast<NTSTATUS(NTAPI*)(UINT)>(NtUserGetAsyncKeyState_Spoof)(Key); // calling spoofed function
	ZeroMemory(NtUserGetAsyncKeyState_Spoof, 0x1000); // clean address
	VirtualFree(NtUserGetAsyncKeyState_Spoof, 0, MEM_RELEASE); // free it
	return Result; // return the status
}

BOOLEAN WINAPI movemouse(int X, int Y, int time)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = time;
	input.mi.dx = X;
	input.mi.dy = Y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK;
	return NtUserSendInput(1, &input, sizeof(input));
}


VOID mouseevent2(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
{

	INPUT Input[3] = { 0 };
	Input[0].type = INPUT_MOUSE;
	Input[0].mi.dx = dx;
	Input[0].mi.dy = dy;
	Input[0].mi.mouseData = dwData;
	Input[0].mi.dwFlags = dwFlags;
	Input[0].mi.time = 0;
	Input[0].mi.dwExtraInfo = dwExtraInfo;

	NtUserSendInput((UINT)1, (LPINPUT)&Input, (INT)sizeof(INPUT));
}

UINT WINAPI getkey(UINT Key)
{
	return NtUserGetAsyncKeyState(Key);
}