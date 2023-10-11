#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include <iostream>
#include <Windows.h>

struct Vector {
	Vector() noexcept
		: x(), y(), z() {}

	Vector(float x, float y, float z) noexcept
		: x(x), y(y), z(z) {}

	Vector& operator+(const Vector& v) noexcept {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector& operator-(const Vector& v) noexcept {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	float x, y, z;
};

struct ViewMatrix {
	ViewMatrix() noexcept
		: data() {}

	float* operator[](int index) noexcept {
		return data[index];
	}

	const float* operator[](int index) const noexcept {
		return data[index];
	}

	float data[4][4];
};

static bool world_to_screen(const Vector& world, Vector& screen, const ViewMatrix& vm) noexcept {
	float w = vm[3][0] * world.x + vm[3][1] * world.y + vm[3][2] * world.z + vm[3][3];

	if (w < 0.001f) {
		return false;
	}

	const float x = world.x * vm[0][0] + world.y * vm[0][1] + world.z * vm[0][2] + vm[0][3];
	const float y = world.x * vm[1][0] + world.y * vm[1][1] + world.z * vm[1][2] + vm[1][3];

	w = 1.f / w;
	float nx = x * w;
	float ny = y * w;

	const ImVec2 size = ImGui::GetIO().DisplaySize;

	screen.x = (size.x * 0.5f * nx) + (nx + size.x * 0.5f);
	screen.y = -(size.y * 0.5f * ny) + (ny + size.y * 0.5f);

	return true;
}

namespace AimControl
{
	inline int HotKey = VK_LMENU;
	inline float AimFov = 5;
	inline float Smooth = 0.7;
	inline Vec2 RCSScale = { 1.f,1.f };
	inline int RCSBullet = 1;
	inline std::vector<int> HotKeyList{VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL};

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

		Yaw = Yaw * Smooth + Local.Pawn.ViewAngle.y;
		Pitch = Pitch * Smooth + Local.Pawn.ViewAngle.x;

		// Recoil control
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

		gGame.SetViewAngle(Yaw, Pitch);
	}
}