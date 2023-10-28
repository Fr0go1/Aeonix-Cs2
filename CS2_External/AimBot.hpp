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
		int ScreenCenterX = Gui.Window.Size.x / 2;
		int ScreenCenterY = Gui.Window.Size.y / 2;
		float TargetX = 0.f;
		float TargetY = 0.f;

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
			Sleep(1);
		}

		/*
		Yaw = Yaw * (1 - Smooth) + Local.Pawn.ViewAngle.y;
		Pitch = Pitch * (1 - Smooth) + Local.Pawn.ViewAngle.x;

		// Recoil control
		if (MenuConfig::RCS)
		{
			if (Local.Pawn.ShotsFired > RCSBullet)
			{
				Vec2 PunchAngle;
				if (Local.Pawn.AimPunchCache.Count <= 0 && Local.Pawn.AimPunchCache.Count > 0xFFFF)
					return;
				if (!ProcessMgr.ReadMemory<Vec2>(Local.Pawn.AimPunchCache.Data + (Local.Pawn.AimPunchCache.Count - 1) * sizeof(Vec3), PunchAngle))
					return;

				Yaw = Yaw - PunchAngle.y * RCSScale.x;
				Pitch = Pitch - PunchAngle.x * RCSScale.y;
			}

		}

		gGame.SetViewAngle(Yaw, Pitch);*/
	}
}