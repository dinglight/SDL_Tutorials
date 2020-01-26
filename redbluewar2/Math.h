#pragma once
#include <cmath>
namespace Math {
    static const float PI = 3.1415936f;
    inline bool NearZero(float val, float epsilon = 0.001f)
    {
        if (fabs(val) <= epsilon) {
            return true;
        }
        else {
            return false;
        }
    }
}