#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Bloc.h"
#include "Constants.h"


class BlocGroup
{
public:
	inline std::vector<Bloc*> GetBlocs()
	{
		return _blocs;
	}

	int worldX;
	int worldY;

	int size;

	BlocGroup();
	~BlocGroup();

	void Initialize(const sf::Texture& texture, std::vector<Bloc*> blocsTmp);

	void Move(const sf::Vector2f dir);
	bool Rorate(Grid plateau);

	bool UpdateStep(Grid plateau);
	bool CanMove(Grid plateau, sf::Vector2f dir);


private:
	std::vector<Bloc*> _blocs;
};