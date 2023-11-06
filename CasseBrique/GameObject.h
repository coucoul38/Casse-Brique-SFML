#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>


class GameObject
{
public:
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Color color;
	sf::Vector2f acceleration;
	float speed;
	float rotation;
	std::string shape;

	GameObject(std::string new_shape, sf::Vector2f new_size);
	int Move(int x, int y);
	int ChangeColor(sf::Color new_color);
	int Resize(sf::Vector2f new_size);
	int Draw(sf::RenderWindow* window);
	bool IsCollision(GameObject object2);
	~GameObject();
};