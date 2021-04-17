#include "Bloc.h";
#include <iostream>

Bloc::Bloc() :worldX(0), worldY(0), localX(0), localY(0)
{

}

Bloc::~Bloc()
{
	std::cout << "Destroyed\n";
}

void Bloc::Initialize(const sf::Texture& texture) {
	_entity.Initialize(texture);
	_entity.scale = sf::Vector2f(4,4);

	SetPosition(GridX(), GridY());
}

void Bloc::SetPosition(int gridX, int gridY) 
{
	this->worldX = gridX;
	this->worldY = gridY;

	_entity.position.x = GridX() * (_entity.scale.x * 8);
	_entity.position.y = GridY() * (_entity.scale.y * 8);
	
}

void Bloc::Move(const sf::Vector2f dir)
{
	SetPosition(dir.x + worldX, dir.y + worldY);
}

void Bloc::MoveLocal(const sf::Vector2f dir)
{
	localX += dir.x;
	localY += dir.y;
}
