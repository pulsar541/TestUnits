// Units.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <random>

#include "Unit.h"
#include "Cell.h"
 
using namespace GameCore;

#define PI 3.14159265358979323846f
#define PIo180 0.01745329251f


#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 768
#define SCENE_SCALE  10

const char* dataFileName = "data.txt";

int win_width;
int win_height;
int WinFar = 10; 
 
std::vector<Unit> unitList;   
std::map<long, Cell> gameField;


void updateFieldCells()
{ 
    while (1)
    {
        for (std::vector<Unit>::iterator i = unitList.begin(); i != unitList.end(); ++i)
        {
            Vec2 unitCoord = i->GetCoord();
            Cell cell;
            cell.AddIndex(i->GetIndex()); 
            long key = (int)unitCoord.x * (int)unitCoord.y + (int)unitCoord.x;
            gameField.insert(std::pair<long, Cell>(key,cell));  
        }
        Sleep(500);
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glScalef(SCENE_SCALE, SCENE_SCALE, 1);
    
    //DrawPoint(0, 0); 
    for (std::vector<Unit>::iterator i = unitList.begin(); i != unitList.end(); ++i)
    {
        i->Draw();
    }

    glFlush();
    glutSwapBuffers();
}

void GenerateDataFile()
{
     std::string buffer;
     std::random_device rd;
     std::mt19937 mt(rd());
     std::uniform_real_distribution<double> randd(-100.0, 100.0);

     for (int c = 0; c < 10000; c++)
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
    //GenerateDataFile();

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

        Unit u(ind++, data[0], data[1], Vec2(data[2], data[3]));
        unitList.push_back(u);

        if (unitsMaxCount-- == 0)
            break;
          
    } 
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
      
    // game init
    InitUnits(5000);

    // gl init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Units");

    glClearColor(0, 0, 0, 1.0); 
    glutDisplayFunc(display);
    glutReshapeFunc(on_resize);

    glutMainLoop();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
