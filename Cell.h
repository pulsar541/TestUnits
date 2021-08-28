#pragma once

#include <list>
#include <algorithm>

struct Cell
{
	std::list<int> unitsIndexes;
	void AddIndex(int index);
	void RemoveIndex(int index);
};

