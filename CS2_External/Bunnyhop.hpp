#pragma once
#include "Game.h"
#include "Entity.h"
#include <Windows.h>

namespace Bunnyhop
{
	inline void Run(const CEntity& Local)
	{
		const bool hasFlagInAir = Local.Pawn.HasFlag(PlayerPawn::Flags::IN_AIR);
		if (GetAsyncKeyState(VK_SPACE) && hasFlagInAir)
		{
			gGame.SetForceJump(65537);
		}
		else if (GetAsyncKeyState(VK_SPACE) && !hasFlagInAir)
		{
			gGame.SetForceJump(256);
			gGame.SetForceJump(65537);
			gGame.SetForceJump(256);
		}
		else
		{
			gGame.SetForceJump(256);
		}
	}
}

namespace Bunnyhop2
{
    inline void Run(const CEntity& Local)
    {
        const bool hasFlagInAir = Local.Pawn.HasFlag(PlayerPawn::Flags::IN_AIR);
		if (GetAsyncKeyState(VK_SPACE))
        {
            // scrolling up
            INPUT inputScrollUp;
            inputScrollUp.type = INPUT_MOUSE;
            inputScrollUp.mi.dx = 0;
            inputScrollUp.mi.dy = 0;
            inputScrollUp.mi.mouseData = WHEEL_DELTA;
            inputScrollUp.mi.dwFlags = MOUSEEVENTF_WHEEL;
            inputScrollUp.mi.time = 0;
            inputScrollUp.mi.dwExtraInfo = 0;

			SendInput(1, &inputScrollUp, sizeof(INPUT));
        }
    }
}