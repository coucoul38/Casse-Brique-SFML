#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
class GameObject
{
private:
	sf::Vector2f acceleration;
	float speed;
	float rotation;
public:
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Color color;

	GameObject();
	int Move();
	int ChangeColor();
	~GameObject();
};

