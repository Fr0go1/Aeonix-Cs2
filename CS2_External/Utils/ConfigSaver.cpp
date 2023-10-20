#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ConfigSaver.hpp"
#include "../MenuConfig.hpp"
#include "../TriggerBot.hpp"
#include "../AimBot.hpp"
#include <Shlobj.h>
#include <filesystem>

namespace MyConfigSaver {

    void SaveConfig(const std::string& filename) {
        TCHAR documentsPath[MAX_PATH];
        if (SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documentsPath) != S_OK) {
            std::cerr << "Error: Could not retrieve the Documents directory path." << std::endl;
            return;
        }

        char narrowPath[MAX_PATH];
        if (WideCharToMultiByte(CP_UTF8, 0, documentsPath, -1, narrowPath, sizeof(narrowPath), NULL, NULL) == 0) {
            std::cerr << "Error: Could not convert wide character path to narrow character path." << std::endl;
            return;
        }

        std::string documentsDir(narrowPath);
        std::string configFilePath = documentsDir + "\\.Aeonix\\" + filename;

        std::ofstream configFile(configFilePath);
        if (!configFile.is_open()) {
            std::cerr << "Error: Could not open the configuration file." << std::endl;
            return;
        }

        // Example: Save global settings to the file
        configFile << "ShowBoneESP " << MenuConfig::ShowBoneESP << std::endl;
        configFile << "VisibleEsp " << MenuConfig::VisibleEsp << std::endl;
        configFile << "HealthText " << MenuConfig::HealthText << std::endl;
        configFile << "SpectateEsp " << MenuConfig::SpectateEsp << std::endl;
        configFile << "MinTriggerDelay " << TriggerBot::MinDelay << std::endl;
        configFile << "MaxTriggerDelay " << TriggerBot::MaxDelay << std::endl;
        configFile << "ShowBoxESP " << MenuConfig::ShowBoxESP << std::endl;
        configFile << "TriggerHotKey " << MenuConfig::TriggerHotKey << std::endl;
        configFile << "RCSBullet " << AimControl::RCSBullet << std::endl;
        configFile << "ShowHealthBar " << MenuConfig::ShowHealthBar << std::endl;
        configFile << "AimFov " << AimControl::AimFov << std::endl;
        configFile << "FovLineSize " << MenuConfig::FovLineSize << std::endl;
        configFile << "AimBotHotKey " << MenuConfig::AimBotHotKey << std::endl;
        configFile << "ShowLineToEnemy " << MenuConfig::ShowLineToEnemy << std::endl;
        configFile << "RCSScale.x " << AimControl::RCSScale.x << std::endl;
        configFile << "RCSScale.y " << AimControl::RCSScale.y << std::endl;
        configFile << "ShowWeaponESP " << MenuConfig::ShowWeaponESP << std::endl;
        configFile << "Smooth " << AimControl::Smooth << std::endl;
        configFile << "ShowFovLine " << MenuConfig::ShowFovLine << std::endl;
        configFile << "ShowEyeRay " << MenuConfig::ShowEyeRay << std::endl;
        configFile << "ShowPlayerName " << MenuConfig::ShowPlayerName << std::endl;
        configFile << "AimBot " << MenuConfig::AimBot << std::endl;
        configFile << "AimPosition " << MenuConfig::AimPosition << std::endl;
        configFile << "AimPositionIndex " << MenuConfig::AimPositionIndex << std::endl;
        configFile << "HealthBarType " << MenuConfig::HealthBarType << std::endl;
        configFile << "BoneColor " << MenuConfig::BoneColor.Value.x << " " << MenuConfig::BoneColor.Value.y << " " << MenuConfig::BoneColor.Value.z << " " << MenuConfig::BoneColor.Value.w << std::endl;
        configFile << "BoneVisColor " << MenuConfig::BoneVisColor.Value.x << " " << MenuConfig::BoneVisColor.Value.y << " " << MenuConfig::BoneVisColor.Value.z << " " << MenuConfig::BoneVisColor.Value.w << std::endl;
        configFile << "FovLineColor " << MenuConfig::FovLineColor.Value.x << " " << MenuConfig::FovLineColor.Value.y << " " << MenuConfig::FovLineColor.Value.z << " " << MenuConfig::FovLineColor.Value.w << std::endl;
        configFile << "LineToEnemyColor " << MenuConfig::LineToEnemyColor.Value.x << " " << MenuConfig::LineToEnemyColor.Value.y << " " << MenuConfig::LineToEnemyColor.Value.z << " " << MenuConfig::LineToEnemyColor.Value.w << std::endl;
        configFile << "BoxColor " << MenuConfig::BoxColor.Value.x << " " << MenuConfig::BoxColor.Value.y << " " << MenuConfig::BoxColor.Value.z << " " << MenuConfig::BoxColor.Value.w << std::endl;
        configFile << "EyeRayColor " << MenuConfig::EyeRayColor.Value.x << " " << MenuConfig::EyeRayColor.Value.y << " " << MenuConfig::EyeRayColor.Value.z << " " << MenuConfig::EyeRayColor.Value.w << std::endl;
        configFile << "RadarCrossLineColor " << MenuConfig::RadarCrossLineColor.Value.x << " " << MenuConfig::RadarCrossLineColor.Value.y << " " << MenuConfig::RadarCrossLineColor.Value.z << " " << MenuConfig::RadarCrossLineColor.Value.w << std::endl;
        configFile << "HeadShootLineColor " << MenuConfig::HeadShootLineColor.Value.x << " " << MenuConfig::HeadShootLineColor.Value.y << " " << MenuConfig::HeadShootLineColor.Value.z << " " << MenuConfig::HeadShootLineColor.Value.w << std::endl;
        configFile << "ShowMenu " << MenuConfig::ShowMenu << std::endl;
        configFile << "ShowRadar " << MenuConfig::ShowRadar << std::endl;
        configFile << "RadarRange " << MenuConfig::RadarRange << std::endl;
        configFile << "RadarPointSizeProportion " << MenuConfig::RadarPointSizeProportion << std::endl;
        configFile << "ShowCrossLine " << MenuConfig::ShowRadarCrossLine << std::endl;
        configFile << "RadarType " << MenuConfig::RadarType << std::endl;
        configFile << "Proportion " << MenuConfig::Proportion << std::endl;
        configFile << "BoxType " << MenuConfig::BoxType << std::endl;
        configFile << "TriggerBot " << MenuConfig::TriggerBot << std::endl;
        configFile << "TeamCheck " << MenuConfig::TeamCheck << std::endl;
        configFile << "VisibleCheck " << MenuConfig::VisibleCheck << std::endl;
        configFile << "ShowHeadShootLine " << MenuConfig::ShowHeadShootLine << std::endl;
        configFile << "ShowCrossHair " << MenuConfig::ShowCrossHair << std::endl;
        configFile << "CrossHairColor " << CrosshairConfig::CrossHairColor.Value.x << " " << CrosshairConfig::CrossHairColor.Value.y << " " << CrosshairConfig::CrossHairColor.Value.z << " " << CrosshairConfig::CrossHairColor.Value.w << std::endl;
        configFile << "CrossHairSize " << CrosshairConfig::CrossHairSize << std::endl;
        configFile << "drawDot " << CrosshairConfig::drawDot << std::endl;
        configFile << "tStyle " << CrosshairConfig::tStyle << std::endl;
        configFile << "HorizontalLength " << CrosshairConfig::HorizontalLength << std::endl;
        configFile << "VerticalLength " << CrosshairConfig::VerticalLength << std::endl;
        configFile << "drawOutLine " << CrosshairConfig::drawOutLine << std::endl;
        configFile << "Gap " << CrosshairConfig::Gap << std::endl;
        configFile << "ShowAimFovRange " << MenuConfig::ShowAimFovRange << std::endl;
        configFile << "AimFovRangeColor " << MenuConfig::AimFovRangeColor.Value.x << " " << MenuConfig::AimFovRangeColor.Value.y << " " << MenuConfig::AimFovRangeColor.Value.z << " " << MenuConfig::AimFovRangeColor.Value.w << std::endl;
        configFile << "VisibleColor " << MenuConfig::VisibleColor.Value.x << " " << MenuConfig::VisibleColor.Value.y << " " << MenuConfig::VisibleColor.Value.z << " " << MenuConfig::VisibleColor.Value.w << std::endl;
        configFile << "OBSBypass " << MenuConfig::OBSBypass << std::endl;
        configFile << "ShowDistance " << MenuConfig::ShowDistance << std::endl;
        configFile << "RadarBgAlpha " << MenuConfig::RadarBgAlpha << std::endl;
        configFile << "Style " << MenuConfig::styleee << std::endl;
        configFile << "StyleIndex " << MenuConfig::selectedStyleIndex << std::endl;
        configFile << "EspVisCheck " << MenuConfig::EspVisCheck << std::endl;
        configFile.close();
        std::cout << "Configuration saved to " << filename << std::endl;
    }

    void LoadConfig(const std::string& filename) {
        TCHAR documentsPath[MAX_PATH];
        if (SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documentsPath) != S_OK) {
            std::cerr << "Error: Could not retrieve the Documents directory path." << std::endl;
            return;
        }

        char narrowPath[MAX_PATH];
        if (WideCharToMultiByte(CP_UTF8, 0, documentsPath, -1, narrowPath, sizeof(narrowPath), NULL, NULL) == 0) {
            std::cerr << "Error: Could not convert wide character path to narrow character path." << std::endl;
            return;
        }

        std::string documentsDir(narrowPath);
        std::string configFilePath = documentsDir + "\\.Aeonix\\" + filename;

        std::ifstream configFile(configFilePath);
        if (!configFile.is_open()) {
            std::cerr << "Error: Could not open the configuration file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key;
            if (iss >> key) {
                if (key == "ShowBoneESP") iss >> MenuConfig::ShowBoneESP;
                else if (key == "VisibleEsp") iss >> MenuConfig::VisibleEsp;
                else if (key == "HealthText") iss >> MenuConfig::HealthText;
                else if (key == "SpectateEsp") iss >> MenuConfig::SpectateEsp;
                else if (key == "MinTriggerDelay") iss >> TriggerBot::MinDelay;
                else if (key == "MaxTriggerDelay") iss >> TriggerBot::MaxDelay;
                else if (key == "ShowBoxESP") iss >> MenuConfig::ShowBoxESP;
                else if (key == "TriggerHotKey") { iss >> MenuConfig::TriggerHotKey; TriggerBot::SetHotKey(MenuConfig::TriggerHotKey); }
                else if (key == "RCSBullet") iss >> AimControl::RCSBullet;
                else if (key == "ShowHealthBar") iss >> MenuConfig::ShowHealthBar;
                else if (key == "AimFov") iss >> AimControl::AimFov;
                else if (key == "FovLineSize") iss >> MenuConfig::FovLineSize;
                else if (key == "AimBotHotKey") { iss >> MenuConfig::AimBotHotKey; AimControl::SetHotKey(MenuConfig::AimBotHotKey); }
                else if (key == "ShowLineToEnemy") iss >> MenuConfig::ShowLineToEnemy;
                else if (key == "RCSScale.x") iss >> AimControl::RCSScale.x;
                else if (key == "RCSScale.y") iss >> AimControl::RCSScale.y;
                else if (key == "ShowWeaponESP") iss >> MenuConfig::ShowWeaponESP;
                else if (key == "Smooth") iss >> AimControl::Smooth;
                else if (key == "ShowFovLine") iss >> MenuConfig::ShowFovLine;
                else if (key == "ShowEyeRay") iss >> MenuConfig::ShowEyeRay;
                else if (key == "ShowPlayerName") iss >> MenuConfig::ShowPlayerName;
                else if (key == "AimBot") iss >> MenuConfig::AimBot;
                else if (key == "AimPosition") iss >> MenuConfig::AimPosition;
                else if (key == "AimPositionIndex") iss >> MenuConfig::AimPositionIndex;
                else if (key == "HealthBarType") iss >> MenuConfig::HealthBarType;
                else if (key == "BoneColor") iss >> MenuConfig::BoneColor.Value.x >> MenuConfig::BoneColor.Value.y >> MenuConfig::BoneColor.Value.z >> MenuConfig::BoneColor.Value.w;
                else if (key == "BoneVisColor") iss >> MenuConfig::BoneVisColor.Value.x >> MenuConfig::BoneVisColor.Value.y >> MenuConfig::BoneVisColor.Value.z >> MenuConfig::BoneVisColor.Value.w;
                else if (key == "FovLineColor") iss >> MenuConfig::FovLineColor.Value.x >> MenuConfig::FovLineColor.Value.y >> MenuConfig::FovLineColor.Value.z >> MenuConfig::FovLineColor.Value.w;
                else if (key == "LineToEnemyColor") iss >> MenuConfig::LineToEnemyColor.Value.x >> MenuConfig::LineToEnemyColor.Value.y >> MenuConfig::LineToEnemyColor.Value.z >> MenuConfig::LineToEnemyColor.Value.w;
                else if (key == "BoxColor") iss >> MenuConfig::BoxColor.Value.x >> MenuConfig::BoxColor.Value.y >> MenuConfig::BoxColor.Value.z >> MenuConfig::BoxColor.Value.w;
                else if (key == "EyeRayColor") iss >> MenuConfig::EyeRayColor.Value.x >> MenuConfig::EyeRayColor.Value.y >> MenuConfig::EyeRayColor.Value.z >> MenuConfig::EyeRayColor.Value.w;
                else if (key == "RadarCrossLineColor") iss >> MenuConfig::RadarCrossLineColor.Value.x >> MenuConfig::RadarCrossLineColor.Value.y >> MenuConfig::RadarCrossLineColor.Value.z >> MenuConfig::RadarCrossLineColor.Value.w;
                else if (key == "HeadShootLineColor") iss >> MenuConfig::HeadShootLineColor.Value.x >> MenuConfig::HeadShootLineColor.Value.y >> MenuConfig::HeadShootLineColor.Value.z >> MenuConfig::HeadShootLineColor.Value.w;
                else if (key == "ShowMenu") iss >> MenuConfig::ShowMenu;
                else if (key == "ShowRadar") iss >> MenuConfig::ShowRadar;
                else if (key == "RadarRange") iss >> MenuConfig::RadarRange;
                else if (key == "RadarPointSizeProportion") iss >> MenuConfig::RadarPointSizeProportion;
                else if (key == "ShowCrossLine") iss >> MenuConfig::ShowRadarCrossLine;
                else if (key == "RadarType") iss >> MenuConfig::RadarType;
                else if (key == "Proportion") iss >> MenuConfig::Proportion;
                else if (key == "BoxType") iss >> MenuConfig::BoxType;
                else if (key == "TriggerBot") iss >> MenuConfig::TriggerBot;
                else if (key == "TeamCheck") iss >> MenuConfig::TeamCheck;
                else if (key == "VisibleCheck") iss >> MenuConfig::VisibleCheck;
                else if (key == "ShowHeadShootLine") iss >> MenuConfig::ShowHeadShootLine;
                else if (key == "ShowCrossHair") iss >> MenuConfig::ShowCrossHair;
                else if (key == "CrossHairColor") iss >> CrosshairConfig::CrossHairColor.Value.x >> CrosshairConfig::CrossHairColor.Value.y >> CrosshairConfig::CrossHairColor.Value.z >> CrosshairConfig::CrossHairColor.Value.w;
                else if (key == "CrossHairSize") iss >> CrosshairConfig::CrossHairSize;
                else if (key == "drawDot") iss >> CrosshairConfig::drawDot;
                else if (key == "tStyle") iss >> CrosshairConfig::tStyle;
                else if (key == "HorizontalLength") iss >> CrosshairConfig::HorizontalLength;
                else if (key == "VerticalLength") iss >> CrosshairConfig::VerticalLength;
                else if (key == "drawOutLine") iss >> CrosshairConfig::drawOutLine;
                else if (key == "Gap") iss >> CrosshairConfig::Gap;
                else if (key == "ShowAimFovRange") iss >> MenuConfig::ShowAimFovRange;
                else if (key == "AimFovRangeColor") iss >> MenuConfig::AimFovRangeColor.Value.x >> MenuConfig::AimFovRangeColor.Value.y >> MenuConfig::AimFovRangeColor.Value.z >> MenuConfig::AimFovRangeColor.Value.w;
                else if (key == "VisibleColor") iss >> MenuConfig::VisibleColor.Value.x >> MenuConfig::VisibleColor.Value.y >> MenuConfig::VisibleColor.Value.z >> MenuConfig::VisibleColor.Value.w;
                else if (key == "OBSBypass") iss >> MenuConfig::OBSBypass;
                else if (key == "ShowDistance") iss >> MenuConfig::ShowDistance;
                else if (key == "RadarBgAlpha") iss >> MenuConfig::RadarBgAlpha;
                else if (key == "StyleIndex") iss >> MenuConfig::selectedStyleIndex;
                else if (key == "EspVisCheck") iss >> MenuConfig::EspVisCheck;
            }
        }

        configFile.close();
        std::cout << "Configuration loaded from " << filename << std::endl;
    }
} // namespace ConfigSaver