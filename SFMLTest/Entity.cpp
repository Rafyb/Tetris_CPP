#include "Entity.h"

void Entity::Initialize(const sf::Texture& texture)
{
	scale = sf::Vector2f(1, 1);
	_sprite.setTexture(texture);
}

void Entity::Draw(sf::RenderWindow& window)
{
	_sprite.setPosition(position);
	_sprite.setScale(scale);
	window.draw(_sprite);
}
