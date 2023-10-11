#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>
#include <map>
#include "Entity.h"


namespace PreviewESP
{
void ESP_Preview(ImVec2 window_pos)
    {
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();

        // Preview Size
        float preview_width = 200.0f;
        float preview_height = 400.0f;
        ImVec2 preview_center(window_pos.x + preview_width / 2, window_pos.y + preview_height / 2);

        // Bounding Box
        float box_width = 60.0f;
        float box_height = 120.0f;
        ImVec2 box_top_left(preview_center.x - box_width / 2, preview_center.y - box_height / 2);
        ImVec2 box_bottom_right(preview_center.x + box_width / 2, preview_center.y + box_height / 2);
        draw_list->AddRect(box_top_left, box_bottom_right, IM_COL32(255, 0, 0, 255)); // Red color

        // Health Bar
        float health_bar_width = 10.0f;
        float health_bar_height = 120.0f;
        ImVec2 health_bar_pos(box_top_left.x - 15.0f, box_top_left.y);
        draw_list->AddRectFilled(health_bar_pos, ImVec2(health_bar_pos.x + health_bar_width, health_bar_pos.y + health_bar_height), IM_COL32(0, 128, 0, 255)); // Green color

        // Headshot Indicator
        ImVec2 headshot_pos(box_top_left.x + box_width / 2, box_top_left.y + 10.0f);
        draw_list->AddCircleFilled(headshot_pos, 5.0f, IM_COL32(255, 255, 0, 255)); // Yellow color

        // Draw Text indicating it's a preview
        draw_list->AddText(preview_center, IM_COL32(255, 255, 255, 255), "ESP Preview");
    }

    void ShowESP_PreviewMenu()
    {
        if (ImGui::Begin("ESP Preview Menu"))
        {
            ImVec2 window_pos = ImGui::GetWindowPos();
            ESP_Preview(window_pos);
        }
        ImGui::End();
    }
}