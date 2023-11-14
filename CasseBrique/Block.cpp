#include "Block.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Block::Block(sf::Vector2f new_size, sf::RenderWindow* new_window, int new_HP)
	: GameObject("rectangle", new_size, new_window, 0.0f) {
	HP = new_HP;
}

int Block::onCollisionEnter(AABB a, AABB b) {
	std::cout << "HP: " << HP << "\n";
	HP -= 1;
	return 0;
}

void Block::Update(float deltaTime) {
	GameObject::Update(deltaTime);
	std::cout << "HP: " << HP << "\n";
	//if (HP <= 0) {
	//	return 1;
	//}
	//else {
	//	return 0;
	//}
}