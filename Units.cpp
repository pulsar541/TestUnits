// Units.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <random>
#include <thread>

#include "Unit.h"
#include "Cell.h"
 
using namespace GameCore;
 
#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 768

#define MAX_UNITS_COUNT 10000
#define SCENE_SCALE  30
#define FIELD_WIDTH 200
#define FIELD_HEIGHT 200

#define DEBUG_MODE true   //если true, то визуализируются номера юнитов и их "сектора зрения" 

const char* dataFileName = "data.txt";      //если у вас нет этого файла,  раскомментируйте и вызовите один раз GenerateDataFile (216 строка)
const char* resultFileName = "result.txt";  //результат работы, согласно заданию

int win_width;
int win_height;
int WinFar = 10; 
bool mouseLBpressed = false;
float oldMouseX;
float oldMouseY;
Vec2 sceneOffset;
 
std::vector<Unit> unitList;    
CellManager cellManager;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 
    glTranslatef(sceneOffset.x, sceneOffset.y, 1); 
    glScalef(SCENE_SCALE, SCENE_SCALE, 1); 
    
    for (std::vector<Unit>::iterator i = unitList.begin(); i != unitList.end(); ++i)
    {
        i->Draw();
    }

    if (!mouseLBpressed && DEBUG_MODE)
    {  
        for (std::vector<Unit>::iterator i = unitList.begin(); i != unitList.end(); ++i)
        {
            i->DrawInfo();
        }
    }

    glFlush();
    glutSwapBuffers();
}

void GenerateDataFile()
{
     std::string buffer;
     std::random_device rd;
     std::mt19937 mt(rd());
     std::uniform_real_distribution<double> randd(-FIELD_WIDTH/2, FIELD_WIDTH/2);

     for (int c = 0; c < MAX_UNITS_COUNT; c++)
     { 
         std::ostringstream ss;
         float x = randd(mt);
         float y = randd(mt);
         Vec2 radiusVec(randd(mt), randd(mt));
         radiusVec.normalize();
         ss << x << " " << y << " " << radiusVec.x << " " << radiusVec.y << "\n";
         buffer += ss.str();
         ss.clear();
     }  
     std::ofstream fo(dataFileName);
     fo.write(buffer.data(), buffer.size());
}

void InitUnits(int unitsMaxCount = -1)
{   
    std::string buffer;

    std::ifstream f(dataFileName);
    f.seekg(0, std::ios::end);
    buffer.resize(f.tellg());
    f.seekg(0);
    f.read((char *)buffer.data(), buffer.size()); 

    std::istringstream is(buffer);
    std::string line;
    int ind = 0;
    while (is)
    {
        getline(is, line); 
       // cout << "line: " << line << "\n"; 
        std::stringstream ss(line);
        float data[4];
        for (int i = 0; i < 4;i++) {
            ss >> data[i];
        }

        Unit u(ind++, 
            Vec2(data[0], data[1]), 
            Vec2(data[2], data[3]));
          
        unitList.push_back(u); 

        if (unitsMaxCount-- == 0)
            break;
          
    } 
}



void TaskUpdateUnitsInfo(bool saveToFile = false, const char* resultFilename = "")
{ 
     
    for (std::vector<Unit>::iterator i = unitList.begin(); i != unitList.end(); ++i)
    { 
        Vec2 center = i->GetCoord();
        Vec2 sectorStart= i->GetStartViewSector();
        Vec2 sectorEnd = i->GetEndViewSector();
        float radiusSquared = i->GetViewDistance() * i->GetViewDistance();

        Cell* tmpCell = cellManager.GetCellByPosition(i->GetCoord());
        if (tmpCell != nullptr)
        {  
            int detectedAliensCount = 0;
            for (std::list<int>::iterator n = tmpCell->unitsIndexes.begin(); n != tmpCell->unitsIndexes.end(); ++n)
            { 
                if (unitList.at(*n).GetIndex() == i->GetIndex())
                    continue; 


                Vec2 point = unitList.at(*n).GetCoord();
                bool isInside = isInsideSector(point, center, sectorStart, sectorEnd, radiusSquared);  

                if (isInside)
                {
                    detectedAliensCount++;
                }
            }
            i->SetDetectedAliensCount(detectedAliensCount);
        }
    }  

    if (saveToFile)
    { 
        std::string buffer; 
        for (std::vector<Unit>::iterator i = unitList.begin(); i != unitList.end(); ++i)
        {
            std::ostringstream ss; 
            ss << "Unit " << i->GetIndex() << " sees " << i->GetDetectedAliensCount() << std::endl;
            buffer += ss.str();
            ss.clear();
        }
        std::ofstream fo(resultFilename);
        fo.write(buffer.data(), buffer.size()); 
    }

}


void on_mouse(int button, int state, int x, int y)
{  
    if (button == GLUT_LEFT_BUTTON)
    {
        mouseLBpressed = (state == GLUT_DOWN);
    }

    else if (button == GLUT_RIGHT_BUTTON)
    { 
        mouseLBpressed = (state == GLUT_DOWN);
    }
     
    oldMouseX = x;
    oldMouseY = y;
}

void on_mouseMove(int mx, int my)
{
    sceneOffset.x += (mx - oldMouseX);
    sceneOffset.y -= (my - oldMouseY); 
    oldMouseX = mx;
    oldMouseY = my;
    glutPostRedisplay();  
}

void on_resize(int w, int h)
{
    win_width = w;
    win_height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display();
}

int main(int argc, char** argv)
{
    std::cout << "Test Units!\n";
       
    //GenerateDataFile();  

    // game init 
    InitUnits(MAX_UNITS_COUNT);
    cellManager.Init(FIELD_WIDTH, FIELD_HEIGHT, 20);
    cellManager.Update(unitList);
    cellManager.PrintToFile("cells.txt"); //debug info about cells
     
    std::thread t1(TaskUpdateUnitsInfo, true, resultFileName);
      
    // gl init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Units");

    glClearColor(0, 0, 0, 1.0); 
    glutDisplayFunc(display);
    glutReshapeFunc(on_resize);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_mouseMove); 

    glutMainLoop();
    return 0;
}
