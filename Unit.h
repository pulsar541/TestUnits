#pragma once

#include "glut.h"
 #include <cmath>
#include "GameMath.h"

namespace GameCore
{
    
    using namespace GameMath;
    class Unit
    {   
        int _selfIndex;
        float _x, _y;
        float _directionAngle;
        const float _size = 1.0f;
        const float _viewSectorAngle = 135.5f;
        const float _viewDistance = 2.0f;

    public:
        Unit(int index, float x = 0, float y = 0, Vec2 direction = Vec2(1, 0));
        void Draw();
        void Update();
         
        int GetIndex();
        Vec2 GetCoord();
    };
}

