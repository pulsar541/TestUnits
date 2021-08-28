#include "GameMath.h"

#include <stdint.h>

namespace GameMath
{
    float Q_rsqrt(float number) //invert fast sqrt
    {
        const float x2 = number * 0.5F;
        const float threehalfs = 1.5F;

        union {
            float f;
            uint32_t i;
        } conv = { number };
        conv.i = 0x5f3759df - (conv.i >> 1);
        conv.f *= threehalfs - x2 * conv.f * conv.f;
        return conv.f;
    } 
    
    Vec2::Vec2(float vx, float vy)
        : x(vx)
        , y(vy)
    {}

    Vec2& Vec2::operator = (Vec2& c)
    {
        this->x = c.x;
        this->y = c.y;
        return *this;
    }

    Vec2& Vec2::operator + (Vec2& c)
    {
        this->x += c.x;
        this->y += c.y;
        return *this;
    }

    Vec2& Vec2::operator - (Vec2& c)
    {
        this->x -= c.x;
        this->y -= c.y;
        return *this;
    }

    Vec2& Vec2::normalize()
    {
        float inv_magnitude = Q_rsqrt(x * x + y * y);
        this->x *= inv_magnitude;
        this->y *= inv_magnitude;
        return *this;
    } 

}