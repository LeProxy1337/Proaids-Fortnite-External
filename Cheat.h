#pragma once 
#include "GameFuncs.h"
#include "Offsets.h"
#include "Vector.h"
#include "draw.h"
#include "spoofed.h"
#include "drvkm.h"
#include "defs.h"
float CenterX = GetSystemMetrics(0) / 2 - 1;
float CenterY = GetSystemMetrics(1) / 2 - 1;

typedef struct players {
    uint64_t actor;
    int ia;
    char isDBNO;
    uint64_t mesh;
    uint64_t currentweapon;
    uint64_t aimbotmesh;
    FN_POINTER bonearray;
    wchar_t platformud;
    int teamid;
    int myteamid;
    uint64_t testplatformud;
    uint64_t playerstate;
    std::string playernameud;
    uint64_t localplayerstate;
}players;
std::vector<players> entitylist;

class Color
{
public:
    RGBA red = { 255,0,0,255 };
    RGBA Magenta = { 255,0,255,255 };
    RGBA yellow = { 255,255,0,255 };
    RGBA grayblue = { 128,128,255,255 };
    RGBA green = { 128,224,0,255 };
    RGBA darkgreen = { 0,224,128,255 };
    RGBA brown = { 192,96,0,255 };
    RGBA pink = { 255,168,255,255 };
    RGBA DarkYellow = { 216,216,0,255 };
    RGBA SilverWhite = { 236,236,236,255 };
    RGBA purple = { 144,0,255,255 };
    RGBA Navy = { 88,48,224,255 };
    RGBA skyblue = { 0,136,255,255 };
    RGBA graygreen = { 128,160,128,255 };
    RGBA blue = { 0,96,192,255 };
    RGBA orange = { 255,128,0,255 };
    RGBA peachred = { 255,80,128,255 };
    RGBA reds = { 255,128,192,255 };
    RGBA darkgray = { 96,96,96,255 };
    RGBA Navys = { 0,0,128,255 };
    RGBA darkgreens = { 0,128,0,255 };
    RGBA darkblue = { 0,128,128,255 };
    RGBA redbrown = { 128,0,0,255 };
    RGBA purplered = { 128,0,128,255 };
    RGBA greens = { 0,255,0,255 };
    RGBA envy = { 0,255,255,255 };
    RGBA black = { 0,0,0,255 };
    RGBA gray = { 128,128,128,255 };
    RGBA white = { 255,255,255,255 };
    RGBA blues = { 30,144,255,255 };
    RGBA lightblue = { 135,206,250,160 };
    RGBA Scarlet = { 220, 20, 60, 160 };
    RGBA white_ = { 255,255,255,200 };
    RGBA gray_ = { 128,128,128,200 };
    RGBA black_ = { 0,0,0,200 };
    RGBA red_ = { 255,0,0,200 };
    RGBA Magenta_ = { 255,0,255,200 };
    RGBA yellow_ = { 255,255,0,200 };
    RGBA grayblue_ = { 128,128,255,200 };
    RGBA green_ = { 128,224,0,200 };
    RGBA darkgreen_ = { 0,224,128,200 };
    RGBA brown_ = { 192,96,0,200 };
    RGBA pink_ = { 255,168,255,200 };
    RGBA darkyellow_ = { 216,216,0,200 };
    RGBA silverwhite_ = { 236,236,236,200 };
    RGBA purple_ = { 144,0,255,200 };
    RGBA Blue_ = { 88,48,224,200 };
    RGBA skyblue_ = { 0,136,255,200 };
    RGBA graygreen_ = { 128,160,128,200 };
    RGBA blue_ = { 0,96,192,200 };
    RGBA orange_ = { 255,128,0,200 };
    RGBA pinks_ = { 255,80,128,200 };
    RGBA Fuhong_ = { 255,128,192,200 };
    RGBA darkgray_ = { 96,96,96,200 };
    RGBA Navy_ = { 0,0,128,200 };
    RGBA darkgreens_ = { 0,128,0,200 };
    RGBA darkblue_ = { 0,128,128,200 };
    RGBA redbrown_ = { 128,0,0,200 };
    RGBA purplered_ = { 128,0,128,200 };
    RGBA greens_ = { 0,255,0,200 };
    RGBA envy_ = { 0,255,255,200 };

    RGBA glassblack = { 0, 0, 0, 160 };
    RGBA GlassBlue = { 65,105,225,80 };
    RGBA glassyellow = { 255,255,0,160 };
    RGBA glass = { 200,200,200,60 };

    RGBA filled = { 0, 0, 0, 150 };

