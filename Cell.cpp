#include "Cell.h" 
#include <fstream>

namespace GameCore
{
	void Cell::AddIndex(int index)
	{
		unitsIndexes.push_back(index);
	}

	void Cell::RemoveIndex(int index)
	{
		unitsIndexes.remove(index);
	}

	CellManager::CellManager()
	{ 
	}

	void CellManager::Init(int fieldWidth, int fieldHeight, float cellScale)
	{
		_fieldWidht = fieldWidth;
		_fieldHeight = fieldHeight;
		_cellScale = cellScale;
		if (_cellScale < 1)
			_cellScale = 1;
	}

	void CellManager::Clear()
	{
		int I = _cells.size();
		for (int i = 0; i < I; i++) {
			int J = _cells.at(i).size();
			for (int j = 0; j < J; j++) {
				_cells.at(i).at(j).unitsIndexes.clear();
			}
			_cells.at(i).clear();
		}
		_cells.clear();
	}

	void CellManager::Update(std::vector<Unit>& units)
	{
		Clear(); 

		int count_i = _fieldWidht / _cellScale;
		int count_j = _fieldHeight / _cellScale;

		_cells.resize(count_i);
		for (int i = 0; i < count_i; ++i) 
			_cells.at(i).resize(count_j);  
		 
		float halfFieldWidth = _fieldWidht / 2;
		float halfFieldHeight = _fieldHeight / 2;
		for (std::vector<Unit>::iterator u = units.begin(); u != units.end(); ++u)
		{
			Vec2 tmpPos = u->GetCoord();

			int i = ((tmpPos.x + halfFieldWidth) / _cellScale);
			int j = ((tmpPos.y + halfFieldHeight) / _cellScale);

			if (i < 0)
				i = 0;
			if (i > count_i - 1)
				i = count_i - 1;

			if (j < 0)
				j = 0;
			if (j > count_j - 1)
				j = count_j - 1;

			_cells.at(i).at(j).unitsIndexes.push_back(u->GetIndex());
		}

	}
	void CellManager::PrintToFile(const char* filename)
	{ 
		std::string buffer; 
		int I = _cells.size();
		for (int i = 0; i < I; i++) 
		{ 
			int J = _cells.at(i).size();
			for (int j = 0; j < J; j++) 
			{
				std::ostringstream ss;
				ss << "[" << i <<"," << j<< "]: "; 

				int U = _cells.at(i).at(j).unitsIndexes.size();
				for (std::list<int>::iterator u = _cells.at(i).at(j).unitsIndexes.begin(); u != _cells.at(i).at(j).unitsIndexes.end(); ++u)
				{
					ss << *u << " ";
				}
				ss << "\n";
				buffer += ss.str();
				ss.clear(); 
			} 
		}
 
		std::ofstream fo(filename);
		fo.write(buffer.data(), buffer.size());
	}

	Cell*  CellManager::GetCellByPosition(const Vec2& position)
	{ 
		int count_i = _fieldWidht / _cellScale;
		int count_j = _fieldHeight / _cellScale;
		float halfFieldWidth = _fieldWidht / 2;
		float halfFieldHeight = _fieldHeight / 2;

		int cell_i = (position.x + halfFieldWidth) / _cellScale;
		int cell_j = (position.y + halfFieldHeight) / _cellScale; 

		if(cell_i >= 0 && cell_i < count_i && cell_j >=0 && cell_j < count_j)
			return &_cells.at(cell_i).at(cell_j); 

		return nullptr;
	}
 
}