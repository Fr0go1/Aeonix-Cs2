#pragma once
#define _USE_MATH_DEFINES
#include "../Game.h"
#include <math.h>
#include <tuple>

class Base_Radar
{
public:
	// �����״�����
	void SetSize(const float& Size);
	void SetPos(const Vec2& Pos);
	void SetRange(const float& Range);
	void SetCrossColor(const ImColor& Color);
	void SetProportion(const float& Proportion);
	void SetDrawList(ImDrawList* DrawList);
	// ��ȡ�״�����
	float GetSize();
	Vec2 GetPos();
	// ��ӻ��Ƶ�
	void AddPoint(const Vec3& LocalPos,const float& LocalYaw, const Vec3& Pos, ImColor Color, int Type = 0, float Yaw = 0.0f);
	// ��Ⱦ
	void Render();
public:
	ImDrawList* DrawList = nullptr;
	// ʮ����ʾ
	bool ShowCrossLine = true;
	// ʮ����ɫ
	ImColor CrossColor = ImColor(255, 255, 255, 255);
	// ����
	float Proportion = 2680;
	// Բ��뾶
	float CircleSize = 4;
	// ��ͷ�ߴ�
	float ArrowSize = 11;
	// Բ����ͷ�ߴ�
	float ArcArrowSize = 7;
	// �״ﷶΧ
	float RenderRange = 250;
	// ����Yaw����
	float LocalYaw = 0.0f;
	// ״̬
	bool Opened = true;
	// �״�������� 0:Բ�� 1:��ͷ 2:Բ����ͷ
	int  PointType = 0;
private:
	Vec2  Pos{ 0,0 };
	float Width = 200;
	std::vector<std::tuple<Vec2, ImColor, int, float>> Points;
};