    RGBA Plum = { 221,160,221,160 };

};
Color Col;
//functions
void RadarRange(float* x, float* y, float range)
{
    if (fabs((*x)) > range || fabs((*y)) > range)
    {
        if ((*y) > (*x))
        {
            if ((*y) > -(*x))
            {
                (*x) = range * (*x) / (*y);
                (*y) = range;
            }
            else
            {
                (*y) = -range * (*y) / (*x);
                (*x) = -range;
            }
        }
        else
        {
            if ((*y) > -(*x))
            {
                (*y) = range * (*y) / (*x);
                (*x) = range;
            }
            else
            {
                (*x) = -range * (*x) / (*y);
                (*y) = -range;
            }
        }
    }
}

bool ShowRadar = true;
bool rect_radar = true;
float radar_position_x{ 10.0f };
float radar_position_y{ 10.0f };
float radar_size{ 150.0f };
float RadarDistance = { 50.f };
float downed[1];
float fl_VisibleColor[3];
float fl_InVisibleColor[3];
Camera GetCamera()
{
    Camera FGC_Camera;
            FGC_Camera.Location = camera::location;
            FGC_Camera.Rotation.x = camera::rotation.x;
            FGC_Camera.Rotation.y = camera::rotation.y;
            FGC_Camera.Rotation.z = 0;
    return FGC_Camera;
}
void CalcRadarPoint(Vector3 vOrigin, int& screenx, int& screeny)
{
    Camera vCamera = GetCamera();
    Vector3 vAngle = vCamera.Rotation;
    auto fYaw = vAngle.y * M_PI / 180.0f;
    float dx = vOrigin.x - vCamera.Location.x;
    float dy = vOrigin.y - vCamera.Location.y;

    float fsin_yaw = sinf(fYaw);
    float fminus_cos_yaw = -cosf(fYaw);

    float x = dy * fminus_cos_yaw + dx * fsin_yaw;
    x = -x;
    float y = dx * fminus_cos_yaw - dy * fsin_yaw;

    float range = (float)RadarDistance * 1000.f;

    RadarRange(&x, &y, range);

    ImVec2 DrawPos = ImVec2(radar_position_x, radar_position_y);
    ImVec2 DrawSize = ImVec2(radar_size, radar_size);


    int rad_x = (int)DrawPos.x;
    int rad_y = (int)DrawPos.y;

    float r_siz_x = DrawSize.x;
    float r_siz_y = DrawSize.y;

    int x_max = (int)r_siz_x + rad_x - 5;
    int y_max = (int)r_siz_y + rad_y - 5;

    screenx = rad_x + ((int)r_siz_x / 2 + int(x / range * r_siz_x));
    screeny = rad_y + ((int)r_siz_y / 2 + int(y / range * r_siz_y));

    if (screenx > x_max)
        screenx = x_max;

    if (screenx < rad_x)
        screenx = rad_x;

    if (screeny > y_max)
        screeny = y_max;

    if (screeny < rad_y)
        screeny = rad_y;
}

void fortnite_radar(float x, float y, float size, bool rect = false)
{
    if (ShowRadar)
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);
        static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
        ImGui::Begin(("##radar"), nullptr, flags);

        float render_size = 5;
        ImDrawList* drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(ImVec2(x, y), ImVec2(x + size, y + size), ImGui::GetColorU32({ 0.43f, 0.43f, 0.43f, 1.f }), 0.0f, 0);
            drawList->AddCircleFilled(ImVec2(x + size / 2, y + size / 2), render_size / 2 * sqrt(2), ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }), 1000);
          //  drawList->AddCircle(ImVec2(x + size / 2, y + size / 2), size, ImGui::GetColorU32({ 0.1f, 0.1f, 0.1f, 1.0f }), 1000, 5);

        ImGui::End();
    }
}

void add_players_radar(Vector3 WorldLocation)
{
    if (ShowRadar)
    {
        static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
        ImGui::Begin(("##radar"), nullptr, flags);

        int ScreenX, ScreenY = 0;
        const auto& GetWindowDrawList = ImGui::GetWindowDrawList();
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        CalcRadarPoint(WorldLocation, ScreenX, ScreenY);
        if (Options::IsVisible) {
            drawList->AddCircleFilled(ImVec2(ScreenX, ScreenY), 5, ImGui::GetColorU32({ fl_VisibleColor[0],fl_VisibleColor[1],fl_VisibleColor[2],  1.0f }), 7);
        }
        else {
            drawList->AddCircleFilled(ImVec2(ScreenX, ScreenY), 5, ImGui::GetColorU32({ fl_InVisibleColor[0],fl_InVisibleColor[1],fl_InVisibleColor[2],  1.0f }), 7);
        }
       

        ImGui::End();
    }
}

namespace Cheat {

