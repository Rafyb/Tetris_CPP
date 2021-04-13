#include "Grid.h";
#include <iostream>

Grid::Grid() 
{
	_nb = 0;
	
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
	for (int i = 0; i < GRID_WIDTH; i++) {
		free(_gridFixed[i]);
	}
	free(_gridFixed);
}


void Grid::Initialize(sf::Texture* textures) 
{
	_blockTxt = textures;
}

Bloc* Grid::InstantiateBloc() 
{
	Bloc* newBloc = new Bloc();
	newBloc->Initialize(_blockTxt[0]);

	//_blocs.push_back(&newBloc);

	_nb++;
	return newBloc;
}

bool Grid::CanMove(int x, int y)
{
	if (x < 0 || x >= GRID_WIDTH) return false;
	if (y >= GRID_HEIGHT) return false;
	
	return !_gridFixed[x][y];
}

void Grid::Fix(Bloc bloc)
{
	std::cout << "Fixed X:" << bloc.gridX << " Y:" << bloc.gridY << "\n";
	_gridFixed[bloc.gridX][bloc.gridY] = true;
	std::cout << !_gridFixed[bloc.gridX][bloc.gridY] << "\n";
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
		_gridFixed[blocs[i]->gridX][blocs[i]->gridY] = true;
	}
}