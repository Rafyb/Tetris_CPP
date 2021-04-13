#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public :
		sf::Vector2f position;
		sf::Vector2f scale;

		void Initialize(const sf::Texture& texture);
		void Draw(sf::RenderWindow& window);
	
private :
	sf::Sprite _sprite;
};