    void worldloop() {

        while (true) {

            std::vector<players> tmpList;


            pointer::Uworld = driver.readptr<uint64_t>(virtualaddy + Offsets::UWorld); //+
            pointer::GameInstance = driver.readptr<uint64_t>(pointer::Uworld + Offsets::OwningGameInstance); //+
            pointer::PersistentLevel = driver.readptr<uint64_t>(pointer::Uworld + Offsets::PersistentLevel);
            pointer::LocalPlayers = driver.readptr<uint64_t>(pointer::GameInstance + Offsets::LocalPlayers);
            pointer::LocalPlayer = driver.readptr<uint64_t>(pointer::LocalPlayers);
            pointer::PlayerController = driver.readptr<uint64_t>(pointer::LocalPlayer + Offsets::PlayerController); //+
            pointer::LocalPawn = driver.readptr<uint64_t>(pointer::PlayerController + Offsets::AcknowledgedPawn); //+
            pointer::PlayerState = driver.readptr<uint64_t>(pointer::LocalPawn + Offsets::PlayerState);
            pointer::RootComponent = driver.readptr<uint64_t>(pointer::LocalPawn + Offsets::RootComponent); //+
            pointer::LocalActorPos = driver.readptr<Vector3>(pointer::RootComponent + Offsets::LocalActorPos);
            pointer::PlayerCameraManager = driver.readptr<uintptr_t>(pointer::PlayerController + Offsets::PlayerCameraManager);



            pointer::ActorCount = driver.readptr<int>(pointer::PersistentLevel + 0xA0);
            pointer::AActors = driver.readptr<uintptr_t>(pointer::PersistentLevel + 0x98);

            for (Options::Misc::i = 0; Options::Misc::i < pointer::ActorCount; ++Options::Misc::i) {

                pointer::CurrentActor = driver.readptr<uint64_t>(pointer::AActors + Options::Misc::i * 0x8);
                if (!pointer::CurrentActor || pointer::CurrentActor == NULL) { continue; }
                pointer::CurrentActorMesh = driver.readptr<uint64_t>(pointer::CurrentActor + Offsets::Mesh);
                if (!pointer::CurrentActorMesh || pointer::CurrentActorMesh == NULL)continue;
                int curactorid = driver.readptr<int>(pointer::CurrentActor + 0x18);
                if (!curactorid || curactorid == NULL)continue;

                       pointer::PlayerState = driver.readptr<uint64_t>(pointer::CurrentActor + Offsets::PlayerState);
                       pointer::LocalPlayerState = driver.readptr<uint64_t>(pointer::LocalPawn + Offsets::PlayerState);
                       char isDBNO = (driver.readptr<char>(pointer::CurrentActor + 0x832) >> 4) & 1;
                       int MyTeamId = driver.readptr<int>(pointer::LocalPlayerState + Offsets::TeamIndex);
                       int TeamId = driver.readptr<int>(pointer::PlayerState + Offsets::TeamIndex);
                       if (MyTeamId == TeamId) continue;
                       if (!MyTeamId || MyTeamId == NULL)continue;

                   if (!pointer::PlayerState || pointer::PlayerState == NULL)continue;
                   if (pointer::LocalPawn == pointer::CurrentActor)continue;
                      
                    if (driver.readptr<float>(pointer::CurrentActor + Offsets::ReviveFromDBNOTime) == 10 && pointer::CurrentActorMesh != 0x0 && curactorid != 0x0 && pointer::CurrentActor != 0x0 && pointer::PlayerState)
                    {
                        players fnlEntity{ };
                        fnlEntity.actor = pointer::CurrentActor;
                        fnlEntity.mesh = pointer::CurrentActorMesh;
                        fnlEntity.myteamid = MyTeamId;
                        fnlEntity.isDBNO = isDBNO;
                        fnlEntity.playerstate = pointer::PlayerState;
                        fnlEntity.localplayerstate = pointer::LocalPlayerState;
                        tmpList.push_back(fnlEntity);
                }
            }
            entitylist.clear();
            entitylist = tmpList;
            Sleep(2300);
        }
    }



    void actor_loop() {
        auto entityListCopy = entitylist;
        float closestDistance = FLT_MAX;
        DWORD_PTR closestPawn = NULL;

     

      


       if (Options::Visuals::ShowFOV) {
              ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(width / 2, height / 2), Options::Aimbot::fov / camera::fov * 360, IM_COL32(255, 255, 255, 110), 790, 1);
       }


