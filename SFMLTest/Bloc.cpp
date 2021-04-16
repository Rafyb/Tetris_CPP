#include "Bloc.h";
#include <iostream>

Bloc::Bloc() :gridX(0), gridY(-1)
{

}

Bloc::~Bloc()
{
	std::cout << "Destroyed\n";
}

void Bloc::Initialize(const sf::Texture& texture) {
	_entity.Initialize(texture);
	_entity.scale = sf::Vector2f(4,4);

	SetPosition(gridX, gridY);
}

void Bloc::SetPosition(int gridX, int gridY) 
{
	this->gridX = gridX;
	this->gridY = gridY;

	_entity.position.y = gridY * (_entity.scale.y * 8);
	_entity.position.x = gridX * (_entity.scale.x * 8);
}

void Bloc::Move(const sf::Vector2f dir)
{
	SetPosition(dir.x + gridX, dir.y + gridY);	
}

void Bloc::UpdateStep()
{
	Move(sf::Vector2f(0, 1));
}
