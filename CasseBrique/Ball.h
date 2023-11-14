#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball(sf::Vector2f new_size, sf::RenderWindow* new_window, float new_speed);
	int onCollisionEnter(AABB a, AABB b) override;
};