       for (auto entity : entityListCopy)
       {
            FN_VECTOR vHeadBone = get_bone(entity.mesh, 68);
            FN_VECTOR vHeadBoneOut = W2S(vHeadBone);

            FN_VECTOR vRootBone = get_bone(entity.mesh, 0);
            FN_VECTOR vRootBoneOut = W2S(vRootBone);

            FN_VECTOR HeadBox = W2S(FN_VECTOR(vHeadBone.x, vHeadBone.y, vHeadBone.z + 15));
            FN_VECTOR RootBox = W2S(FN_VECTOR(vRootBone.x, vRootBone.y, vRootBone.z));
           
            float distance = pointer::LocalActorPos.Distance(vHeadBone) / 100.f;



            static ImColor ImESPColor;

       
            float BoxHeight = abs(HeadBox.y - vRootBoneOut.y);
            float BoxWidth = BoxHeight * 0.75;



            if (distance < Options::Visuals::MaxESPDrawDistance || Options::Visuals::ESP) {


                if (fisVisible(entity.mesh)) {

                    Options::IsVisible = true;
                    if (!entity.isDBNO) {
                        ImESPColor = ImGui::GetColorU32({ fl_VisibleColor[0],fl_VisibleColor[1],fl_VisibleColor[2],  1.0f });
                    }
                    else {
                        ImESPColor = ImGui::GetColorU32({ downed[1], downed[1], downed[1], 1.0f });
                    }
                   
                }
                else {
                    Options::IsVisible = false;
                    if (!entity.isDBNO) {
                        ImESPColor = ImGui::GetColorU32({ fl_InVisibleColor[0],fl_InVisibleColor[1],fl_InVisibleColor[2],  1.0f });
                    }
                    else {
                        ImESPColor = ImGui::GetColorU32({ downed[1], downed[1], downed[1], 1.0f });
                    }
                }





                if (Options::Visuals::LineESP) {
                    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(width / 2, height / 1), ImVec2(vRootBoneOut.x, vRootBoneOut.y), ImESPColor, 1.f);
                }
                if (Options::Visuals::Radar) {
                    add_players_radar(vRootBone);
                }
              


                if (IsInScreen(vHeadBoneOut))
                {

                    if (Options::Visuals::BoxESP) {
                        draw_cornered_box(HeadBox.x - (BoxWidth / 2), HeadBox.y, BoxWidth, BoxHeight, ImESPColor, Options::BoxThickness);
                    }

                    if (Options::Visuals::CornerBoxESP)
                    {
                        draw_cornered_box2(HeadBox.x - (BoxWidth / 2), HeadBox.y, BoxWidth, BoxHeight, ImESPColor, Options::BoxThickness);
                    }

                    if (Options::Visuals::Distance) {

                        std::string DistanceText = ("(") + std::to_string(int(distance)) + ("m)");
                        ImVec2 DistanceTextSize = ImGui::CalcTextSize(DistanceText.c_str());
                        OutlinedText(vRootBoneOut.x - DistanceTextSize.x / 2, vRootBoneOut.y, IM_COL32(255, 255, 255, 255), DistanceText.c_str());

                    }




                }
            }

            auto dx = vHeadBoneOut.x - (width / 2);
            auto dy = vHeadBoneOut.y - (height / 2);
            auto dist = sqrtf(dx * dx + dy * dy);

            if (dist < Options::Aimbot::fov / camera::fov * 360 && dist < closestDistance) {


                if (Options::Aimbot::SkipKnocked) {
                    if (!entity.isDBNO) {

                        closestDistance = dist;
                        closestPawn = entity.actor;
                    }
                }
                else
                {

                    closestDistance = dist;
                    closestPawn = entity.actor;
                }
            }
            else {

            }
        }

        if (Options::Aimbot::Aimbot && closestPawn && GETKEY(Options::Aimbot::aimkey))
        {
                    auto AimbotMesh = driver.readptr<uint64_t>(closestPawn + Offsets::Mesh);

                    if (fisVisible(AimbotMesh)) {
                        Vector3 HeadPosition;
                        Vector3 Head;


                            if (Options::Aimbot::hitbox == 0)
                            {
                                HeadPosition = get_bone(AimbotMesh, 68);
                            }
                            if (Options::Aimbot::hitbox == 1)
                            {
                                HeadPosition = get_bone(AimbotMesh, 66);
                            }
                            if (Options::Aimbot::hitbox == 2)
                            {
                                HeadPosition = get_bone(AimbotMesh, 6);
                            }
                       

                        Head = W2S(HeadPosition);

                        if (Head.x != 0 || Head.y != 0 || Head.z != 0)
                        {
                                    if ((GetDistance(Head.x, Head.y, Head.z, width / 2, height / 2) <= Options::Aimbot::fov / camera::fov * 360))
                                    {
                                        mouse::mouse(Head.x, Head.y, Options::Aimbot::Smooth);
                                    }
                        }
                    }
        }
        else
        {
            closestDistance = FLT_MAX;
            closestPawn = NULL;
        }

    }



}