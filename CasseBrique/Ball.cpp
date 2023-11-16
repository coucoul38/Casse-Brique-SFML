#include "Ball.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Ball::Ball(float x, float y, float radius, float speed, sf::RenderWindow* window)
	: GameObject(x, y, radius, speed, window){
}

int Ball::onCollisionEnter(AABB a, AABB b){
	float difXright = (a.min.x - b.max.x);
	float difXleft = (a.max.x - b.min.x);
	float difX = std::min(abs(difXleft), abs(difXright));

	float difYbottom = (a.min.y - b.max.y);
	float difYtop = (a.max.y - b.min.y);
	float difY = std::min(abs(difYtop), abs(difYbottom));

	if (difX < difY) {
		//vertical collision
		multiplyDirection(-1, 1);
		//color = sf::Color(0, 255, 0, 255);
		return 2;
	}
	else {
		//horizontal collision

		multiplyDirection(1, -1);
		//color = sf::Color(0, 0, 255, 255);
		return 3;
	}
}