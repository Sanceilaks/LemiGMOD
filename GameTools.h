#pragma once
#include "VMatrix.h"
#include "CBaseEntity.h"
#include "Interfaces.h"
#include "CUserCmd.h"
#include "QAngle.h"
#include "math.h"

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

};