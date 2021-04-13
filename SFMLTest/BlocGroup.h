#pragma once
#include <SFML/Graphics.hpp>
#include "Bloc.h"
#include "Constants.h"

class BlocGroup
{
public:

	sf::Vector2f BotRight;
	sf::Vector2f TopLeft;

	BlocGroup();

	void Initialize(const sf::Texture& texture, const char* form[]);

	void Move(const sf::Vector2f dir);
	void Rorate(const int angle);

	void UpdateStep();


private:
	Bloc _blocs [4][4];
};