#pragma once
#include <SFML/Graphics.hpp>
#include "Bloc.h"
#include "Constants.h"

class Grid
{
public:
	Grid();
	~Grid();

	Bloc* InstantiateBloc();
	bool CanMove(int x, int y);
	void Fix(std::vector<Bloc*> blocs);
	int HasLine();
	void UpdateGrid(std::vector<Bloc*> blocs);

private:
	bool** _gridFixed;

};