#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "Utils/ConfigMenu.hpp"
#include "Utils/ConfigSaver.hpp"
#include "Utils/style.hpp"
#include "font/IconsFontAwesome5.h"
#include "TriggerBot.hpp"
#include "AimBot.hpp"
#include <Windows.h>
#include <cmath>
#include "Utils/keys.cpp"
#include <thread>

static void HotKey(int* k, const ImVec2& size_arg = ImVec2(0, 0))
{
	static bool waitingforkey = false;
	if (waitingforkey == false) {
		if (ImGui::Button(KeyNames[*k], size_arg))
			waitingforkey = true;
	}
	else if (waitingforkey == true) {
		ImGui::Button("...", size_arg);
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		for (auto& Key : KeyCodes)
		{
			if (GetAsyncKeyState(Key)) {
				*k = Key;
				waitingforkey = false;
			}
		}
	}
}

void Cheats::Menu()
{
	static int tabb = 0;
	//ImGui::ShowMetricsWindow();

	ImGui::SetNextWindowSize(ImVec2(625, 645));

	ImGui::Begin("Aeonix",nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	{
		if (ImGui::BeginChild(1, ImVec2(115, 600), true)) {

			if (MenuConfig::styleee == 3) {
				SetupImGuiStyle1();
			}
			else if (MenuConfig::styleee == 2) {
				SetupImGuiStyle2();
			}
			else if (MenuConfig::styleee == 1) {
				SetupImGuiStyle3();
			}

			if (ImGui::Button(ICON_FA_EYE, ImVec2(100, 48))) {
				tabb = 0;
			}
			ImGui::Spacing();
			if (ImGui::Button(ICON_FA_USER_CIRCLE, ImVec2(100, 48))) {
				tabb = 1;
			}
			ImGui::Spacing();
			if (ImGui::Button(ICON_FA_FILE_CODE, ImVec2(100, 48))) {
				tabb = 2;
			}
			ImGui::Spacing();
			if (ImGui::Button(ICON_FA_HAND_POINTER, ImVec2(100, 48))) {
				tabb = 3;
			}
			ImGui::Spacing();
			if (ImGui::Button(ICON_FA_FOLDER_OPEN, ImVec2(100, 48))) {
				tabb = 4;
			}
			ImGui::Spacing();
			if (ImGui::Button(ICON_FA_SUN, ImVec2(100, 48))) {
				tabb = 5;
			}
		}
		ImGui::EndChild();

		ImGui::SameLine();

		if (ImGui::BeginChild(2, ImVec2(485, 600), true)) {

			if (tabb == 0) {
				//esp
				ImGui::Text("-Visuals-");

				ImGui::Checkbox("BoxESP", &MenuConfig::ShowBoxESP);
				ImGui::SameLine();
				ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();

				if (ImGui::Button("VisCheck (Box)"))
					ImGui::OpenPopup("##boxvis");

				if (ImGui::BeginPopup("##boxvis"))
				{
					ImGui::TextUnformatted("Box Settings");
					ImGui::Checkbox("VisibleBoxESP", &MenuConfig::EspVisCheck);
					ImGui::SameLine();
					ImGui::ColorEdit4("##BoxVisColor", reinterpret_cast<float*>(&MenuConfig::VisibleColor), ImGuiColorEditFlags_NoInputs);
					ImGui::EndPopup();
				}

				ImGui::Combo("BoxType", &MenuConfig::BoxType, "Normal\0Dynamic");

				ImGui::Checkbox("BoneESP", &MenuConfig::ShowBoneESP);
				ImGui::SameLine();
				ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&MenuConfig::BoneColor), ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();

				if (ImGui::Button("VisCheck (Bone)"))
					ImGui::OpenPopup("##bonevis");

				if (ImGui::BeginPopup("##bonevis"))
				{
					ImGui::TextUnformatted("Bone Settings");
					ImGui::Checkbox("VisibleBoneESP", &MenuConfig::VisibleEsp);
					ImGui::SameLine();
					ImGui::ColorEdit4("##BoneVisColor", reinterpret_cast<float*>(&MenuConfig::BoneVisColor), ImGuiColorEditFlags_NoInputs);
					ImGui::EndPopup();
				}

				ImGui::Checkbox("EyeRay", &MenuConfig::ShowEyeRay);
				ImGui::SameLine();
				ImGui::ColorEdit4("##EyeRay", reinterpret_cast<float*>(&MenuConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);

				ImGui::Checkbox("HealthBar", &MenuConfig::ShowHealthBar);
				ImGui::Combo("HealthBarType", &MenuConfig::HealthBarType, "Vetical\0Horizontal");

				ImGui::Checkbox("WeaponText", &MenuConfig::ShowWeaponESP);
				ImGui::Checkbox("PlayerName", &MenuConfig::ShowPlayerName);

				ImGui::Checkbox("HeadShootLine", &MenuConfig::ShowHeadShootLine);
				ImGui::SameLine();
				ImGui::ColorEdit4("##HeadShootLineColor", reinterpret_cast<float*>(&MenuConfig::HeadShootLineColor), ImGuiColorEditFlags_NoInputs);

				ImGui::Checkbox("FovLine", &MenuConfig::ShowFovLine);
				ImGui::SameLine();
				ImGui::ColorEdit4("##FovLineColor", reinterpret_cast<float*>(&MenuConfig::FovLineColor), ImGuiColorEditFlags_NoInputs);
				float FovLineSizeMin = 20.f, FovLineSizeMax = 120.f;
				Gui.SliderScalarEx1("FovLineSize", ImGuiDataType_Float, &MenuConfig::FovLineSize, &FovLineSizeMin, &FovLineSizeMax, "%.1f", ImGuiSliderFlags_None);

				ImGui::Checkbox("LineToEnemy", &MenuConfig::ShowLineToEnemy);
				ImGui::SameLine();
				ImGui::ColorEdit4("##LineToEnemyColor", reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);

				ImGui::Checkbox("CrossHair", &MenuConfig::ShowCrossHair);
				ImGui::SameLine();
				ImGui::ColorEdit4("##CrossHairColor", reinterpret_cast<float*>(&CrosshairConfig::CrossHairColor), ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine();
				if (ImGui::Button("Settings"))
					ImGui::OpenPopup("##Settings");
				if (ImGui::BeginPopup("##Settings"))
				{
					ImGui::TextUnformatted("Settings");
					ImGui::Checkbox("Center Dot", &CrosshairConfig::drawDot);
					ImGui::SliderInt("Horizontal Length", &CrosshairConfig::HorizontalLength, 0, 75, "%d");
					ImGui::SliderInt("Vertical Length", &CrosshairConfig::VerticalLength, 0, 75, "%d");
					ImGui::SliderInt("Gap", &CrosshairConfig::Gap, 0, 35, "%d");
					ImGui::Checkbox("Outline", &CrosshairConfig::drawOutLine);
					ImGui::Checkbox("T Style", &CrosshairConfig::tStyle);
					ImGui::EndPopup();
				}

				ImGui::Checkbox("Distance Esp", &MenuConfig::ShowDistance);
				ImGui::Checkbox("Health Text", &MenuConfig::HealthText);
				ImGui::Text("[INSERT] HideMenu");

			}
			else if (tabb == 1) {
				//aimbot
				ImGui::Text("-Aimbot-");

				ImGui::Checkbox("AimBot", &MenuConfig::AimBot);
				ImGui::SameLine();
				HotKey(&AimControl::HotKey, ImVec2(95, 28));

				if (ImGui::Combo("AimKey", &MenuConfig::AimBotHotKey, "MENU\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
				{
					AimControl::SetHotKey(MenuConfig::AimBotHotKey);
				}

				float FovMin = 0.1f, FovMax = 89.f;
				float SmoothMin = 0.1f, SmoothMax = 1.f;
				Gui.SliderScalarEx1("AimFov", ImGuiDataType_Float, &AimControl::AimFov, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);
				ImGui::Checkbox("FovCircle", &MenuConfig::ShowAimFovRange);
				ImGui::SameLine();
				ImGui::ColorEdit4("##FovCircleColor", reinterpret_cast<float*>(&MenuConfig::AimFovRangeColor), ImGuiColorEditFlags_NoInputs);
				Gui.SliderScalarEx1("Smooth", ImGuiDataType_Float, &AimControl::Smooth, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);
				if (ImGui::Combo("AimPos", &MenuConfig::AimPosition, "Head\0Neck\0Spine"))
				{
					switch (MenuConfig::AimPosition)
					{
					case 0:
						MenuConfig::AimPositionIndex = BONEINDEX::head;
						break;
					case 1:
						MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
						break;
					case 2:
						MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
						break;
					default:
						break;
					}
				}
				float BulletMin = 1, BulletMax = 6;
				float RecoilMin = 0.f, RecoilMax = 2.f;
				Gui.SliderScalarEx1("Start Bullet", ImGuiDataType_U32, &AimControl::RCSBullet, &BulletMin, &BulletMax, "%1.f", ImGuiSliderFlags_None);
				Gui.SliderScalarEx1("RCS Yaw", ImGuiDataType_Float, &AimControl::RCSScale.x, &RecoilMin, &RecoilMax, "%.1f", ImGuiSliderFlags_None);
				Gui.SliderScalarEx1("RCS Pitch", ImGuiDataType_Float, &AimControl::RCSScale.y, &RecoilMin, &RecoilMax, "%.1f", ImGuiSliderFlags_None);
				ImGui::Checkbox("VisibleCheck", &MenuConfig::VisibleCheck);
				ImGui::Text("[INSERT] HideMenu");
			}
			else if (tabb == 2) {
				//radar
				ImGui::Text("-Misc-");
				ImGui::Checkbox("Radar", &MenuConfig::ShowRadar);
				ImGui::Combo("RadarType", &MenuConfig::RadarType, "Circle\0Arrow\0CircleWithArrow");

				ImGui::Checkbox("CrossLine", &MenuConfig::ShowRadarCrossLine);
				ImGui::SameLine();
				ImGui::ColorEdit4("##CrossLineColor", reinterpret_cast<float*>(&MenuConfig::RadarCrossLineColor), ImGuiColorEditFlags_NoInputs);

				float ProportionMin = 500.f, ProportionMax = 3300.f;
				float RadarRangeMin = 100.f, RadarRangeMax = 300.f;
				float RadarBgAlphaMin = 0.0f, RadarBgAlphaMax = 1.0f;
				float RadarPointSizeProportionMin = 0.8f, RadarPointSizeProportionMax = 2.f;
				Gui.SliderScalarEx1("PointSize", ImGuiDataType_Float, &MenuConfig::RadarPointSizeProportion, &RadarPointSizeProportionMin, &RadarPointSizeProportionMax, "%.1f", ImGuiSliderFlags_None);
				Gui.SliderScalarEx1("Proportion", ImGuiDataType_Float, &MenuConfig::Proportion, &ProportionMin, &ProportionMax, "%.1f", ImGuiSliderFlags_None);
				Gui.SliderScalarEx1("RadarRange", ImGuiDataType_Float, &MenuConfig::RadarRange, &RadarRangeMin, &RadarRangeMax, "%.1f", ImGuiSliderFlags_None);
				Gui.SliderScalarEx1("RadarBgAlpha", ImGuiDataType_Float, &MenuConfig::RadarBgAlpha, &RadarBgAlphaMin, &RadarBgAlphaMax, "%.3f", ImGuiSliderFlags_None);

				ImGui::Checkbox("Bunnyhop", &MenuConfig::BunnyHop);
				ImGui::SameLine();
				ImGui::Checkbox("Bunnyhop 2", &MenuConfig::BunnyHop2);
				ImGui::Text("[INSERT] HideMenu");
			}
			else if (tabb == 3) {
				//triggerbot
				ImGui::Text("-Triggerbot-");

				ImGui::Checkbox("TriggerBot", &MenuConfig::TriggerBot);
				ImGui::SameLine();
				HotKey(&TriggerBot::HotKey, ImVec2(95, 28));

				if (ImGui::Combo("Triggerbot Key", &MenuConfig::TriggerHotKey, "MENU\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
				{
					TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
				}

				DWORD MinTriggerDelayMin = 10, MinTriggerDelayMax = 300;
				DWORD MaxTriggerDelayMin = 10, MaxTriggerDelayMax = 600;
				Gui.SliderScalarEx1("MinDelay", ImGuiDataType_U32, &TriggerBot::MinDelay, &MinTriggerDelayMin, &MinTriggerDelayMax, "%d", ImGuiSliderFlags_None);
				Gui.SliderScalarEx1("MaxDelay", ImGuiDataType_U32, &TriggerBot::MaxDelay, &MaxTriggerDelayMin, &MaxTriggerDelayMax, "%d", ImGuiSliderFlags_None);
				ImGui::Text("[INSERT] HideMenu");
			}
			else if (tabb == 4) {
				//config
				ConfigMenu::RenderConfigMenu();
				ImGui::Text("[INSERT] HideMenu");
			}
			else if (tabb == 5) {
				ImGui::Combo("Select Style", &MenuConfig::selectedStyleIndex, "Purple\0Future Dark\0Peach\0");
				switch (MenuConfig::selectedStyleIndex) {
				case 0:
					MenuConfig::styleee = 1;
					break;
				case 1:
					MenuConfig::styleee = 2;
					break;
				case 2:
					MenuConfig::styleee = 3;
					break;
				}
				ImGui::Checkbox("TeamCheck", &MenuConfig::TeamCheck);
				ImGui::SameLine();
				ImGui::Checkbox("BypassOBS", &MenuConfig::OBSBypass);
				ImGui::SameLine();
				ImGui::Checkbox("Spectate Esp", &MenuConfig::SpectateEsp);
				if (ImGui::Button("Discord")) {
					std::system("cmd.exe /c start https://discord.gg/2b66kqG2nK");
				}
				ImGui::Text("[INSERT] HideMenu");
			}
		}

		ImGui::EndChild();
	}
	ImGui::End();
}

void Cheats::RadarSetting(Base_Radar& Radar)
{
	ImGui::SetNextWindowBgAlpha(MenuConfig::RadarBgAlpha);

	// Radar window
	ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowSize({ MenuConfig::RadarRange * 2,MenuConfig::RadarRange * 2 });

	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + MenuConfig::RadarRange, ImGui::GetWindowPos().y + MenuConfig::RadarRange });
	Radar.SetProportion(MenuConfig::Proportion);
	Radar.SetRange(MenuConfig::RadarRange);
	Radar.SetSize(MenuConfig::RadarRange * 2);
	Radar.SetCrossColor(MenuConfig::RadarCrossLineColor);

	Radar.ArcArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.ArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.CircleSize *= MenuConfig::RadarPointSizeProportion;

	Radar.ShowCrossLine = MenuConfig::ShowRadarCrossLine;
	Radar.Opened = true;
}

void Cheats::RenderCrossHair(ImDrawList* drawList) noexcept
{
	if (!MenuConfig::ShowCrossHair)
		return;

	Render::DrawCrossHair(drawList, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGui::ColorConvertFloat4ToU32(CrosshairConfig::CrossHairColor));
}

void Cheats::Run()
{
	// Show menu
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(VK_INSERT)
		&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		// Check key state per 150ms once to avoid loop.
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		LastTimePoint = CurTimePoint;
	}

	if (MenuConfig::ShowMenu)
		Menu();

	// Update matrix
	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// LocalEntity
	CEntity LocalEntity;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;

	if (MenuConfig::SpectateEsp) {
		if (!LocalEntity.UpdatePawn(LocalPawnAddress));
	}
	else
	{
		if (!LocalEntity.UpdatePawn(LocalPawnAddress))
			return;
	}

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	// Radar Data
	Base_Radar Radar;
	if (MenuConfig::ShowRadar)
		RadarSetting(Radar);

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		static int LocalPlayerControllerIndex = 1;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
			continue;
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;

		if (!Entity.IsAlive())
			continue;

		// Add entity to radar
		if (MenuConfig::ShowRadar)
			Radar.AddPoint(LocalEntity.Pawn.Pos, LocalEntity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), MenuConfig::RadarType, Entity.Pawn.ViewAngle.y);

		if (!Entity.IsInScreen())
			continue;

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });


		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;
			// From: https://github.com/redbg/CS2-Internal/blob/fc8e64430176a62f8800b7467884806708a865bb/src/include/Cheats.hpp#L129
			if (!MenuConfig::VisibleCheck ||
				Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) ||
				LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}

		// Draw Bone
		if (MenuConfig::ShowBoneESP) {
			Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);

			//visible bone esp
			if (MenuConfig::VisibleEsp) {
				if ((Entity.Pawn.bSpottedByMask & (DWORD64(1) << LocalPlayerControllerIndex)) ||
					(LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << i))) {
					Render::DrawBone(Entity, MenuConfig::BoneVisColor, 1.3);
				}
				else {
					Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);
				}
			}
			else if (!MenuConfig::VisibleCheck) {
				Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);
			}
		}

		// Draw eyeRay
		if (MenuConfig::ShowEyeRay)
			Render::ShowLosLine(Entity, 50, MenuConfig::EyeRayColor, 1.3);

		// Box
		ImVec4 Rect;
		switch (MenuConfig::BoxType)
		{
		case 0:
			Rect = Render::Get2DBox(Entity);
			break;
		case 1:
			Rect = Render::Get2DBoneRect(Entity);
			break;
		default:
			break;
		}

		// Line to enemy
		if (MenuConfig::ShowLineToEnemy)
			Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);

		// Draw Box
		if (MenuConfig::ShowBoxESP) {
			Gui.Rectangle({ Rect.x, Rect.y }, { Rect.z, Rect.w }, { 0, 0, 0, 255 }, 3);
			//Box Vis Check
			if (MenuConfig::EspVisCheck) {
				if ((Entity.Pawn.bSpottedByMask & (DWORD64(1) << LocalPlayerControllerIndex)) ||
					(LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << i))) {
					Gui.Rectangle({ Rect.x, Rect.y }, { Rect.z, Rect.w }, MenuConfig::VisibleColor, 1.3);
				}
				else {
					Gui.Rectangle({ Rect.x, Rect.y }, { Rect.z, Rect.w }, MenuConfig::BoxColor, 1.3);
				}
			}
			else {
				Gui.Rectangle({ Rect.x, Rect.y }, { Rect.z, Rect.w }, MenuConfig::BoxColor, 1.3);
			}
		}

		// Draw HealthBar
		if (MenuConfig::ShowHealthBar)
		{
			ImVec2 HealthBarPos, HealthBarSize;
			if (MenuConfig::HealthBarType == 0)
			{
				// Vertical
				HealthBarPos = { Rect.x - 7.f,Rect.y };
				HealthBarSize = { 7 ,Rect.w };
			}
			else
			{
				// Horizontal
				HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
				HealthBarSize = { 70,8 };
			}
			Render::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
		}

		if (MenuConfig::ShowDistance)
		{
			int distance = static_cast<int>(Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) / 100);
			char buffer[0x48];
			sprintf_s(buffer, "%im", distance);
			std::string dis_str = buffer;
			Gui.StrokeText(dis_str, { Rect.x + Rect.z + 4, Rect.y }, ImColor(255, 255, 255, 255), 12, false);
		}

		if (MenuConfig::HealthText)
		{
			std::string yourString = std::to_string(Entity.Pawn.Health);
			Gui.StrokeText(yourString, { Rect.x + Rect.z + 4, Rect.y + 10 }, ImColor(255, 255, 255, 255), 12, false);
		}

		// Draw weaponName
		if (MenuConfig::ShowWeaponESP)
			Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 12);

		if (MenuConfig::ShowPlayerName)
		{
			if (MenuConfig::HealthBarType == 0)
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 12, true);
			else
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 12, true);
		}
	}

	// Fov line
	if (MenuConfig::ShowFovLine)
		Render::DrawFov(LocalEntity, MenuConfig::FovLineSize, MenuConfig::FovLineColor, 1);

	// Radar render
	if (MenuConfig::ShowRadar)
	{
		Radar.Render();
		//End for radar window
		ImGui::End();
	}

	// HeadShoot Line
	if (MenuConfig::ShowHeadShootLine)
		Render::HeadShootLine(LocalEntity, MenuConfig::HeadShootLineColor);

	if (MenuConfig::ShowCrossHair) {
		RenderCrossHair(ImGui::GetBackgroundDrawList());
	}

	// Fov circle
	if (MenuConfig::ShowAimFovRange)
		Render::DrawFovCircle(LocalEntity);

	if (MenuConfig::BunnyHop)
		Bunnyhop::Run(LocalEntity);

	if (MenuConfig::BunnyHop2)
		Bunnyhop2::Run(LocalEntity);

	// TriggerBot
	if (MenuConfig::TriggerBot && GetAsyncKeyState(TriggerBot::HotKey))
	{
		TriggerBot::Run(LocalEntity);
	}

	if (MenuConfig::AimBot && GetAsyncKeyState(AimControl::HotKey))
	{
		if (AimPos != Vec3(0, 0, 0))
		{
			AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
		}
	}
}
