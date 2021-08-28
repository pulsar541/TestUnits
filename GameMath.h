#pragma once

//#include <stdint.h>

namespace GameMath
{
    #define PI 3.14159265358979323846f
    #define PIo180 0.01745329251f

    struct Vec2
    {
        float x;
        float y;
        Vec2(float vx = 0, float vy = 0);
        Vec2& operator = (Vec2& c);
        Vec2& operator + (Vec2& c);
        Vec2& operator - (Vec2& c);
        Vec2& normalize();
    };
}