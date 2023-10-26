#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include <iostream>
#include "View.hpp"

extern "C" {
#include "Mouse.h"
#include "Entity.h"
}

namespace AimControl
{

    inline int HotKey = VK_RBUTTON;
    inline float AimFov = 5;
    inline float Smooth = 0.7;
    inline Vec2 RCSScale = { 1.f,1.f };
    inline int RCSBullet = 1;
    inline std::vector<int> HotKeyList{ VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };

    inline void SetHotKey(int Index)
    {
        HotKey = HotKeyList.at(Index);
    }

    inline void AimBot(const CEntity& Local, Vec3 LocalPos, Vec3 AimPos)
    {
        float Yaw, Pitch;
        float Distance, Norm;
        Vec3 OppPos;

        OppPos = AimPos - LocalPos;

        Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

        Yaw = atan2f(OppPos.y, OppPos.x) * 57.295779513 - Local.Pawn.ViewAngle.y;
        Pitch = -atan(OppPos.z / Distance) * 57.295779513 - Local.Pawn.ViewAngle.x;
        Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));
        if (Norm > AimFov)
            return;

        Yaw = Yaw * 2 - Smooth + Local.Pawn.ViewAngle.y;
        Pitch = Pitch * 2 - Smooth + Local.Pawn.ViewAngle.x;

        Vec2 ScreenPos;
        if (gGame.View.WorldToScreen(Vec3(AimPos), ScreenPos))
        {
            /*ScreenPos.x /= Smooth;
            ScreenPos.y /= Smooth;*/
            // use logitech-cve for mouse move
            mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE,
                (ScreenPos.x * (65535 / GetSystemMetrics(SM_CXSCREEN))),
                (ScreenPos.y * (65535 / GetSystemMetrics(SM_CYSCREEN))),
                0, 0);

            std::cout << "[Pitch:]" << Pitch << "\n";
            std::cout << "[Yaw: ]" << Yaw << "\n";
            std::cout << "[mouse x:] " << (int)ScreenPos.x << "\n";
            std::cout << "[mouse y:] " << (int)ScreenPos.y << "\n";
            Sleep(1);
        }
    }
}