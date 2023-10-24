#pragma once
#include "..\OS-ImGui\imgui\imgui.h"
#include "..\MenuConfig.hpp"

namespace CheatList
{
	static inline void CheatText(const char* Cheat, bool config)
	{
		if (config)
			ImGui::Text(Cheat);
	}

	inline void Render() noexcept
	{
		if (MenuConfig::CheatList) {

			ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
			ImGui::SetNextWindowBgAlpha(0.3f);
			ImGui::SetNextWindowSize(ImVec2(200, 0));
			ImGui::Begin("Active Features", nullptr, windowFlags);

			CheatText("Aimbot", MenuConfig::AimBot);
			CheatText("Triggerbot", MenuConfig::TriggerBot);
			CheatText("Radar", MenuConfig::ShowRadar);
			CheatText("Bone Esp", MenuConfig::ShowBoneESP);
			CheatText("Box Esp", MenuConfig::ShowBoxESP);
			CheatText("Health Bar", MenuConfig::ShowHealthBar);
			CheatText("Health Text", MenuConfig::HealthText);
			CheatText("Weapon Text", MenuConfig::ShowWeaponESP);
			CheatText("Distance Text", MenuConfig::ShowDistance);
			CheatText("Enemy LOS", MenuConfig::ShowEyeRay);
			CheatText("Name Esp", MenuConfig::ShowPlayerName);
			CheatText("Spectate Esp", MenuConfig::SpectateEsp);
			CheatText("Aimbot Fov", MenuConfig::ShowAimFovRange);
			CheatText("Aimbot Visible Check", MenuConfig::VisibleCheck);
			CheatText("Team Check", MenuConfig::TeamCheck);
			CheatText("SnapLines", MenuConfig::ShowLineToEnemy);

			CheatText("Crosshair", MenuConfig::ShowCrossHair);
			CheatText("Crosshair Dot", CrosshairConfig::drawDot);
			CheatText("Crosshair T Style", CrosshairConfig::tStyle);
			CheatText("Crosshair Outline", CrosshairConfig::drawOutLine);
			CheatText("Headshot Line", MenuConfig::ShowHeadShootLine);
			CheatText("WaterMark", MenuConfig::WaterMark);
			CheatText("OBS Bypass", MenuConfig::OBSBypass);
		}
		ImGui::End();
	}
}