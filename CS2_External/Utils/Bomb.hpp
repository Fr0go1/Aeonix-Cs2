#pragma once
#include "..\MenuConfig.hpp"
#include "..\Entity.h"
#include "..\View.hpp"
/*
namespace BombShit
{
    void DrawC4PlantedBorderBox(const CEntity& localPlayer, const CEntity& plantedC4, const CView& viewMatrix)
    {
        // Check if C4 is planted
        DWORD64 c4IsPlanted = ProcessMgr.ReadMemory<DWORD64>(BaseClient::base + GlobalVar.dwPlantedC4 - 0x8);
        if (c4IsPlanted)
        {
            DWORD64 plantedC4Node = ProcessMgr.ReadMemory<DWORD64>(ProcessMgr.ReadMemory<DWORD64>(BaseClient::base + GlobalVar.dwPlantedC4) + GlobalVar.m_pGameSceneNode);
            Vec3 c4Origin = ProcessMgr.ReadMemory<Vec3>(plantedC4Node + GlobalVar.m_vecAbsOrigin);

            Vec2 c4ScreenPos;
            if (viewMatrix.WorldToScreen(c4Origin, c4ScreenPos))
            {
                float distance = localPlayer.GetAbsOrigin().CalculateDistance(c4Origin);
                float roundedDistance = std::round(distance / 500.f);

                float height = 10 - roundedDistance;
                float width = height * 1.2f;
                float boxX = c4ScreenPos.x - width / 2;
                float boxY = c4ScreenPos.y - height / 2;

                render::DrawBorderBox(
                    g::hdcBuffer,
                    boxX,
                    boxY,
                    width,
                    height,
                    RGB(0, 185, 255)
                );
            }
        }
    }

    void RunBombShit(const CEntity& localPlayer, const CEntity& entities, const CView& viewMatrix)
    {
        DrawC4PlantedBorderBox(localPlayer, entities, viewMatrix);
    }
}*/