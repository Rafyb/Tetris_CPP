#include "BlocGroup.h"
#include <iostream>

BlocGroup::BlocGroup() :worldX(0), worldY(0), size(0)
{

}

void BlocGroup::Initialize(const sf::Texture& texture, std::vector<Bloc*> blocsTmp)
{
	for (int i = 0; i < blocsTmp.size(); i++)
	{
		Bloc* bloc = blocsTmp[i];
		bloc->Initialize(texture);
		_blocs.push_back(bloc);
	}
	
}

bool BlocGroup::UpdateStep(Grid plateau) {

	if( !CanMove(plateau, sf::Vector2f(0,1)) ) return false;

	Move(sf::Vector2f(0, 1));
	return true;
}

void BlocGroup::Move(const sf::Vector2f dir) {
	//std::cout << "Bloc\n";

	worldX += dir.x;
	worldY += dir.y;

	for (int i = 0; i < _blocs.size(); i++)
	{
		//std::cout << "Bloc numero : " + std::to_string(i) << " | ";
		_blocs[i]->SetPosition(worldX,worldY);
		//std::cout << "Bloc position x : " + std::to_string(_blocs[i]->worldX) + " + " + std::to_string(_blocs[i]->localX) << "\n";
		//std::cout << "Bloc position y : " + std::to_string(_blocs[i]->worldY) + " + " + std::to_string(_blocs[i]->localY) << "\n";
	}
}

bool BlocGroup::Rorate(Grid plateau) {
	if (size == 3) 
	{
		for (int i = 0; i < _blocs.size(); i++)
		{
			if (_blocs[i]->localX == 0 && _blocs[i]->localY == 3) if (!plateau.CanMove(worldX, worldY - 2)) return false;
			if (_blocs[i]->localX == 0 && _blocs[i]->localY == 1) if (!plateau.CanMove(worldX + 2, worldY)) return false;
			if (_blocs[i]->localX == 2 && _blocs[i]->localY == 1) if (!plateau.CanMove(worldX, worldY + 2)) return false;
			if (_blocs[i]->localX == 2 && _blocs[i]->localY == 3) if (!plateau.CanMove(worldX - 2, worldY)) return false;

			if (_blocs[i]->localX == 1 && _blocs[i]->localY == 3) if (!plateau.CanMove(worldX - 1, worldY - 1)) return false;
			if (_blocs[i]->localX == 0 && _blocs[i]->localY == 2) if (!plateau.CanMove(worldX + 1, worldY - 1)) return false;
			if (_blocs[i]->localX == 1 && _blocs[i]->localY == 1) if (!plateau.CanMove(worldX + 1, worldY + 1)) return false;
			if (_blocs[i]->localX == 2 && _blocs[i]->localY == 2) if (!plateau.CanMove(worldX - 1, worldY + 1)) return false;
		}

		for (int i = 0; i < _blocs.size(); i++)
		{
			
			if (_blocs[i]->localX == 0 && _blocs[i]->localY == 3) _blocs[i]->MoveLocal(sf::Vector2f(0,-2));
			else if (_blocs[i]->localX == 0 && _blocs[i]->localY == 1) _blocs[i]->MoveLocal(sf::Vector2f(+2, 0));
			else if (_blocs[i]->localX == 2 && _blocs[i]->localY == 1) _blocs[i]->MoveLocal(sf::Vector2f(0, +2));
			else if (_blocs[i]->localX == 2 && _blocs[i]->localY == 3) _blocs[i]->MoveLocal(sf::Vector2f(-2, 0));
			
			
			else if (_blocs[i]->localX == 1 && _blocs[i]->localY == 3) _blocs[i]->MoveLocal(sf::Vector2f(-1, -1));
			else if (_blocs[i]->localX == 0 && _blocs[i]->localY == 2) _blocs[i]->MoveLocal(sf::Vector2f(+1, -1));
			else if (_blocs[i]->localX == 1 && _blocs[i]->localY == 1) _blocs[i]->MoveLocal(sf::Vector2f(+1, +1));
			else if (_blocs[i]->localX == 2 && _blocs[i]->localY == 2) _blocs[i]->MoveLocal(sf::Vector2f(-1, +1));

			
		}
	}
	return true;
}

bool BlocGroup::CanMove(Grid plateau, sf::Vector2f dir)
{
	for (int i = 0; i < _blocs.size(); i++)
	{
		if (!plateau.CanMove(_blocs[i]->GridX() + dir.x, _blocs[i]->GridY() + dir.y)) return false;
	}
	return true;
}
