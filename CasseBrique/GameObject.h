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
	sf::Vector2f velocity;
	float speed;
	float rotation;
	std::string shape;

	sf::RenderWindow* window;

	GameObject(std::string new_shape, sf::Vector2f new_size, sf::RenderWindow* new_window);
	void Move();
	int Draw();
	bool IsCollision(GameObject object2);

	void Update() {
		this->Move();
		this->Draw();
	}

	~GameObject();
};