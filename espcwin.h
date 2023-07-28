#pragma once

char* drawBuff = (char*)malloc(1024);

typedef struct _ItemBase {
	uint32_t actorscount;
	uint64_t actorsarray;
}_ItemBase;
std::vector<_ItemBase> itemBaseList;

typedef struct _Item {
	uint64_t actor;
	std::string ItemName;
	BYTE bWTier;
	int type;
}_Item;
std::vector<_Item> itemList;
uint64_t AFortPickupAthena = 0;

typedef struct _Entity {
	int type;
	uint64_t actor;
	uint64_t mesh;
	uint64_t currweapon;
	uint64_t playerstate;
}_Entity;
std::vector<_Entity> EntityList;

typedef struct _Ground {
	uint64_t actor;
	int type;
}_Ground;
std::vector<_Ground> GroundList;

static bool isVisible(DWORD_PTR mesh)
{
	float fLastSubmitTime = read<float>(mesh + 0x330);
	float fLastRenderTimeOnScreen = read<float>(mesh + 0x338);
	const float fVisionTick = 0.06f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
	return bVisible;
}
static auto DrawBone(int64_t pMeshAddress, RGBA color, float thickness) -> void
{
	Vector3 vHeadBoneOut, vNeckOut, vPelvisOut;
	Vector3 vUpperArmLeftOut, vLeftHandOut, vlowerarmLeftOut;
	Vector3 vUpperArmRightOut, vLowerarmRightOut, vRightHandOut;
	Vector3 vLeftThighOut, vLeftCalfOut, vLeftLballOut, vLeftFootOut;
	Vector3 vRightThighOut, vRightCalfOut, vRightLballut, vRightFootOut;

	Vector3 vHeadBone = GetBoneWithRotation(pMeshAddress, 68);
	vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
	Vector3 vNeck = GetBoneWithRotation(pMeshAddress, 67);
	vNeckOut = ProjectWorldToScreen(vNeck);
	Vector3 vPelvis = GetBoneWithRotation(pMeshAddress, 2);
	vPelvisOut = ProjectWorldToScreen(vPelvis);

	Vector3 vLeftUpperArm = GetBoneWithRotation(pMeshAddress, 9);
	vUpperArmLeftOut = ProjectWorldToScreen(vLeftUpperArm);
	Vector3 vLeftlowerarm = GetBoneWithRotation(pMeshAddress, 10);
	vlowerarmLeftOut = ProjectWorldToScreen(vLeftlowerarm);
	Vector3 vLeftHand = GetBoneWithRotation(pMeshAddress, 11);
	vLeftHandOut = ProjectWorldToScreen(vLeftHand);

	Vector3 vRightUpperArm = GetBoneWithRotation(pMeshAddress, 38);
	vUpperArmRightOut = ProjectWorldToScreen(vRightUpperArm);
	Vector3 vRightLowerarm = GetBoneWithRotation(pMeshAddress, 39);
	vLowerarmRightOut = ProjectWorldToScreen(vRightLowerarm);
	Vector3 vRightHand = GetBoneWithRotation(pMeshAddress, 40);
	vRightHandOut = ProjectWorldToScreen(vRightHand);

	Vector3 vLeftThigh = GetBoneWithRotation(pMeshAddress, 69);
	vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
	Vector3 vLeftCalf = GetBoneWithRotation(pMeshAddress, 70);
	vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
	Vector3 vLeftFoot = GetBoneWithRotation(pMeshAddress, 73);
	vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
	Vector3 vLeftLball = GetBoneWithRotation(pMeshAddress, 74);
	vLeftLballOut = ProjectWorldToScreen(vLeftLball);

	Vector3 vRightThigh = GetBoneWithRotation(pMeshAddress, 76);
	vRightThighOut = ProjectWorldToScreen(vRightThigh);
	Vector3 vRightCalf = GetBoneWithRotation(pMeshAddress, 77);
	vRightCalfOut = ProjectWorldToScreen(vRightCalf);
	Vector3 vRightFoot = GetBoneWithRotation(pMeshAddress, 80);
	vRightFootOut = ProjectWorldToScreen(vRightFoot);
	Vector3 vRightLball = GetBoneWithRotation(pMeshAddress, 81);
	vRightLballut = ProjectWorldToScreen(vRightLball);

	DrawLine(vNeckOut.x, vNeckOut.y, vHeadBoneOut.x, vHeadBoneOut.y, &color, thickness);
	DrawLine(vPelvisOut.x, vPelvisOut.y, vNeckOut.x, vNeckOut.y, &color, thickness);

	DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &color, thickness);
	DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &color, thickness);

	DrawLine(vlowerarmLeftOut.x, vlowerarmLeftOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &color, thickness);
	DrawLine(vLowerarmRightOut.x, vLowerarmRightOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &color, thickness);

	DrawLine(vLeftHandOut.x, vLeftHandOut.y, vlowerarmLeftOut.x, vlowerarmLeftOut.y, &color, thickness);
	DrawLine(vRightHandOut.x, vRightHandOut.y, vLowerarmRightOut.x, vLowerarmRightOut.y, &color, thickness);

	DrawLine(vLeftThighOut.x, vLeftThighOut.y, vPelvisOut.x, vPelvisOut.y, &color, thickness);
	DrawLine(vRightThighOut.x, vRightThighOut.y, vPelvisOut.x, vPelvisOut.y, &color, thickness);

	DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &color, thickness);
	DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &color, thickness);

	DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &color, thickness);
	DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &color, thickness);

	DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftLballOut.x, vLeftLballOut.y, &color, thickness);
	DrawLine(vRightFootOut.x, vRightFootOut.y, vRightLballut.x, vRightLballut.y, &color, thickness);
}
static auto DrawHead(int64_t pMeshAddress, RGBA color) -> void
{
	Vector3 vHeadBone = GetBoneWithRotation(pMeshAddress, 68);
	Vector3 vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
	float distance_modifier = g_local_relativelocation.Distance(vHeadBoneOut) * 0.001F;
	DrawCircleFilled(vHeadBoneOut.x, vHeadBoneOut.y, 150 / distance_modifier, &color);
}

