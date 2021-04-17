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
	inline int GridX()
	{
		return worldX + localX;
	}
	inline int GridY()
	{
		return worldY + localY;
	}

	int worldX;
	int worldY;

	int localX;
	int localY;

	Bloc();
	~Bloc();
	void Initialize(const sf::Texture& texture);
	void SetPosition(int gridX, int gridY);
	void Move(const sf::Vector2f dir);
	void MoveLocal(const sf::Vector2f dir);
	

private:
	Entity _entity;
};