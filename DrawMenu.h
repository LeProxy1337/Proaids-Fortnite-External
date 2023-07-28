#pragma once 
#include "Settings.h"
#include "Cheat.h"
#include "config.h"


int buttonoffsets[4] = { 0, 0, 0, 0 };
ImColor cRainbow = ImColor(182, 0, 182);
int realkey;
int keystatus;
int aimkey;


bool GetKey(int key)
{
    realkey = key;
    return true;
}
void ChangeKey(void* blank)
{
    keystatus = 1;
    while (true)
    {
        for (int i = 0; i < 0x87; i++)
        {
            if (GetKeyState(i) & 0x8000)
            {
                Options::Aimbot::aimkey = i;
                keystatus = 0;
                return;
            }
        }
    }
}

void ChangeKey2(void* blank)
{
    keystatus = 1;
    while (true)
    {
        for (int i = 0; i < 0x87; i++)
        {
            if (GetKeyState(i) & 0x8000)
            {
                Options::Aimbot::aimkey = i;
                keystatus = 0;
                return;
            }
        }
    }
}
static const char* keyNames[] = {
    "",
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
static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
    const char* const* items = (const char* const*)data;
    if (out_text)
        *out_text = items[idx];
    return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
    const char* preview_value = NULL;
    if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
        Items_ArrayGetter(keyNames, aimkey, &preview_value);

    std::string aimkeys;
    if (preview_value == NULL)
        aimkeys = ("Select Key");
    else
        aimkeys = preview_value;

    if (status == 1)
    {
        aimkeys = ("Press key to bind");
    }
    if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
    {
        if (status == 0)
        {
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
        }
    }
}

namespace Menu {

