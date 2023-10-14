#pragma once
#include "Game.h"
#include "Entity.h"
#include "AimBot.hpp"
#include "Radar/Radar.h"
#include "TriggerBot.hpp"
#include "Bunnyhop.hpp"

namespace Cheats
{
	void Menu();
	void RadarSetting(Base_Radar& Radar);
	void RenderCrossHair(ImDrawList* drawList) noexcept;
	void Run();
}