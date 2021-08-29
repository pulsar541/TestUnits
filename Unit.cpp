#include "Unit.h"
namespace GameCore
{
    Unit::Unit(int index, Vec2 position, Vec2 direction)
    {
        _selfIndex = index;

        std::ostringstream ss;
        ss << index;
        _stringName += ss.str();
        _position = position;
        direction.normalize();
        _directionAngle = std::atan2(-direction.x, direction.y) / PIo180;
        _drawViewSectors = false;
        _detectedAliensCount = 0;

        Update();
    }

    void Unit::Draw()
    {
        glPushMatrix();
            //glLoadIdentity();
            glPushMatrix();
                glTranslatef(_position.x, _position.y, 0); 
                glRotatef(_directionAngle, 0, 0, 1);
                glScalef(_size, _size, 1);
            
                glColor3f(1, 1, 1);
                glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex2f(0, 0.5);
                glColor3f(0.5, 0, 0);
                glVertex2f(-0.25, -0.25);
                glVertex2f(0.25, -0.25);
                glEnd();
            glPopMatrix();

            if (_drawViewSectors)
            {
                glPushMatrix();
                    glTranslatef(_position.x, _position.y, 0);
                    glColor3f(0, 0.5, 0);
                    glBegin(GL_LINE_STRIP);  
                       glVertex2f(_startViewSector.x * _viewDistance, _startViewSector.y * _viewDistance); 
                       glVertex2f(0, 0);
                       glVertex2f(_endViewSector.x * _viewDistance, _endViewSector.y * _viewDistance);
                    glEnd();
                glPopMatrix();
                
                glPushMatrix(); 
                glTranslatef(_position.x, _position.y, 0);
                glRotatef(_directionAngle, 0, 0, 1);
                glBegin(GL_LINE_STRIP);
                for (float ang = -_viewHalfSectorAngle; ang <= _viewHalfSectorAngle; ang += 9)
                {
                    float x = _viewDistance * sin(ang * PIo180);
                    float y = _viewDistance * cos(ang * PIo180);
                    glVertex2f(x, y);
                }
                glEnd();
                glPopMatrix();
            }
              
            glColor3f(1, 1, 0);
            glPushMatrix();
                glTranslatef(_position.x - _size * 0.5f, _position.y + _size * 0.5f, 0);
                glScalef(0.003, 0.003, 1);
                glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)_stringName.c_str());
            glPopMatrix();
   
        glPopMatrix();

    }

    void Unit::Update()
    {
        _startViewSector.x = sin((-_directionAngle - _viewHalfSectorAngle) * PIo180);
        _startViewSector.y = cos((-_directionAngle - _viewHalfSectorAngle) * PIo180);
        _endViewSector.x = sin((-_directionAngle + _viewHalfSectorAngle) * PIo180);
        _endViewSector.y = cos((-_directionAngle + _viewHalfSectorAngle) * PIo180);
    }
 
    int Unit::GetIndex()
    {
        return _selfIndex;
    }

    Vec2 Unit::GetCoord()
    {
        return _position;
    }

    float Unit::GetViewDistance()
    {
        return _viewDistance;
    }

    void Unit::DebugMode(bool value)
    {
        _drawViewSectors = value;
    }

    void Unit::SetDetectedAliensCount(int count)
    {
        _detectedAliensCount = count;
    }
 
    int Unit::GetDetectedAliensCount()
    {
        return _detectedAliensCount;
    }
    Vec2 Unit::GetStartViewSector()
    {
        return _startViewSector;
    }
    Vec2 Unit::GetEndViewSector()
    {
        return _endViewSector;
    }
}