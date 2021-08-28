#include "Cell.h"

void Cell::AddIndex(int index)
{
	unitsIndexes.push_back(index);
}

void Cell::RemoveIndex(int index)
{
	unitsIndexes.remove(index);
}
