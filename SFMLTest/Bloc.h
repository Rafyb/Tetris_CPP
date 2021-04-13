#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Constants.h"

class Bloc 
{
public :
	inline Entity& GetEntity()
	{
		return _entity;
	}
	int gridX;
	int gridY;

	Bloc();
	~Bloc();
	void Initialize(const sf::Texture& texture);
	void SetPosition(int gridX, int gridY);
	void Move(const sf::Vector2f dir);
	void UpdateStep();
	

private:
	Entity _entity;
};