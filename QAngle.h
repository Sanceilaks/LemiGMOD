#pragma once
#pragma warning( push )
#pragma warning( disable : 4244)


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
	static float RadiansToDegrees(float rad)
	{
		return rad * (180.0 / 3.141592653589793238463);
	}


	static QAngle CalculateRelativeAngle(const QAngle& source, const QAngle& destination, const QAngle& viewAngles) noexcept
	{
		QAngle delta = destination - source;
		QAngle angles { RadiansToDegrees(atan2f(-delta.z, std::hypotf(delta.x, delta.y))) - viewAngles.x,
					   RadiansToDegrees(atan2f(delta.y, delta.x)) - viewAngles.y, 0 };
		ClampAngles(angles);
		return angles;
	}
}
#pragma warning( pop )