#include "ConfigMenu.hpp"
#include "../MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include "../TriggerBot.hpp"
#include "../AimBot.hpp"
#include <filesystem>
#include <Shlobj.h>
#include <iostream>

namespace ConfigMenu {

	void RenderConfigMenu() {
		// Config
		ImGui::Text("-Config-");
		static char configNameBuffer[128] = "";

		ImGui::InputText("New Config Name", configNameBuffer, sizeof(configNameBuffer));

		if (ImGui::Button("Create Config"))
		{
			std::string configFileName = std::string(configNameBuffer) + ".config";
			MyConfigSaver::SaveConfig(configFileName);
		}

		ImGui::Separator();

		static int selectedConfig = -1;

		TCHAR documentsPath[MAX_PATH];
		if (SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documentsPath) != S_OK) {
			return;
		}

		char narrowPath[MAX_PATH];
		if (WideCharToMultiByte(CP_UTF8, 0, documentsPath, -1, narrowPath, sizeof(narrowPath), NULL, NULL) == 0) {
			return;
		}

		std::string documentsDir(narrowPath);
		std::string configFilePath = documentsDir + "\\.Aeonix\\";
		static std::vector<std::string> configFiles;

		configFiles.clear();
		for (const auto& entry : std::filesystem::directory_iterator(configFilePath))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".config")
			{
				configFiles.push_back(entry.path().filename().string());
			}
		}

		for (int i = 0; i < configFiles.size(); ++i)
		{
			if (ImGui::Selectable(configFiles[i].c_str(), selectedConfig == i))
			{
				selectedConfig = i;
			}
		}

		if (selectedConfig != -1)
		{
			ImGui::Text("Selected: %s", configFiles[selectedConfig].c_str());
		}

		if (ImGui::Button("Load Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
		{
			std::string selectedConfigFile = configFiles[selectedConfig];
			MyConfigSaver::LoadConfig(selectedConfigFile);
		}
		
		ImGui::SameLine();

		if (ImGui::Button("Save Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			ImGui::OpenPopup("##reallySave");

		if (ImGui::BeginPopup("##reallySave"))
		{
			ImGui::TextUnformatted("Are you sure?");
			if (ImGui::Button("No", { 45.0f, 0.0f }))
				ImGui::CloseCurrentPopup();
			ImGui::SameLine();
			if (ImGui::Button("Yes", { 45.0f, 0.0f }))
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::SaveConfig(selectedConfigFile);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::Separator();

		if (ImGui::Button("Delete Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			ImGui::OpenPopup("##reallyDelete");

		if (ImGui::BeginPopup("##reallyDelete"))
		{
			ImGui::TextUnformatted("Are you sure?");
			if (ImGui::Button("No", { 45.0f, 0.0f }))
				ImGui::CloseCurrentPopup();
			ImGui::SameLine();
			if (ImGui::Button("Yes", { 45.0f, 0.0f }))
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				std::string fullPath = configFilePath + "/" + selectedConfigFile;
				if (std::remove(fullPath.c_str()) == 0)
				{
					configFiles.erase(configFiles.begin() + selectedConfig);
					selectedConfig = -1;
				}
				else
				{
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		namespace fs = std::filesystem;

		ImGui::SameLine();

		if (ImGui::Button("Reset Config"))
			ImGui::OpenPopup("##reallyReset");
		if (ImGui::BeginPopup("##reallyReset"))
		{
			ImGui::TextUnformatted("Are you sure?");
			if (ImGui::Button("No", { 45.0f, 0.0f }))
				ImGui::CloseCurrentPopup();
			ImGui::SameLine();
			if (ImGui::Button("Yes", { 45.0f, 0.0f }))
			{
				ConfigMenu::ResetToDefault();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();

		if (ImGui::Button("Open Directory")) {
			fs::path dirPath(configFilePath);

			if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
				std::string pathString = dirPath.string();

				std::string command = "explorer.exe " + pathString;
				int result = std::system(command.c_str());
			}
		}
	}

	void ResetToDefault() {
		MenuConfig::ShowBoneESP = true;
		MenuConfig::SpectateEsp = false;
		MenuConfig::ShowBoxESP = true;
		MenuConfig::ShowHealthBar = true;
		MenuConfig::ShowWeaponESP = true;
		MenuConfig::ShowEyeRay = true;
		MenuConfig::ShowPlayerName = true;
		MenuConfig::AimBot = true;
		MenuConfig::AimPosition = 0;
		MenuConfig::AimPositionIndex = BONEINDEX::head;
		MenuConfig::BoxType = 0;
		MenuConfig::HealthBarType = 0;
		MenuConfig::BoneColor = ImVec4(255, 255, 255, 255);
		MenuConfig::BoxColor = ImVec4(255, 255, 255, 255);
		MenuConfig::EyeRayColor = ImVec4(255, 0, 0, 255);
		MenuConfig::ShowMenu = true;
		MenuConfig::ShowRadar = true;
		MenuConfig::RadarRange = 150;
		MenuConfig::ShowRadarCrossLine = true;
		MenuConfig::RadarCrossLineColor = ImVec4(34, 34, 34, 180);
		MenuConfig::RadarType = 2;
		MenuConfig::RadarPointSizeProportion = 1.f;
		MenuConfig::Proportion = 2230;
		MenuConfig::TriggerBot = true;
		MenuConfig::TeamCheck = true;
		MenuConfig::VisibleCheck = true;
		MenuConfig::ShowHeadShootLine = true;
		MenuConfig::HeadShootLineColor = ImVec4(255, 255, 255, 255);
		MenuConfig::AimBotHotKey = 0;
		AimControl::SetHotKey(MenuConfig::AimBotHotKey);
		MenuConfig::ShowLineToEnemy = false;
		MenuConfig::FovLineSize = 60.0f;
		TriggerBot::TriggerDelay = 90;
		AimControl::RCSBullet = 1;
		MenuConfig::TriggerHotKey = 0;
		TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
		AimControl::RCSScale = ImVec2(1.2f, 1.4f);
		MenuConfig::FovLineColor = ImVec4(55, 55, 55, 220);
		MenuConfig::LineToEnemyColor = ImVec4(255, 255, 255, 220);
		MenuConfig::ShowCrossHair = true;
		MenuConfig::CrossHairColor = ImColor(45, 45, 45, 255);
		MenuConfig::CrossHairSize = 150;
		MenuConfig::RadarBgAlpha = 0.3f;
		MenuConfig::ShowAimFovRange = true;
		MenuConfig::AimFovRangeColor = ImColor(230, 230, 230, 255);
		MenuConfig::OBSBypass = true;
		MenuConfig::BunnyHop = false;
		MenuConfig::BunnyHop2 = false;
		MenuConfig::ShowDistance = true;
	}
}