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
            ang.y = 180.0f;
        if (ang.y < -180.0f)
            ang.y = -180.0f;

        ang.z = 0.0f;

    }

}