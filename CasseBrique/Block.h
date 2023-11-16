#pragma once
#include "GameObject.h"

class Block : public GameObject
{
private:
	int m_HP;

public:
	
	Block(float x, float y, float width, float height, int HP, sf::RenderWindow* window);
	void setHP(int HP);
	int onCollisionEnter(AABB a, AABB b) override;
};