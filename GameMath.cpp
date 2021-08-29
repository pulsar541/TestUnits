#include "GameMath.h"

#include <stdint.h>

namespace GameMath
{
    #define PI 3.14159265358979323846f
    #define PIo180 0.01745329251f

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
     
    int dotProduct(Vec2& v1, Vec2& v2)
    { 
        return v1.x * v2.x + v1.y * v2.y;
    }

    bool areClockwise(Vec2& v1, Vec2& v2)
    {
        return -v1.x * v2.y + v1.y * v2.x > 0;
    }

    bool isWithinRadius(Vec2 &v, float radiusSquared)
    {
        return v.x * v.x + v.y * v.y <= radiusSquared;
    }

    bool isInsideSector(Vec2& point, Vec2& center, Vec2& sectorStart, Vec2& sectorEnd, float radiusSquared)
    {
        Vec2 relPoint (point.x - center.x, point.y - center.y); 
        return areClockwise(sectorStart, relPoint) &&
            !areClockwise(sectorEnd, relPoint) &&
            isWithinRadius(relPoint, radiusSquared);
    }

    float squareDist(const Vec2& v1, const Vec2& v2) 
    {
        return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
    }

}