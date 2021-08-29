#pragma once

#include <cmath>
#include <sstream>
#include <list>
#include "freeglut.h"
 

#include "GameMath.h"

namespace GameCore
{
    
    using namespace GameMath;
    class Unit
    {   
        const float _size = 0.5f;
        const float _viewSectorAngle = 135.5 ;
        const float _viewHalfSectorAngle = _viewSectorAngle / 2.0f;
        const float _viewDistance = 2.0f; 

        int _selfIndex;
        Vec2 _position;
        float _directionAngle;
        bool _drawViewSectors;

        Vec2 _startViewSector;
        Vec2 _endViewSector;

        std::string _stringName;
        int _detectedAliensCount;

    public:
        Unit(int index, Vec2 position, Vec2 direction = Vec2(1, 0));
        void Draw();
        void Update(); 
        int GetIndex();
        Vec2 GetCoord();
        float GetViewDistance();
        void DebugMode(bool value); 
         
        void SetDetectedAliensCount(int count); 
        int GetDetectedAliensCount();

        Vec2 GetStartViewSector();
        Vec2 GetEndViewSector();

    };
}

