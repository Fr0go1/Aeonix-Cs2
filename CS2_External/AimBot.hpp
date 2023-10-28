#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include <iostream>
#include "View.hpp"

namespace AimControl
{

    inline int HotKey = VK_LBUTTON;
    inline float AimFov = 5;
    inline float Smooth = 0.7;
    inline Vec2 RCSScale = { 1.f,1.f };
    inline int RCSBullet = 1;
    inline std::vector<int> HotKeyList{ VK_LMENU, VK_LBUTTON,VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };

    inline void SetHotKey(int Index)
    {
        HotKey = HotKeyList.at(Index);
    }

    inline void AimBot(const CEntity& Local, Vec3 LocalPos, Vec3 AimPos)
    {
        float Yaw, Pitch;
        float Distance, Norm;
        Vec3 OppPos;
        int ScreenCenterX = Gui.Window.Size.x / 2;
        int ScreenCenterY = Gui.Window.Size.y / 2;
        float TargetX = 0;
        float TargetY = 0;

        OppPos = AimPos - LocalPos;

        Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

        Yaw = (Local.Pawn.ViewAngle.y - (Gui.Window.Size.y / 2));
        Pitch = (Local.Pawn.ViewAngle.x - (Gui.Window.Size.y / 2));
        Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));

        Yaw = Yaw * 2 - Smooth + Local.Pawn.ViewAngle.y;
        Pitch = Pitch * 2 - Smooth + Local.Pawn.ViewAngle.x;

        Vec2 ScreenPos;
        gGame.View.WorldToScreen(Vec3(AimPos), ScreenPos);
        if (Norm > AimFov)
        {
            if (ScreenPos.x > ScreenCenterX)
            {
                TargetX = -(ScreenCenterX - ScreenPos.x);
                TargetX /= Smooth;
                if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
            }
            if (ScreenPos.x < ScreenCenterX)
            {
                TargetX = ScreenPos.x - ScreenCenterX;
                TargetX /= Smooth;
                if (TargetX + ScreenCenterX < 0) TargetX = 0;
            }
            if (ScreenPos.y != 0)
            {
                if (ScreenPos.y > ScreenCenterY)
                {
                    TargetY = -(ScreenCenterY - ScreenPos.y);
                    TargetY /= Smooth;
                    if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
                }

                if (ScreenPos.y < ScreenCenterY)
                {
                    TargetY = ScreenPos.y - ScreenCenterY;
                    TargetY /= Smooth;
                    if (TargetY + ScreenCenterY < 0) TargetY = 0;
                }
            }
            if (!Smooth)
            {
                mouse_event(MOUSEEVENTF_MOVE, (DWORD)(TargetX), (DWORD)(TargetY), NULL, NULL);
                return;
            }
            TargetX /= 10;
            TargetY /= 10;
            if (fabs(TargetX) < 1)
            {
                if (TargetX > 0)
                {
                    TargetX = 1;
                }
                if (TargetX < 0)
                {
                    TargetX = -1;
                }
            }
            if (fabs(TargetY) < 1)
            {
                if (TargetY > 0)
                {
                    TargetY = 1;
                }
                if (TargetY < 0)
                {
                    TargetY = -1;
                }
            }
            mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);

            //std::cout << "[Pitch:]" << Pitch << "\n";
            //std::cout << "[Yaw: ]" << Yaw << "\n";
            //std::cout << "[mouse x:] " << (int)ScreenPos.x << "\n";
            //std::cout << "[mouse y:] " << (int)ScreenPos.y << "\n";
            Sleep(1);
            //MouseController::Move_Mouse((ScreenPos.x * 65535 / GetSystemMetrics(SM_CXSCREEN)), (ScreenPos.y * 65535 / GetSystemMetrics(SM_CYSCREEN)));
        }
    }
}