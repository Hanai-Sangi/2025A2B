#pragma once
#include "GameObject.h"

template<typename T>
inline T Lerp(T start, T end, float rate)
{
	return (end - start) * rate + start;
}

float easeOutBounce(float x) {
    const float n1 = 7.5625;
    const float d1 = 2.75;

    if (x < 1 / d1) {
        return n1 * x * x;
    } else if (x < 2 / d1) {
        return n1 * (x -= 1.5 / d1) * x + 0.75;
    } else if (x < 2.5 / d1) {
        return n1 * (x -= 2.25 / d1) * x + 0.9375;
    } else {
        return n1 * (x -= 2.625 / d1) * x + 0.984375;
    }
}

float easeOutBack(float x) {
    const float c1 = 1.70158;
    const float c3 = c1 + 1;

    return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}