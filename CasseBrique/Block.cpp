#include "Block.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Block::Block(sf::Vector2f new_size, sf::RenderWindow* new_window, int new_HP)
	: GameObject("rectangle", new_size, new_window, 0.0f) {
	HP = new_HP;
	switch (HP)
	{
	case 9:
		color = sf::Color(221, 215, 141, 255);
		break;
	case 8:
		color = sf::Color(30,30,30, 255);
		break;
	case 7:
		color = sf::Color(0, 0, 83, 255);
		break;
	case 6:
		color = sf::Color(70, 0, 55, 255);
		break;
	case 5:
		color = sf::Color(255, 0, 0, 255);
		break;
	case 4:
		color = sf::Color(255, 100, 0, 255);
		break;
	case 3:
		color = sf::Color(221, 164, 88, 255);
		break;
	case 2:
		color = sf::Color(221, 215, 55, 255);
		break;
	case 1:
		color = sf::Color(0, 255, 0, 255);
		break;
	case 0:
		color = sf::Color(0, 0, 0, 255);
		break;
	default:
		break;
	}
}

int Block::onCollisionEnter(AABB a, AABB b) {
	//std::cout << "HP: " << HP << "\n";
	HP -= 1;
	switch (HP)
	{
	case 9:
		color = sf::Color(221, 215, 141, 255);
		break;
	case 8:
		color = sf::Color(30, 30, 30, 255);
		break;
	case 7:
		color = sf::Color(0, 0, 83, 255);
		break;
	case 6:
		color = sf::Color(70, 0, 55, 255);
		break;
	case 5:
		color = sf::Color(255, 0, 0, 255);
		break;
	case 4:
		color = sf::Color(255, 100, 0, 255);
		break;
	case 3:
		color = sf::Color(221, 164, 88, 255);
		break;
	case 2:
		color = sf::Color(221, 215, 55, 255);
		break;
	case 1:
		color = sf::Color(0, 255, 0, 255);
		break;
	case 0:
		color = sf::Color(0, 0, 0, 255);
		return 1;
	default:
		break;
	}
	return 0;
}

int Block::Update(float deltaTime) {
	GameObject::Update(deltaTime);
	return 0;
}