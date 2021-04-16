#include "BlocGroup.h"

BlocGroup::BlocGroup()
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

	for (int i = 0; i < _blocs.size(); i++)
	{
		_blocs[i]->UpdateStep();
	}
	return true;
}

void BlocGroup::Move(const sf::Vector2f dir) {
	for (int i = 0; i < _blocs.size(); i++)
	{
		_blocs[i]->Move(dir);
	}
}

bool BlocGroup::Rorate(Grid plateau) {
	return false;
}

bool BlocGroup::CanMove(Grid plateau, sf::Vector2f dir)
{
	for (int i = 0; i < _blocs.size(); i++)
	{
		if (!plateau.CanMove(_blocs[i]->gridX + dir.x, _blocs[i]->gridY + dir.y)) return false;
	}
	return true;
}
