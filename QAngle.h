#pragma once

#include "vector.h"

namespace Math
{
	typedef CVector QAngle;

    static void ClampAngles(QAngle& ang)
    {
        if (ang.x > 89.0f)
            ang.x = 89.0f;
        if (ang.x < -89.0f)
            ang.x = -89.0f;

        if (ang.y > 180.0f)
            ang.y -= 180.0f;
        if (ang.y < -180.0f)
            ang.y += 180.0f;

        ang.z = 0.0f;

    }
	static float AngleNormalize(float angle)
	{
		angle = fmodf(angle, 360.0f);
		if (angle > 180)
		{
			angle -= 360;
		}
		if (angle < -180)
		{
			angle += 360;
		}
		return angle;
	}
	static float AngleNormalizePositive(float angle)
	{
		angle = fmodf(angle, 360.0f);

		if (angle < 0.0f)
		{
			angle += 360.0f;
		}

		return angle;
	}
	static float AngleDifference(float destAngle, float srcAngle)
	{
		float delta;

		delta = fmodf(destAngle - srcAngle, 360.0f);
		if (destAngle > srcAngle)
		{
			if (delta >= 180)
				delta -= 360;
		}
		else
		{
			if (delta <= -180)
				delta += 360;
		}
		return delta;
	}

}