#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball(float x, float y, float radius, float speed, sf::RenderWindow* window);
	int onCollisionEnter(AABB a, AABB b) override;
};