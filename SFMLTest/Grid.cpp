#include "Grid.h";
#include <iostream>

Grid::Grid() 
{
	_gridFixed = (bool**) malloc(sizeof(bool*) * GRID_WIDTH);
	for (int i = 0; i < GRID_WIDTH; i++) {
		_gridFixed[i] = (bool*)malloc(sizeof(bool) * GRID_HEIGHT);
		for (int y = 0; y < GRID_HEIGHT; y++) {
			_gridFixed[i][y] = false;
		}
	}
	
}

Grid::~Grid()
{
	/*
	for (int i = 0; i < GRID_WIDTH; i++) {
		free(_gridFixed[i]);
	}
	free(_gridFixed);*/
}

bool Grid::CanMove(int x, int y)
{
	if (x < 0 || x >= GRID_WIDTH) return false;
	if (y >= GRID_HEIGHT) return false;
	if (y < 0 ) return true;
	return !_gridFixed[x][y];
}

bool Grid::isEnd(std::vector<Bloc*> blocs) {
	for (int i = 0; i < blocs.size(); i++) {
		if (blocs[i]->GridY() <= 0) return true;
	}
	return false;
}


void Grid::Fix(std::vector<Bloc*> blocs)
{
	for (int i = 0; i < blocs.size(); i++) {
		_gridFixed[blocs[i]->GridX()][blocs[i]->GridY()] = true;
	}
}

int Grid::HasLine() 
{
	bool isAlign;
	for (int y = 0; y < GRID_HEIGHT; y++) {
		isAlign = true;
		for (int x = 0; x < GRID_WIDTH; x++) {
			if (!_gridFixed[x][y]) 
			{
				isAlign = false;
				break;
			}
		}
		if (isAlign) return y;

	}
	return -1;
}

void Grid::UpdateGrid(std::vector<Bloc*> blocs)
{
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			_gridFixed[i][y] = false;
		}
	}
	for (int i = 0; i < blocs.size(); i++) {
		if (blocs[i]->GridX() >= 0 && blocs[i]->GridX() < GRID_WIDTH && blocs[i]->GridY() >= 0 && blocs[i]->GridY() < GRID_HEIGHT) _gridFixed[blocs[i]->GridX()][blocs[i]->GridY()] = true;
	}
}