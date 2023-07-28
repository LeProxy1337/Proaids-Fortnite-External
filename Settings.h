#pragma once

#include "Includes.h"
#include <cstddef>
#include <wtypes.h>
#include "ImGui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui_internal.h"

int width1 = 1920;
int height1 = 1080;
int width = 1920;
int height = 1080;

uintptr_t process_id;
uintptr_t virtualaddy;

HWND windowid = NULL;
bool test = true;
bool test2 = false;
bool test3 = false;
bool test4 = false;
bool test5 = false;
 static int menu_animation = 0;
 static int border_animation = 0;
 static int menu_slide = 0;
 static bool small_tab = false;
 static int do_tab_anim = 0;
bool open = true;
uintptr_t ptr_cam_rotation;
uintptr_t ptr_cam_location;

namespace dynamicoffsets {

	uintptr_t CurrentWeapon;


	bool BIsTargeting;

	uint32_t pawnWeaponID;
	std::string pObjName;
}


bool rifleout;
bool shotgunout;
bool smgout;
bool sniperout;

bool uncommon = true;
bool rare = true;
bool epic = true;
bool legendary = true;
bool mythic = true;
bool common = true;

bool enemiesarround = true;
int enemyID = 0;
int enemyIDvis = 0;
int CloseRangeDistanceID = 0;

float CloseRangeDistance = 50.f;
namespace Options {
	bool DrawFPS = true;
	int VisDist = 100;
	bool Items;
	bool enableloot = true;
	bool universalaim = true;


	bool DynamicFOV = true;
	bool StaticFOV = false;


	bool Triggerkey;
	bool Universaltrig;




	namespace Aimbot {
		bool Aimbot = false;
		bool Triggerbot = false;
		bool vischeck = true;
		bool SkipKnocked = true;
		bool Onlywithgun = false;
		bool RandomAim = false;
		int triggerfov = 25;
		int fov = 50;
		int fovrifle = 50;
		int fovshotgun = 50;
		int fovsmg = 50;
		int fovsniper = 50;



		int Smooth = 7;
		int SmoothRifle = 7;
		int SmoothShotgun = 7;
		int SmoothSMG = 7;
		int SmoothSniper = 7;

		static int weapon = 0;
		static int hitbox = 0;
		 int aimkey = 0;
		 int aimkey2 = 0;
		static int AimBoneInt;
	}
	
	bool IsVisible;
	int BoxThickness = 1;
	int BoxThicknessOutline = 2;
	namespace Visuals {
		bool ESP = true;
		bool BoxESP = false;
		bool Filled; 
		bool Weapon;
		bool Name;
		bool CornerBoxESP = false;
		bool RoundBox = false;
		bool FilledBoxESP = false;
		bool bFill2DBox = false;
		bool LineESP = false;
		bool Outline = true;
		bool OutlineText = true;
		bool ShowFOV = true;
		bool Distance = true;
		bool SkeletonESP = true;
		bool LobbyESP = false;
		bool ViewAngle;
		bool Crosshair = false;
		bool Radar;
		float MaxESPDrawDistance = 300;
		float MaxSkeletonDrawDistance = 200;
	}

	namespace Misc{
		bool Backtrack;
		int UDSlider = 10;
		bool test = true;
		bool DeveloperOptions = false;
		bool Skydiving;
		int Pickuptime;
		bool InstantItemPickup;
		bool JumpLastActivatedTime;
		bool bAlwaysboosting;
		bool selfdestruct;
		bool boundingboxes;
		int explode = 1;
		int i = 0;
	}

	namespace Exploits {


	}

	namespace Fonts {

		ImFont* fontmain = nullptr;
		ImFont* fontmainbig = nullptr;
		ImFont* fontmainbigbig = nullptr;
		ImFont* icon = nullptr;

	}

	namespace Intro {
		bool temp = false;
		bool test1 = false;
		bool test2 = false;
		bool test3 = true;
		bool test4 = true;
	}

	//Misc

	bool ShowMenu = false;

	namespace Colors
	{
		float RadarPlayers[3] = { 1.0f , 1.0f , 1.0f };
		float espcol[3] = { 1.0f , 1.0f , 1.0f };
		float espcolvi[3] = { 1.0f , 1.0f , 1.0f };
		float espfilledvis[3] = { 1.0f , 1.0f , 1.0f };
		float espfilled[3] = { 1.0f , 1.0f , 1.0f };
		float skelcol[3] = { 1.0f , 1.0f , 1.0f };
		float skelcolvis[3] = { 1.0f , 1.0f , 1.0f };
		float distancecol[3] = { 1.0f , 1.0f , 1.0f };
		float distancecolvi[3] = { 1.0f , 1.0f , 1.0f };
		float crosscol[3] = { 1.0f , 1.0f , 1.0f };
		float fovcol[3] = { 1.0f , 1.0f , 1.0f };
		float linecol[3] = { 1.0f , 1.0f , 1.0f };
		float TopTextVisible[3] = { 1.0f , 1.0f , 1.0f };
	}

	namespace login {
		bool login1 = false;
		bool login2 = false;
		bool login3 = false;
		bool login4 = false;

		bool login5 = false;
		bool login6 = false;
		bool login7 = false;
		bool login8 = false;

	}

}

static const char* Hitbox[] =
{
	"Head",
	"Neck",
	"Chest"
};


static const char* Weapons[] =
{
	"Rifle",
	"Shotgun",
	"SMG", 
	"Sniper"
};


const char* const KeyNames[] = {
	"No Key Selected",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

bool ImGui::Hotkey(const char* label, int* k, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f), window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id, false);
	const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered) {
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = *k;

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (ImGui::IsKeyPressedMap(ImGuiKey_Escape)) {
			*k = 0;
			ImGui::ClearActiveID();
		}
		else {
			*k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImColor(30, 30, 30, 255)), true, 0.f);

	if (*k != 0 && g.ActiveId != id) {
		strcpy_s(buf_display, KeyNames[*k]);
	}
	else if (g.ActiveId == id) {
		strcpy_s(buf_display, "Press a key");
		Sleep(100);
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
	//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
	//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}