static double GetCrossDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
static auto move_to(float x, float y) -> void {
	float center_x = (ImGui::GetIO().DisplaySize.x / 2);
	float center_y = (ImGui::GetIO().DisplaySize.y / 2);

	float smooth = aimbot::aimspeed;
	smooth = aimbot2::aimspeed;
	smooth = aimbot3::aimspeed;
	smooth = aimbot4::aimspeed;
	smooth = aimbot5::aimspeed;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	MouseController::Move_Mouse((int)target_x, (int)(target_y));
}

void __cdecl LootCache1(void*)
{
	while (true)
	{
		std::vector<_ItemBase> itemBaseList_tmp;

		auto uworld = read<uint64_t>(globals::imagebase + 0xC640158);
		auto game_instance = read<uint64_t>(uworld + 0x1a8);
		g_local_player_array = read<uint64_t>(read<uint64_t>(game_instance + 0x38));
		auto player_controller = read<uint64_t>(g_local_player_array + 0x30);

		g_local_player_pawn = read<uint64_t>(player_controller + 0x310);
		g_local_rootcomponent = read<uint64_t>(g_local_player_pawn + 0x188);
		g_local_relativelocation = read<Vector3>(g_local_rootcomponent + 0x128);

		auto levelscount = read<uint32_t>(uworld + 0x160 + 0x8);

		for (uint32_t n = 0; n < levelscount; n++)
		{
			auto levels = read<uint64_t>(uworld + 0x160);
			if (!levels) continue;

			auto level = read<uint64_t>(levels + (n * 0x8));
			if (!level) continue;

			auto actorscount = read<uint32_t>(level + 0xA0);
			auto actorsarray = read<uint64_t>(level + 0x98);
			if (!actorsarray) continue;

			_ItemBase baseItem{ };
			baseItem.actorscount = actorscount;
			baseItem.actorsarray = actorsarray;
			itemBaseList_tmp.push_back(baseItem);
		}
		itemBaseList.clear();
		itemBaseList = itemBaseList_tmp;
		Sleep(1000);
	}
}
void __cdecl LootCache2(void*)
{
	while (true)
	{
		std::vector<_Item> itemList_tmp;

		auto uworld = read<uint64_t>(globals::imagebase + 0xC640158);
		auto game_instance = read<uint64_t>(uworld + 0x1a8);
		g_local_player_array = read<uint64_t>(read<uint64_t>(game_instance + 0x38));
		auto player_controller = read<uint64_t>(g_local_player_array + 0x30);

		g_local_player_pawn = read<uint64_t>(player_controller + 0x310);
		g_local_rootcomponent = read<uint64_t>(g_local_player_pawn + 0x188);
		g_local_relativelocation = read<Vector3>(g_local_rootcomponent + 0x128);

		for (unsigned long i = 0; i < itemBaseList.size(); i++)
		{
			for (uint32_t n = 0; n < itemBaseList[i].actorscount; n++)
			{
				auto actor = read<uint64_t>(itemBaseList[i].actorsarray + (n * 0x8));

				auto actorClassPrivate = read<uint64_t>(actor + 0x10);
				if (!AFortPickupAthena) {
					auto pUItemID = read<uint32_t>(actor + 0x18);
					if (!pUItemID) continue;

					auto pObjName = GetNameFromFName(pUItemID);

					if (strstr(pObjName.c_str(), "Fort_Pickup_Creative_C") || strstr(pObjName.c_str(), "FortPickupAthena") && visuals::items)
					{
						AFortPickupAthena = read<uint64_t>(actor + 0x10); // (ClassPrivate)
					}
					else
						continue;
				}

				if (actorClassPrivate == AFortPickupAthena)
				{
					auto item = read<uint64_t>(actor + (0x2f8 + 0x18)); // (PrimaryPickupItemEntry + ItemDefinition)
					if (item)
					{
						auto DisplayName = read<uint64_t>(item + 0x90); // DisplayName (FText)
						auto ItemLength = read<uint32_t>(DisplayName + 0x38); // FText -> Length
						wchar_t* ItemName = new wchar_t[uint64_t(ItemLength) + 1];

						auto shit = read<PVOID>(DisplayName + 0x30);
						ReadProcessMemory((uint64_t)shit, ItemName, ItemLength * sizeof(wchar_t)); // FText -> Name

						std::wstring wItemName(ItemName);
						std::string sItemName(wItemName.begin(), wItemName.end());
						auto bWTier = read<BYTE>(item + 0x74);

						_Item currItem{ };
						currItem.actor = actor;
						currItem.ItemName = sItemName;
						currItem.bWTier = bWTier;
						itemList_tmp.push_back(currItem);
					}
				}
			}
		}
		itemList.clear();
		itemList = itemList_tmp;
		Sleep(1000);
	}
}
void __cdecl EntityCache(void*)
{
	while (true)
	{
		std::vector<_Entity> EntityList_tmp;

		auto uworld = read<uint64_t>(globals::imagebase + 0xC640158);
		auto game_instance = read<uint64_t>(uworld + 0x1a8);
		g_local_player_array = read<uint64_t>(read<uint64_t>(game_instance + 0x38));
		auto player_controller = read<uint64_t>(g_local_player_array + 0x30);

		g_local_player_pawn = read<uint64_t>(player_controller + 0x310);
		g_local_rootcomponent = read<uint64_t>(g_local_player_pawn + 0x188);
		g_local_relativelocation = read<Vector3>(g_local_rootcomponent + 0x128);

		auto persistent_level = read<uint64_t>(uworld + 0x30);
		auto actor_array = read<uint64_t>(persistent_level + 0x98);
		auto actor_count = read<uint32_t>(persistent_level + 0xA0);

		auto player_state = read<int64_t>(g_local_player_pawn + 0x290);
		g_local_team_id = read<int32_t>(player_state + 0x1010);

		g_local_currweapon = read<uint64_t>(g_local_player_pawn + 0x790);

		for (int i = 0; i < actor_count; i++)
		{
			auto actor = read<uint64_t>(actor_array + (i * 0x8));

			auto object_id = read<uint32_t>(actor + 0x18);
			auto pObjName = GetNameFromFName(object_id);

			if (strstr(pObjName.c_str(), "PlayerPawn_Athena_C") || strstr(pObjName.c_str(), "BP_PlayerPawn_Athena_Phoebe_C"))
			{
				auto mesh = read<uint64_t>(actor + 0x2F0);
				auto currweapon = read<uint64_t>(actor + 0x790);
				auto player_state = read<int64_t>(actor + 0x290);

				_Entity currEntity{ };
				currEntity.type = 0;
				currEntity.actor = actor;
				currEntity.mesh = mesh;
				currEntity.currweapon = currweapon;
				currEntity.playerstate = player_state;
				EntityList_tmp.push_back(currEntity);
			}

		}
		EntityList.clear();
		EntityList = EntityList_tmp;
		Sleep(1000);
	}
}
DWORD WINAPI LootCache3(LPVOID lpParam)
{
	while (true)
	{
		std::vector<_Ground> itemList_tmp;

		auto uworld = read<uint64_t>(globals::imagebase + 0xC640158);
		auto game_instance = read<uint64_t>(uworld + 0x1a8);
		g_local_player_array = read<uint64_t>(read<uint64_t>(game_instance + 0x38));
		auto player_controller = read<uint64_t>(g_local_player_array + 0x30);

		g_local_player_pawn = read<uint64_t>(player_controller + 0x338);
		g_local_rootcomponent = read<uint64_t>(g_local_player_pawn + 0x190);
		g_local_relativelocation = read<Vector3>(g_local_rootcomponent + 0x138);

		for (unsigned long i = 0; i < itemBaseList.size(); i++)
		{
			for (uint32_t n = 0; n < itemBaseList[i].actorscount; n++)
			{
				auto actor = read<uint64_t>(itemBaseList[i].actorsarray + (n * 0x8));

				auto pUItemID = read<uint32_t>(actor + 0x18);
				if (!pUItemID) continue;

				auto pObjName = GetNameFromFName(pUItemID);

				if (strstr(pObjName.c_str(), "Tiered_Chest") && (visuals::chest))
				{
					_Ground currItem{ };
					currItem.actor = actor;
					currItem.type = 1;
					itemList_tmp.push_back(currItem);
				}
				else if (strstr(pObjName.c_str(), "Tiered_Ammo") && (visuals::ammobox))
				{
					_Ground currItem{ };
					currItem.actor = actor;
					currItem.type = 2;
					itemList_tmp.push_back(currItem);
				}
				else if (strstr(pObjName.c_str(), "AthenaSupplyDrop_C") && (visuals::supply))
				{
					_Ground currItem{ };
					currItem.actor = actor;
					currItem.type = 3;
					itemList_tmp.push_back(currItem);
				}
				else if (strstr(pObjName.c_str(), "Vehicle_C") && (visuals::vehicle))
				{
					_Ground currItem{ };
					currItem.actor = actor;
					currItem.type = 4;
					itemList_tmp.push_back(currItem);
				}
			}
		}
		//GroundList.clear();
		GroundList = itemList_tmp;
		Sleep(800);
	}
}

