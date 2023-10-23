#pragma once
#include "..\OS-ImGui\imgui\imgui.h"
#include "GlobalVars.hpp"
#include "..\MenuConfig.hpp"
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <chrono>
#include <ctime>

namespace Watermark
{
    inline float watermarkalpha = 0.35f;

	inline void Render() noexcept
	{
        if (MenuConfig::WaterMark) {

            globalvars GV;
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
            ImGui::SetNextWindowBgAlpha(Watermark::watermarkalpha);
            ImGui::Begin("Aeonix-Watermark", nullptr, windowFlags);

            static auto FrameRate = 1.0f;
            FrameRate = 0.9f * FrameRate + 0.1f * GV.GetFrameCount();

            //cheat name
            if (MenuConfig::watermarkcheat)
                ImGui::Text("Aeonix");
            ImGui::SameLine();
            if (MenuConfig::watermarkcheat && (MenuConfig::watermarkuser || MenuConfig::watermarkfps || MenuConfig::watermarktime))
                ImGui::Text("|");
            ImGui::SameLine();

            //username
            DWORD buffer_size = 256;
            wchar_t username[256];

            if (GetUserName(username, &buffer_size)) {
                char narrowUsername[256];
                size_t charsConverted = 0;
                if (wcstombs_s(&charsConverted, narrowUsername, sizeof(narrowUsername), username, _TRUNCATE) == 0) {
                    if (MenuConfig::watermarkuser)
                        ImGui::Text(narrowUsername);
                }
            }
            ImGui::SameLine();
            if (MenuConfig::watermarkuser && (MenuConfig::watermarkfps || MenuConfig::watermarktime))
                ImGui::Text("|");
            ImGui::SameLine();

            //fps
            if (MenuConfig::watermarkfps)
                ImGui::Text("%d fps", FrameRate != 0.0f ? static_cast<int>(1 / FrameRate) : 0);
            ImGui::SameLine();
            if (MenuConfig::watermarkfps && MenuConfig::watermarktime)
                ImGui::Text("|");
            ImGui::SameLine();

            //time
            const auto now = std::chrono::system_clock::now();
            const auto in_time_t = std::chrono::system_clock::to_time_t(now);
            std::tm localTime;
            if (localtime_s(&localTime, &in_time_t) == 0) {
                if (MenuConfig::watermarktime) {
                    ImGui::Text("%02d:%02d:%02d", localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
                }
            }
        }


		ImGui::End();
	}
}