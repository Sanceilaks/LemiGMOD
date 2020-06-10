#pragma once
#include "VMatrix.h"
#include "CBaseEntity.h"
#include "Interfaces.h"
#include "CUserCmd.h"
#include "QAngle.h"
#include "math.h"



#pragma warning( push )
#pragma warning( disable : 4244) //4244


enum ECSPlayerBones {
	pelvis = 0,
	spine_0,
	spine_1,
	spine_2,
	spine_3,
	neck_0,
	head_0,
	clavicle_L,
	arm_upper_L,
	arm_lower_L,
	hand_L
};


class GameTools
{
public:
	static Math::CVector GetEntityBone(CBaseEntity* pEntity, ECSPlayerBones Bone)
	{
		Math::matrix3x4_t boneMatrix[128];

		if (!pEntity->SetupBones(boneMatrix, 128, 0x00000100, Interfaces::Get().Engine->GetLastTimeStemp()))
			return Math::CVector();

		Math::matrix3x4_t hitbox = boneMatrix[Bone];

		return Math::CVector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}

	static bool WorldToScreen(Math::CVector in, Math::CVector& out)
	{
		const Math::VMatrix w2sm = Interfaces::Get().Engine->GetViewMatrix();
		float w = w2sm[3][0] * in.x + w2sm[3][1] * in.y + w2sm[3][2] * in.z + w2sm[3][3];

		if (w > 0.001f)
		{
			int width, height; Interfaces::Get().Engine->GetScreenSize(width, height);

			float fl1DBw = 1 / w;
			out.x = (width / 2) + (0.5f * ((w2sm[0][0] * in.x + w2sm[0][1] * in.y + w2sm[0][2] * in.z + w2sm[0][3]) * fl1DBw) * width + 0.5f);
			out.y = (height / 2) - (0.5f * ((w2sm[1][0] * in.x + w2sm[1][1] * in.y + w2sm[1][2] * in.z + w2sm[1][3]) * fl1DBw) * height + 0.5f);
			return true;
		}
		return false;
	}
	static void CorrectMovement(CUserCmd* cmd, Math::QAngle oldangles)
	{
		float deltaView;
		float yaw[2];

		float pitch = fmodf(Math::AngleNormalizePositive(cmd->ViewAngles.x), 360);


		yaw[0] = Math::AngleNormalizePositive(oldangles.y);
		yaw[1] = Math::AngleNormalizePositive(cmd->ViewAngles.y);

		if (yaw[1] < yaw[0])
			deltaView = abs(yaw[1] - yaw[0]);
		else
			deltaView = 360.0f - abs(yaw[0] - yaw[1]);

		deltaView = 360.0f - deltaView;

		float fwdmov, sdmov; fwdmov = cmd->ForwardMove; sdmov = cmd->SideMove;

		cmd->ForwardMove = cos(DEG2RAD(deltaView)) * fwdmov + cos(DEG2RAD(deltaView + 90.f)) * sdmov;
		cmd->SideMove = sin(DEG2RAD(deltaView)) * fwdmov + sin(DEG2RAD(deltaView + 90.f)) * sdmov;
	}

	static Math::QAngle FixAngles(Math::QAngle angles)
	{
		angles.x = Math::AngleNormalize(angles.x);
		angles.y = Math::AngleNormalize(angles.y);
		if (angles.x > 89.f)
			angles.x = 89.f;
		else if (angles.x < -89.f)
			angles.x = -89.f;
		return angles;
	}

	static Math::CVector CalcAngle(Math::CVector src, Math::CVector dst)
	{
		auto ret = Math::CVector();
		Math::CVector delta = src - dst;
		double hyp = delta.Length2D();
		ret.y = (atan(delta.y / delta.x) * 57.295779513082f);
		ret.x = (atan(delta.z / hyp) * 57.295779513082f);
		ret.z = 0.f;

		if (delta.x >= 0.f)
			ret.y += 180.f;
		return ret;
	}

	static float GetFoV(Math::QAngle qAngles, Math::CVector vecSource, Math::CVector vecDestination, bool bDistanceBased)
	{
		auto MakeVector = [](Math::QAngle qAngles)
		{
			auto ret = Math::CVector();
			auto pitch = float(qAngles[0] * M_PI / 180.f);
			auto yaw = float(qAngles[1] * M_PI / 180.f);
			auto tmp = float(cos(pitch));
			ret.x = float(-tmp * -cos(yaw));
			ret.y = float(sin(yaw) * tmp);
			ret.z = float(-sin(pitch));
			return ret;
		};

		Math::CVector ang, aim;
		double fov;

		ang = CalcAngle(vecSource, vecDestination);
		aim = MakeVector(qAngles);
		ang = MakeVector(ang);

		auto mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		auto mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		auto u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];

		fov = acos(u_dot_v / (mag_s * mag_d)) * (180.f / M_PI);

		if (bDistanceBased) {
			fov *= 1.4;
			float xDist = abs(vecSource[0] - vecDestination[0]);
			float yDist = abs(vecSource[1] - vecDestination[1]);
			float Distance = sqrt((xDist * xDist) + (yDist * yDist));

			Distance /= 650.f;

			if (Distance < 0.7f)
				Distance = 0.7f;

			if (Distance > 6.5)
				Distance = 6.5;

			fov *= Distance;
		}

		return (float)fov;
	}

	static bool IsVisible(Math::CVector TraceStartPos, Math::CVector TraceEndPos, CBasePlayer* player)
	{
		CBasePlayer* LocalPlayer = CBasePlayer::GetLocalPlayer();
		if (!LocalPlayer)
			return false;

		Ray_t ray;
		trace_t tr;
		CTraceFilter filter;
		filter.pSkip = LocalPlayer;

		Math::CVector EyePos = LocalPlayer->GetEyePosition();

		ray.Init(EyePos, TraceEndPos);

		Interfaces::Get().EngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

		if (tr.m_pEnt == player || tr.fraction >= 0.98f)
			return true;
		return false;
	}

	static int GetFov()
	{
		if (!Interfaces::Get().Engine->isInGame())
			return 0;

		auto glua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);
		if (!glua) return 0;

		glua->PushSpecial(LUA::Special::glob);
		glua->GetField(-1, "LocalPlayer");
		glua->Call(0, 1);

		glua->GetField(-1, "GetFOV");
		glua->Push(-2);
		glua->Call(1, 1);

		int ret = glua->GetNumber();
		glua->Pop(3);

		return ret;
	}

	static void SetFov(int fov)
	{
		if (!Interfaces::Get().Engine->isInGame())
			return;

		auto glua = Interfaces::Get().LuaShared->CreateInterface(LUA::Type::client);
		if (!glua) return;

		glua->PushSpecial(LUA::Special::glob);

		glua->GetField(-1, "LocalPlayer");
		glua->Call(0, 1);

		glua->GetField(-1, "SetFOV");
		glua->PushNumber(fov);
		glua->Call(1, 0);

		glua->Pop(3);
	}

	static void SetViewModelFov() {};

};


#pragma warning( pop )