void DrawCallback()
{
	RGBA Fov = { colors::fov[0] * 255, colors::fov[1] * 255, colors::fov[2] * 255, 255 };
	RGBA invisible = { colors::invisible[0] * 255, colors::invisible[1] * 255, colors::invisible[2] * 255, 255 };
	RGBA visible = { colors::visible[0] * 255, colors::visible[1] * 255, colors::visible[2] * 255, 255 };
	RGBA RGBAColor;

	uint64_t PawnMesh = read<uint64_t>(g_local_player_pawn + 0x2F0);
	Vector3 pLocalPosition = GetBoneWithRotation(PawnMesh, 68);
	if (_isnanf(pLocalPosition.x) || _isnanf(pLocalPosition.y) || _isnanf(pLocalPosition.z))
	{
		pLocalPosition = { 0.f, 0.f, 0.f };
	}

	auto distance = 0.0;
	bool Visible;

	for (unsigned long i = 0; i < itemList.size(); i++)
	{
		auto entity = itemList[i];
		auto ItemRoot = read<uint64_t>(entity.actor + 0x188);
		auto ItemLocation = read<Vector3>(ItemRoot + 0x128);

		if (pLocalPosition.x != 0.f)
		{
			distance = pLocalPosition.Distance(ItemLocation) / 100;
		}

		if (distance < visuals::ItemDistance)
		{
			auto bWTier = entity.bWTier;
			auto ItemName = entity.ItemName.c_str();

			auto ItemScreenPos = ProjectWorldToScreen(ItemLocation);

			if (visuals::items)
			{
				if (bWTier == 2 && (items::UnCommon))
				{
					RGBAColor = Col.green;
					sprintf(drawBuff, "%s | %0.fm\0", ItemName, distance);
					DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &RGBAColor, true, true, drawBuff);
				}
				else if ((bWTier == 3) && (items::rare))
				{
					RGBAColor = Col.blue;
					sprintf(drawBuff, "%s | %0.fm\0", ItemName, distance);
					DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &RGBAColor, true, true, drawBuff);
				}
				else if ((bWTier == 4) && (items::purple))
				{
					RGBAColor = Col.purple;
					sprintf(drawBuff, "%s | %0.fm\0", ItemName, distance);
					DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &RGBAColor, true, true, drawBuff);
				}
				else if ((bWTier == 5) && (items::gold))
				{
					RGBAColor = Col.yellow;
					sprintf(drawBuff, "%s | %0.fm\0", ItemName, distance);
					DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &RGBAColor, true, true, drawBuff);
				}
				else if ((bWTier == 6) && (items::mythic))
				{
					RGBAColor = Col.yellow;
					sprintf(drawBuff, "%s | %0.fm\0", ItemName, distance);
					DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &RGBAColor, true, true, drawBuff);
				}
				else if ((bWTier == 0) || (bWTier == 1) && (items::Common))
				{
					RGBAColor = Col.white;
					sprintf(drawBuff, "%s | %0.fm\0", ItemName, distance);
					DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &RGBAColor, true, true, drawBuff);
				}
			}
		}
	}
	for (unsigned long i = 0; i < EntityList.size(); i++)
	{
		auto entity = EntityList[i];
		auto actor = entity.actor;

		auto mesh = entity.mesh;
		auto type = entity.type;
		auto currweapon = entity.currweapon;
		auto playerstate = entity.playerstate;

		if (type == 0)
		{
			auto Itemdef = read<uint64_t>(currweapon + 0x3d8);
			auto isReloading = read<bool>(currweapon + 0x311);
			auto AmmoCount = read<int32_t>(currweapon + 0xb24);

			auto WeaponID = read<uint32_t>(Itemdef + 0x18);
			auto TeamNumber = read<int32_t>(playerstate + 0x1010);

			Visible = isVisible(mesh);

			auto foot = GetBoneWithRotation(mesh, 0);
			auto head = GetBoneWithRotation(mesh, 68);

			auto player_screen = ProjectWorldToScreen(foot);
			auto head_screen = ProjectWorldToScreen(Vector3(head.x, head.y + 0.3, head.z));
			auto normal_head = ProjectWorldToScreen(head);

			auto rootcomponent = read<uint64_t>(entity.actor + 0x188);
			auto root_position = read<Vector3>(rootcomponent + 0x128);
			if (head.z <= root_position.z) {
				continue;
			}

			if (pLocalPosition.x != 0.f)
			{
				distance = pLocalPosition.Distance(foot) / 100;
			}

			auto local_Itemdef = read<uint64_t>(g_local_currweapon + 0x3d8);
			auto pawnWeaponID = read<uint32_t>(local_Itemdef + 0x18);
			std::string pObjName = GetNameFromFName(pawnWeaponID);

			auto dx = normal_head.x - (globals::width / 2);
			auto dy = normal_head.y - (globals::height / 2);
			auto dist = sqrtf(dx * dx + dy * dy);

			bool bIsCrouched = read<bool>(g_local_player_pawn + 0x3f0);
			bool bIsTargeting = read<bool>(g_local_currweapon + 0xa85);

			float BoxHeight = player_screen.y - head_screen.y;
			float BoxWidth = BoxHeight / 1.8f;

			if (TeamNumber != g_local_team_id)
			{
				RGBA box{ Visible ? visible : invisible };

				if (pObjName.find("Assault") != std::string::npos
					|| pObjName.find("Boss") != std::string::npos
					|| pObjName.find("Launcher") != std::string::npos
					|| pObjName.find("Bow") != std::string::npos
					|| pObjName.find("Rifle") != std::string::npos
					|| pObjName.find("Pistol") != std::string::npos)
				{
					if (bIsTargeting)
					{
						if (aimbot::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot::adsfov, &Fov, 100);
						}
					}
					else {
						if (aimbot::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot::aimfov, &Fov, 100);
						}
					}

					if (bIsCrouched)
						aimbot::hipfire = aimbot::hipfire;
					else
						aimbot::aimspeed = aimbot::aimspeed;

					if (bIsTargeting)
						aimbot::adsfov = aimbot::adsfov;
					else
						aimbot::aimfov = aimbot::aimfov;

					if (aimbot::aimbot)
					{
						if (dist < aimbot::aimfov && dist < closestDistance && targetlocked == false && Visible) {

							if (distance <= aimbot::aimdistance)
							{
								closestDistance = dist;
								closestPawn = entity.actor;
							}
						}
					}
				}
				if (pObjName.find("Shotgun") != std::string::npos)
				{

					if (bIsTargeting)
					{
						if (aimbot2::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot2::adsfov, &Fov, 100);
						}
					}
					else {
						if (aimbot2::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot2::aimfov, &Fov, 100);
						}
					}

					if (bIsCrouched)
						aimbot2::hipfire = aimbot2::hipfire;
					else
						aimbot2::aimspeed = aimbot2::aimspeed;

					if (bIsTargeting)
						aimbot2::adsfov = aimbot2::adsfov;
					else
						aimbot2::aimfov = aimbot2::aimfov;

					if (aimbot2::aimbot)
					{
						if (dist < aimbot2::aimfov && dist < closestDistance && targetlocked == false && Visible) {

							if (distance <= aimbot2::aimdistance) {
								closestDistance = dist;
								closestPawn = entity.actor;
							}
						}
					}
				}
				if (pObjName.find("SMG") != std::string::npos)
				{
					if (bIsTargeting)
					{
						if (aimbot3::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot3::adsfov, &Fov, 100);
						}
					}
					else {
						if (aimbot3::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot3::aimfov, &Fov, 100);
						}
					}

					if (bIsCrouched)
						aimbot3::hipfire = aimbot3::hipfire;
					else
						aimbot3::aimspeed = aimbot3::aimspeed;

					if (bIsTargeting)
						aimbot3::adsfov = aimbot3::adsfov;
					else
						aimbot3::aimfov = aimbot3::aimfov;

					if (aimbot3::aimbot) {
						if (dist < aimbot3::aimfov && dist < closestDistance && targetlocked == false && Visible) {
							if (distance <= aimbot3::aimdistance) {
								closestDistance = dist;
								closestPawn = entity.actor;
							}
						}
					}
				}
				if (pObjName.find("Sniper") != std::string::npos)
				{
					if (bIsTargeting)
					{
						if (aimbot5::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot5::adsfov, &Fov, 100);
						}
					}
					else {
						if (aimbot5::fovcircle) {
							DrawCircle(ImGui::GetIO().DisplaySize.x / 2.f, ImGui::GetIO().DisplaySize.y / 2.f, aimbot5::aimfov, &Fov, 100);
						}
					}

					if (bIsCrouched)
						aimbot5::hipfire = aimbot5::hipfire;
					else
						aimbot5::aimspeed = aimbot5::aimspeed;

					if (bIsTargeting)
						aimbot5::adsfov = aimbot5::adsfov;
					else
						aimbot5::aimfov = aimbot5::aimfov;

					if (aimbot5::aimbot) {
						if (dist < aimbot5::aimfov && dist < closestDistance && targetlocked == false && Visible) {
							if (distance <= aimbot5::aimdistance) {
								closestDistance = dist;
								closestPawn = entity.actor;
							}
						}
					}
				}

				if (distance < visuals::MaxSkeletonDrawDistance)
				{
					if (visuals::skeleton)
					{
						float distance_modifier = pLocalPosition.Distance(foot) * 0.001F;
						DrawCircleFilled(normal_head.x, normal_head.y, 10 / distance_modifier, &box);

						DrawBone(mesh, box, 2);
					}
				}
				if (distance < visuals::MaxDistance)
				{
					if (visuals::box)
					{
						if (visuals::boxMode == 0 || visuals::boxMode == 1)
						{
							if (visuals::outline)
							{
								DrawNormalBox(player_screen.x - BoxWidth / 2 + 1, head_screen.y, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
								DrawNormalBox(player_screen.x - BoxWidth / 2 - 1, head_screen.y, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
								DrawNormalBox(player_screen.x - BoxWidth / 2, head_screen.y + 1, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
								DrawNormalBox(player_screen.x - BoxWidth / 2, head_screen.y - 1, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
							}
							DrawNormalBox(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, thickness::box_thick, &box);
						}
						if (visuals::boxMode == 2 || visuals::boxMode == 3)
						{
							if (visuals::outline)
							{
								DrawCornerBox(player_screen.x - BoxWidth / 2 + 1, head_screen.y, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
								DrawCornerBox(player_screen.x - BoxWidth / 2 - 1, head_screen.y, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
								DrawCornerBox(player_screen.x - BoxWidth / 2, head_screen.y + 1, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
								DrawCornerBox(player_screen.x - BoxWidth / 2, head_screen.y - 1, BoxWidth, BoxHeight, thickness::box_thick, &Col.black);
							}
							DrawCornerBox(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, thickness::box_thick, &box);
						}

						if (visuals::boxMode == 1 || visuals::boxMode == 3)  thickness::box_thick = 1,
							DrawFilledRect(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, &Col.filled);
					}
					if (visuals::lines)
					{
						if (visuals::lineMode == 0)
							DrawLine(globals::width / 2, globals::height, player_screen.x, player_screen.y, &box, 1.5f);
						if (visuals::lineMode == 1)
							DrawLine(globals::width / 2, 0.f, player_screen.x, player_screen.y, &box, 1.5f);
						if (visuals::lineMode == 2)
							DrawLine(globals::width / 2, globals::height / 2, player_screen.x, player_screen.y, &box, 1.5f);
					}
					if (visuals::weapon)
					{
						if (isReloading)
						{
							sprintf(drawBuff, "Reloading...");
							DrawString(14, player_screen.x, player_screen.y + 65, &Col.white_, true, true, drawBuff);
						}
						else
						{
							if (WeaponID > 0)
							{
								std::string pObjName = GetNameFromFName(WeaponID);
								sprintf(drawBuff, "%s", pObjName.c_str());
								DrawString(14, player_screen.x, player_screen.y + 65, &Col.white_, true, true, drawBuff);
							}
							else
							{
								sprintf(drawBuff, "%s", "NULL");
								DrawString(14, player_screen.x, player_screen.y + 65, &Col.white_, true, true, drawBuff);
							}
						}
					}

					if (visuals::ammo)
					{
						sprintf(drawBuff, "Ammo : %d", AmmoCount);
						DrawString(14, player_screen.x, player_screen.y + 43.0f, &Col.white_, true, true, drawBuff);
					}

					if (visuals::teamid)
					{
						sprintf(drawBuff, "TeamID : %.2d", TeamNumber);
						DrawString(14, player_screen.x, player_screen.y + 55.0f, &Col.white_, true, true, drawBuff);
					}
					if (visuals::name)
					{
						sprintf(drawBuff, "%0.fm\0", distance);
						DrawString(14, player_screen.x, player_screen.y + 33.0f, &Col.white_, true, true, drawBuff);
					}
				}
			}
		}
	}
	/*for (unsigned long i = 0; i < GroundList.size(); i++)
	{
		auto entity = GroundList[i];
		auto actor = entity.actor;

		auto ItemRoot = read<uint64_t>(entity.actor + 0x138);
		auto ItemLocation = read<Vector3>(ItemRoot + 0x11c);
		auto ItemScreenPos = ProjectWorldToScreen(ItemLocation);

		if (pLocalPosition.x != 0.f)
		{
			distance = pLocalPosition.Distance(ItemLocation) / 100;
		}

		if (entity.type == 1 && (visuals::chest))
		{
			if (distance < visuals::ChestDistance)
			{
				sprintf(drawBuff, "Chest | %0.fm\0", distance);
				DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &Col.white, true, true, drawBuff);
			}
		}
		else if (entity.type == 2 && (visuals::ammobox))
		{
			if (distance < visuals::AmmoDistance)
			{
				sprintf(drawBuff, "AmmoBox | %0.fm\0", distance);
				DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &Col.white, true, true, drawBuff);
			}
		}
		else if (entity.type == 3 && (visuals::supply))
		{
			if (distance < visuals::SupplyDistance)
			{
				sprintf(drawBuff, "SupplyBox | %0.fm\0", distance);
				DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &Col.white, true, true, drawBuff);
			}
		}
		else if (entity.type == 4 && (visuals::vehicle))
		{
			if (distance < visuals::VehicleDistance)
			{
				sprintf(drawBuff, "Vehicle | %0.fm\0", distance);
				DrawString(14, ItemScreenPos.x, ItemScreenPos.y, &Col.white, true, true, drawBuff);
			}
		}
	}*/

	if (g_local_player_pawn)
	{
		if (closestPawn != 0)
		{
			if (aimbot::aimbot && closestPawn && MouseController::GetAsyncKeyState(hotkeys::aimkey))
			{
				targetlocked = true;
				Visible = true;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;


				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot::aimfov)) {
						if (Distance <= aimbot::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
							move_to(rootHeadOut.x, rootHeadOut.y);
						}

					}
				}
			}
			else
			{
				isaimbotting = false;
				targetlocked = false;
				Visible = false;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;

				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot::aimfov)) {
						if (Distance <= aimbot::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
						}
					}
				}
				closestDistance = FLT_MAX;
				closestPawn = NULL;
			}
			if (aimbot2::aimbot && closestPawn && MouseController::GetAsyncKeyState(hotkeys2::aimkey2))
			{
				targetlocked = true;
				Visible = true;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;


				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot2::aimfov)) {
						if (Distance <= aimbot2::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
							move_to(rootHeadOut.x, rootHeadOut.y);
						}

					}
				}
			}
			else
			{
				isaimbotting = false;
				targetlocked = false;
				Visible = false;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;

				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot2::aimfov)) {
						if (Distance <= aimbot2::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
						}
					}
				}
				closestDistance = FLT_MAX;
				closestPawn = NULL;
			}
			if (aimbot3::aimbot && closestPawn && MouseController::GetAsyncKeyState(hotkeys3::aimkey3))
			{
				targetlocked = true;
				Visible = true;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;


				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot3::aimfov)) {
						if (Distance <= aimbot3::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
							move_to(rootHeadOut.x, rootHeadOut.y);
						}
					}
				}
			}
			else
			{
				isaimbotting = false;
				targetlocked = false;
				Visible = false;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;

				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot3::aimfov)) {
						if (Distance <= aimbot3::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
						}
					}
				}
				closestDistance = FLT_MAX;
				closestPawn = NULL;
			}
			if (aimbot4::aimbot && closestPawn && MouseController::GetAsyncKeyState(hotkeys4::aimkey4))
			{
				targetlocked = true;
				Visible = true;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;


				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot4::aimfov)) {
						if (Distance <= aimbot4::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
							move_to(rootHeadOut.x, rootHeadOut.y);
						}
					}
				}
			}
			else
			{
				isaimbotting = false;
				targetlocked = false;
				Visible = false;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;

				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot4::aimfov)) {
						if (Distance <= aimbot4::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
						}
					}
				}
				closestDistance = FLT_MAX;
				closestPawn = NULL;
			}
			if (aimbot5::aimbot && closestPawn && MouseController::GetAsyncKeyState(hotkeys5::aimkey5))
			{
				targetlocked = true;
				Visible = true;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;

				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot5::aimfov)) {
						if (Distance <= aimbot5::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
							move_to(rootHeadOut.x, rootHeadOut.y);
						}
					}
				}
			}
			else
			{
				isaimbotting = false;
				targetlocked = false;
				Visible = false;

				uint64_t currentactormesh = read<uint64_t>(closestPawn + 0x2F0);
				auto rootHead = GetBoneWithRotation(currentactormesh, select_hitbox());
				Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

				uint64_t rootcomponent = read<uint64_t>(closestPawn + 0x188);
				Vector3 Relativelocation = read<Vector3>(rootcomponent + 0x128);
				float Distance = pLocalPosition.Distance(Relativelocation) / 100;

				if (rootHeadOut.x != 0 || rootHeadOut.y != 0) {
					if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, globals::width / 2, globals::height / 2) <= aimbot5::aimfov)) {
						if (Distance <= aimbot5::aimdistance) {
							DrawLine(globals::width / 2, globals::height / 2, rootHeadOut.x, rootHeadOut.y, &Fov, 1.f);
						}
					}
				}
				closestDistance = FLT_MAX;
				closestPawn = NULL;
			}
		}
	}
}
