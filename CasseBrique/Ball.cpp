#include "Ball.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Ball::Ball(sf::Vector2f new_size, sf::RenderWindow* new_window, float new_speed)
	: GameObject("circle", new_size, new_window, new_speed){
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
		direction.x = -direction.x;
		//color = sf::Color(0, 255, 0, 255);
		return 2;
	}
	else {
		//horizontal collision
		direction.y = -direction.y;
		//color = sf::Color(0, 0, 255, 255);
		return 3;
	}
}