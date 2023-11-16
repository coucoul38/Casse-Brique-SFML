#include "Block.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Block::Block(float x, float y, float width, float height, int HP, sf::RenderWindow* window)
	: GameObject(x, y, width, height, 0.f, window) {
	setHP(HP);
}

void Block::setHP( int HP )
{
	m_HP = HP;

	switch (m_HP)
	{
	case 9:
		setColor( sf::Color(255, 255, 255, 255) );
		break;
	case 8:
		setColor(sf::Color(50, 50, 50, 255) );
		break;
	case 7:
		setColor(sf::Color(0, 0, 83, 255) );
		break;
	case 6:
		setColor(sf::Color(70, 0, 55, 255) );
		break;
	case 5:
		setColor(sf::Color(255, 0, 0, 255));
		break;
	case 4:
		setColor(sf::Color(255, 100, 0, 255));
		break;
	case 3:
		setColor(sf::Color(221, 164, 88, 255));
		break;
	case 2:
		setColor(sf::Color(221, 215, 55, 255));
		break;
	case 1:
		setColor(sf::Color(0, 255, 0, 255));
		break;
	case 0:
		setColor(sf::Color(0, 0, 0, 255));
		break;
	default:
		break;
	}
}

int Block::onCollisionEnter(AABB a, AABB b) {
	setHP(m_HP - 1);
	return 0;
}
