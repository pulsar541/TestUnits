#pragma once
 
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

    int dotProduct(Vec2& v1, Vec2& v2);
    bool areClockwise(Vec2& v1, Vec2& v2);
    bool isWithinRadius(Vec2& v, float radiusSquared);
    bool isInsideSector(Vec2& point, Vec2& center, Vec2& sectorStart, Vec2& sectorEnd, float radiusSquared);
    float squareDist(const Vec2& v1, const Vec2& v2);
}