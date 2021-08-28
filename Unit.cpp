#include "Unit.h"
namespace GameCore
{
    Unit::Unit(int index, float x, float y, Vec2 direction)
    {
        _selfIndex = index;
        _x = x;
        _y = y;
        direction.normalize();
        _directionAngle = std::atan2(-direction.x, direction.y) / PIo180;
    }

    void Unit::Draw()
    {
        glPushMatrix();
            //glLoadIdentity();
            glTranslatef(_x, _y, 0); 
            glRotatef(_directionAngle, 0, 0, 1);
            glScalef(_size, _size, 1);
            glPushMatrix();
                glColor3f(1, 1, 1);
                glBegin(GL_TRIANGLES);
                glVertex2f(0, 0.5);
                glVertex2f(-0.5, -0.25);
                glVertex2f(0.5, -0.25);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glRotatef(-_viewSectorAngle / 2, 0, 0, 1);
                glColor3f(0, 1, 0);
                glBegin(GL_LINES);
                glVertex2f(0, 0);
                glVertex2f(0, _viewDistance);
                glEnd();
                glRotatef(_viewSectorAngle, 0, 0, 1);
                glColor3f(0, 1, 0);
                glBegin(GL_LINES);
                glVertex2f(0, 0);
                glVertex2f(0, _viewDistance);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glBegin(GL_LINE_STRIP);
                for (float ang = -_viewSectorAngle / 2; ang <= _viewSectorAngle / 2; ang += 9)
                {
                    float x = _viewDistance * sin(ang * PIo180);
                    float y = _viewDistance * cos(ang * PIo180);
                    glVertex2f(x, y); 
                }
                glEnd();
            glPopMatrix();

             

        glPopMatrix();

    }

    void Unit::Update()
    {

    }
 
    int Unit::GetIndex()
    {
        return _selfIndex;
    }

    Vec2 Unit::GetCoord()
    {
        return Vec2(_x, _y);
    }
}