	void DrawMenu() {

        static int MenuTab;


        if (open)
        {
            menu_animation = menu_animation + 6;
            border_animation = border_animation + 6;
            menu_slide = menu_slide + 10;
        }
        else if (!open)
        {
            menu_animation = menu_animation - 6;
            border_animation = border_animation - 6;
            menu_slide = menu_slide - 10;
        }

        if (menu_animation > 254)
            menu_animation = 255;

        if (border_animation > 3.4)
            border_animation = 3.5;
        if (border_animation < 1)
            border_animation = 0;

        if (menu_slide > 560)
            menu_slide = 561;
        if (menu_slide < 1)
            menu_slide = 0;



        ImGuiStyle& style = ImGui::GetStyle();
        auto color = style.Colors;

        color[ImGuiCol_WindowBg] = ImColor(40, 40, 40, menu_animation);

        color[ImGuiCol_ChildBg] = ImColor(35, 35, 35, menu_animation);
        color[ImGuiCol_Border] = ImColor(25, 25, 25, menu_animation);
        color[ImGuiCol_BorderShadow] = ImColor(50, 50, 50, menu_animation);
        color[ImGuiCol_Button] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_ButtonActive] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25, menu_animation);
        color[ImGuiCol_ScrollbarBg] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_ScrollbarGrab] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_ScrollbarGrabActive] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_ScrollbarGrabHovered] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_CheckMark] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_FrameBg] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_SliderGrab] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_SliderGrabActive] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_PlotLines] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_PlotLinesHovered] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_PlotHistogram] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_PlotHistogramHovered] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_TabActive] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_TabUnfocusedActive] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_Header] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_HeaderActive] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_HeaderHovered] = ImColor(95, 75, 113, menu_animation);
        color[ImGuiCol_TitleBg] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_FrameBgActive] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_TitleBgActive] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_TitleBgCollapsed] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_PopupBg] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_TextSelectedBg] = ImColor(130, 60, 180, menu_animation);
        color[ImGuiCol_Text] = ImColor(255, 255, 255, menu_animation);
        color[ImGuiCol_TextDisabled] = ImColor(255, 255, 255, menu_animation);
        color[ImGuiCol_NavHighlight] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_NavWindowingHighlight] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_NavWindowingDimBg] = ImColor(40, 40, 40, menu_animation);
        color[ImGuiCol_ModalWindowDimBg] = ImColor(40, 40, 40, menu_animation);

        style.WindowTitleAlign = ImVec2(0.5, 0.5);
        style.WindowBorderSize = 1.0;


        style.ChildRounding = 0;
        style.FrameRounding = 0;
        style.ScrollbarRounding = 0;
        style.GrabRounding = 0;
        style.PopupRounding = 0;
        style.WindowRounding = 0;
        style.FramePadding = ImVec2(3.0f, 3.0f);

        style.AntiAliasedLines = true;
        style.AntiAliasedFill = true;
		if (Options::ShowMenu) {
            ImGui::PushFont(main_font);
            ImGui::SetNextWindowSize(ImVec2(menu_slide, 500));
            ImGui::Begin("", nullptr, ImGuiWindowFlags_NoDecoration);

            ImGui::BeginChild("##LeftSide", ImVec2(120, ImGui::GetContentRegionAvail().y), TRUE);
            {
                if (ImGui::Button("AIM", ImVec2(110, 40)))
                    MenuTab = 1;

                if (ImGui::Button("VISUAL", ImVec2(110, 40)))
                    MenuTab = 2;

                if (ImGui::Button("MISC", ImVec2(110, 40)))
                    MenuTab = 3;

                if (ImGui::Button("CONFIG", ImVec2(110, 40)))
                    MenuTab = 4;
            }
            ImGui::EndChild();
            ImGui::SameLine();

            ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
            {
                if (MenuTab == 1) {
                    ImGui::Text("Aim");
                    ImGui::Separator();
                    ImGui::Checkbox("Enable Combat", &Options::Aimbot::Aimbot);
                    ImGui::SliderInt("Radius Value", &Options::Aimbot::fov, 1, 360);
                    ImGui::SliderInt("Smoothing", &Options::Aimbot::Smooth, 1, 30);
                    ImGui::Checkbox("Show Radius", &Options::Visuals::ShowFOV);



                    ImGui::Checkbox("Skip Knocked", &Options::Aimbot::SkipKnocked);
         
                    ImGui::Checkbox("Random Bone", &Options::Aimbot::RandomAim);
                 
                    ImGui::Combo(("Hitbox"), &Options::Aimbot::hitbox, Hitbox, IM_ARRAYSIZE(Hitbox));

                   HotkeyButton(Options::Aimbot::aimkey, ChangeKey, keystatus); ImGui::SameLine(); ImGui::Text(("Aimbot Key"));
                }
            }
            ImGui::EndChild();
            ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
            {
                if (MenuTab == 2) {
                    ImGui::Text("Visual");
                    ImGui::Separator();
                    ImGui::Checkbox("Enable Visuals ", &Options::Visuals::ESP);
                    ImGui::Checkbox("Draw Box", &Options::Visuals::BoxESP);
                    ImGui::Checkbox("Draw CornerBox", &Options::Visuals::CornerBoxESP);
                    ImGui::Checkbox("Draw Distance", &Options::Visuals::Distance);
                    ImGui::Checkbox("Draw Snaplines", &Options::Visuals::LineESP);
                    ImGui::Checkbox("Draw Radar", &Options::Visuals::Radar);
                    if (Options::Visuals::Radar) {
                        ImGui::Separator();
                        ImGui::SliderFloat(("Pos X"), &radar_position_x, 10.f, 2000.f);
                        ImGui::Separator();
                        ImGui::SliderFloat(("Pos Y"), &radar_position_y, 10.f, 2000.f);
                        ImGui::Separator();
                        ImGui::SliderFloat(("Distance"), &RadarDistance, 10.f, 700.f);
                        ImGui::Separator();
                        ImGui::SliderFloat(("Size"), &radar_size, 100.f, 500.f);
                    }

                }
            }
            ImGui::EndChild();
            ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
            {
                if (MenuTab == 3) {
                    ImGui::Text("Misc");
                    ImGui::Separator();
                    ImGui::Checkbox("Use Beta W2S", &worldtoscreentwo);
                    ImGui::SliderInt("Box Thickness", &Options::BoxThickness, 1, 30);



                    ImGui::SliderFloat("Display Distance", &Options::Visuals::MaxESPDrawDistance, 1, 450);
                    if (ImGui::Button(("Panic")))
                    {

                        exit(0);
                    }
                }
            }
            ImGui::EndChild();
            ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
            {
                if (MenuTab == 4) {
                    ImGui::Text("Config");
                    ImGui::Separator();
                    ImGui::PushItemWidth(130.0f);
                    ImGui::ColorPicker3(("Visible Color"), fl_VisibleColor, ImGuiColorEditFlags_NoInputs); 
                    ImGui::ColorPicker3(("InVisible Color"), fl_InVisibleColor, ImGuiColorEditFlags_NoInputs);
                }
            }
            ImGui::EndChild();


            ImGui::End();
            ImGui::PopFont();
		}
       
	}

    void render() {
    
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (Options::Visuals::Radar) {
            fortnite_radar(radar_position_x, radar_position_y, radar_size, rect_radar);
        }
        Cheat::actor_loop();
      
        DrawMenu();


        ImGui::Render();
      

        int display_w, display_h;
        glfwGetFramebufferSize(OverlayWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(OverlayWindow);
    }
    
}