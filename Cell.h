#pragma once

#include <list>
#include <vector>
#include <algorithm>
#include "Unit.h"
namespace GameCore
{ 
	struct Cell
	{
		std::list<int> unitsIndexes;
		void AddIndex(int index);
		void ClearIndexes();
	};

	class CellManager
	{
		std::vector<std::vector<Cell>> _cells;
		float _cellScale;
		float _fieldWidht;
		float _fieldHeight;
	public:  
		CellManager();
		void Init(int fieldSizeX, int fieldSizeY, float cellScale);
		void Clear();
		void Update(std::vector<Unit>& units); 
		void PrintToFile(const char* filename); //debug info
		Cell* GetCellByPosition(const Vec2& position);
	};


}
