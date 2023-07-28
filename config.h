#pragma once
#pragma once
#include "settings.h"
#include <format>

BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
    char lpString[1024];
    sprintf(lpString, TEXT ("%d"), nInteger);
    return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
    char lpString[1024];
    sprintf(lpString, TEXT ("%f"), nInteger);
    return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
{
    char szData[32];

    GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

    return (float)atof(szData);
}

void savecfg(LPCSTR path)
{

    //aimbot//
    WritePrivateProfileInt((("a")), (TEXT ("Aimbot")), Options::Aimbot::Aimbot, path);
    WritePrivateProfileInt((("a")), (TEXT ("FOV")), Options::Aimbot::fov, path);
    WritePrivateProfileInt((("a")), (TEXT ("SY")), Options::Aimbot::Smooth, path);
    WritePrivateProfileInt((("a")), (TEXT("Skip Knocked")), Options::Aimbot::SkipKnocked, path);
    WritePrivateProfileInt((("a")), (TEXT("Random Aim")), Options::Aimbot::RandomAim, path);
    WritePrivateProfileInt((("a")), (TEXT("Hitbox")), Options::Aimbot::hitbox, path);
    WritePrivateProfileInt((("a")), (TEXT("Aimkey")), Options::Aimbot::aimkey, path);

    //visual//
    WritePrivateProfileInt((("b")), (TEXT ("Crosshair")), Options::Visuals::Crosshair, path);
    WritePrivateProfileInt((("b")), (TEXT ("Snapline")), Options::Visuals::LineESP, path);
    WritePrivateProfileInt((("b")), (TEXT ("BoxESP")), Options::Visuals::BoxESP, path);
    WritePrivateProfileInt((("b")), (TEXT ("CornerBox")), Options::Visuals::CornerBoxESP, path);
    WritePrivateProfileInt((("b")), (TEXT ("Outline Text")), Options::Visuals::OutlineText, path);
    WritePrivateProfileInt((("b")), (TEXT ("Outline")), Options::Visuals::Outline, path);
    WritePrivateProfileInt((("b")), (TEXT ("Distance")), Options::Visuals::Distance, path);
    WritePrivateProfileInt((("b")), (TEXT("Filled")), Options::Visuals::Filled, path);
    
}
void loadcfg(LPCSTR path)
{
    //aimbot//
    Options::Aimbot::Aimbot = GetPrivateProfileIntA((TEXT ("a")), (TEXT ("Aimbot")), Options::Aimbot::Aimbot, path);
    Options::Aimbot::fov = GetPrivateProfileIntA((TEXT ("a")), (TEXT ("FOV")), Options::Aimbot::fov, path);
    Options::Aimbot::Smooth = GetPrivateProfileIntA((TEXT ("a")), (TEXT ("SY")), Options::Aimbot::Smooth, path);
    Options::Aimbot::SkipKnocked = GetPrivateProfileIntA((TEXT ("a")), (TEXT ("Skip Knocked")), Options::Aimbot::SkipKnocked, path);
    Options::Aimbot::RandomAim = GetPrivateProfileIntA((TEXT("a")), (TEXT("Random Aim")), Options::Aimbot::RandomAim, path);
    Options::Aimbot::hitbox = GetPrivateProfileIntA((TEXT("a")), (TEXT("Hitbox")), Options::Aimbot::hitbox, path);
    Options::Aimbot::aimkey = GetPrivateProfileIntA((TEXT("a")), (TEXT("Aimkey")), Options::Aimbot::aimkey, path);


    //visual//
    Options::Visuals::Crosshair = GetPrivateProfileIntA((TEXT ("b")), (TEXT ("Crosshair")), Options::Visuals::Crosshair, path);
    Options::Visuals::LineESP = GetPrivateProfileIntA((TEXT ("b")), (TEXT ("Snapline")), Options::Visuals::LineESP, path);
    Options::Visuals::BoxESP = GetPrivateProfileIntA((TEXT ("b")), (TEXT ("BoxESP")), Options::Visuals::BoxESP, path);
    Options::Visuals::BoxESP = GetPrivateProfileIntA((TEXT("b")), (TEXT("Filled")), Options::Visuals::Filled, path);
    Options::Visuals::CornerBoxESP = GetPrivateProfileIntA((TEXT ("b")), (TEXT ("CornerBox")), Options::Visuals::CornerBoxESP, path);
    Options::Visuals::OutlineText = GetPrivateProfileIntA((TEXT ("b")), (TEXT ("Outline Text")), Options::Visuals::OutlineText, path);
    Options::Visuals::Outline = GetPrivateProfileIntA((TEXT ("b")), (TEXT ("Outline")), Options::Visuals::Outline, path);
    Options::Visuals::Distance = GetPrivateProfileIntA((TEXT ("b")), (TEXT ("Distance")), Options::Visuals::Distance, path);
    Options::Visuals::MaxESPDrawDistance = GetPrivateProfileIntA((TEXT("b")), (TEXT("Max ESP Draw dist")), Options::Visuals::MaxESPDrawDistance, path);



};