#pragma once
#include "..\MenuConfig.hpp"
#include "..\Entity.h"

namespace SpecList
{
	bool isSpectating(PlayerController* PlayerController)
	{
		DWORD64 hPawn;
		ProcessMgr.ReadMemory(PlayerController->Address + Offset::PlayerController.m_hPawn, hPawn);
		if (!hPawn)
			return false;

		DWORD64 ObserverServices;
		DWORD64 ObserverTarget;
		ProcessMgr.ReadMemory(hPawn + Offset::PlayerController.m_pObserverServices, ObserverServices);
		ProcessMgr.ReadMemory(ObserverServices + Offset::PlayerController.m_hObserverTarget, ObserverTarget);

		DWORD64 targetController;
		ProcessMgr.ReadMemory(ObserverTarget + Offset::PlayerController.m_hController, targetController);
		if (!targetController)
			return false;

		return true;
	}

	void Run(const CEntity& aLocalPlayer, const CEntity& Entities)
	{
		auto y = 0u;
	}
}