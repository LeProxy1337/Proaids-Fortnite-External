#pragma once


#include <iostream>
#include <windows.h>
#include <vcruntime.h>
#include <tlhelp32.h>
#include <uxtheme.h>
#include <dwmapi.h>
#include <winternl.h>
#include <thread>
#include <vector>
#include <array>
#include <WinInet.h>
#include <urlmon.h>


#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Wininet.lib")

#include "DX/d3dx9math.h"

#include <GL/glew.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "Auth/Auth.h"
//#include "Comm.h"
bool streamproof;
using namespace KeyAuth;

std::string name = TEXT("FORTNITE"); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = TEXT("ceJ10e9bfD"); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = TEXT("b290969cef90bd427a65515142b9107c1dc9ae57c91facfdede6f5fd6dd8b2b0"); // app secret, the blurred text on licenses tab and other tabs
std::string version = TEXT("1.0"); // leave alone unless you've changed version on website
std::string url = TEXT("https://keyauth.win/api/1.2/"); // change if you're self-hosting

api KeyAuthApp(name, ownerid, secret, version, url);

bool razermousebypass;
#include "rzctl.h"


using namespace std;



std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}

