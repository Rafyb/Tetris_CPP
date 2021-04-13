#pragma once
#include <SFML/Graphics.hpp>
#include "Bloc.h"
#include "Constants.h"

class Grid
{
public:
	Grid();
	~Grid();
	void Initialize(sf::Texture *textures);
	Bloc* InstantiateBloc();
	bool CanMove(int x, int y);
	//void Draw(sf::RenderWindow& window);
	void Fix(Bloc bloc);
	int HasLine();
	void UpdateGrid(std::vector<Bloc*> blocs);

private:
	bool** _gridFixed;
	sf::Texture* _blockTxt;
	int _nb;
};