#include "Block.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Block::Block(sf::Vector2f new_size, sf::RenderWindow* new_window, int new_HP)
	: GameObject("rectangle", new_size, new_window, 0.0f) {
	HP = new_HP;
}

int Block::AABBCollision(GameObject* otherObject) {
	GameObject::AABBCollision(otherObject);
	return 0;
}

int Block::onCollisionEnter(AABB a, AABB b) {
	std::cout << "HP: " << HP << "\n";
	HP -= 1;
	return 0;
}

int Block::Update(float deltaTime) {
	Draw();
	Move(deltaTime);
	std::cout << "HP: " << HP << "\n";
	if (HP <= 0) {
		return 1;
	}
	else {
		return 0;
	}
}