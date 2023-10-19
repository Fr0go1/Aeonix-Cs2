#pragma once
#include "Game.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include <chrono>
//#include <random>

namespace TriggerBot
{
	//inline DWORD MinDelay = 50; // Minimum delay in milliseconds
	//inline DWORD MaxDelay = 150; // Maximum delay in milliseconds
	inline DWORD TriggerDelay = 90; // ms
	inline int HotKey = VK_LMENU;
	inline std::vector<int> HotKeyList{ VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<DWORD> delayDistribution(MinDelay, MaxDelay);

	inline void SetHotKey(int Index)
	{
		HotKey = HotKeyList.at(Index);
	}

	inline void Run(const CEntity& LocalEntity)
	{
		//DWORD RandomTriggerDelay = delayDistribution(gen);
		
		DWORD uHandle = 0;
		if (!ProcessMgr.ReadMemory<DWORD>(LocalEntity.Pawn.Address + Offset::Pawn.iIDEntIndex, uHandle))
			return;
		if (uHandle == -1)
			return;

		DWORD64 ListEntry = 0;
		ListEntry = ProcessMgr.TraceAddress(gGame.GetEntityListAddress(), { 0x8 * (uHandle >> 9) + 0x10,0x0 });
		if (ListEntry == 0)
			return;

		DWORD64 PawnAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(ListEntry + 0x78 * (uHandle & 0x1FF), PawnAddress))
			return;

		CEntity Entity;
		if (!Entity.UpdatePawn(PawnAddress))
			return;

		bool AllowShoot = false;

		if (MenuConfig::TeamCheck)
			AllowShoot = LocalEntity.Pawn.TeamID != Entity.Pawn.TeamID && Entity.Pawn.Health > 0;
		else
			AllowShoot = Entity.Pawn.Health > 0;

		if (!AllowShoot)
			return;

		static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
		auto CurTimePoint = std::chrono::steady_clock::now();
		//if (CurTimePoint - LastTimePoint >= std::chrono::milliseconds(RandomTriggerDelay))
		if (CurTimePoint - LastTimePoint >= std::chrono::milliseconds(TriggerDelay))
		{
			const bool isAlreadyShooting = GetAsyncKeyState(VK_LBUTTON) < 0;
			if (!isAlreadyShooting)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}

			LastTimePoint = CurTimePoint;
		}
	}

}
