#include "Block.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Block::Block(sf::Vector2f new_size, sf::RenderWindow* new_window, int new_HP)
	: GameObject("rectangle", new_size, new_window, 0.0f) {
	color = sf::Color(100, 255, 100, 255);
	HP = new_HP;
}

int Block::onCollisionEnter(AABB a, AABB b) {
	std::cout << "HP: " << HP << "\n";
	HP -= 1;
	switch (HP)
	{
	case 3:
		color = sf::Color(100, 255, 100, 255);
	case 2:
		color = sf::Color(255, 255, 0, 255);
	case 1:
		color = sf::Color(0, 255, 0, 255);
	case 0:
		color = sf::Color(255, 0, 0, 255);
		return 1;
	default:
		return 0;
	}
	return 0;
}

int Block::Update(float deltaTime) {
	GameObject::Update(deltaTime);
	return 0;
}