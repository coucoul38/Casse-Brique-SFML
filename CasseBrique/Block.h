#pragma once
#include "GameObject.h"

class Block : public GameObject
{
private:
	int HP;
public:
	Block(sf::Vector2f new_size, sf::RenderWindow* new_window, int new_HP);
	int Update(float deltaTime) override;
	int AABBCollision(GameObject* otherObject) override;
	int onCollisionEnter(AABB a, AABB b) override;
};