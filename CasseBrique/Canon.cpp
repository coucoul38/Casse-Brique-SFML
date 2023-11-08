#include "Canon.h"

Canon::Canon(float new_rotation_speed, sf::Color new_color) {
	size = sf::Vector2f(100, 10);
	rectangle = sf::RectangleShape(size);
	pos.x = 0;
	pos.y = 1000 / 2;
}

void Canon::Draw() {
	sf::Vector2f posMax;

	rectangle = sf::RectangleShape::RectangleShape(size);
	rectangle.setFillColor(color);
	rectangle.setPosition(pos);
	rectangle.setOrigin(size.x / 2, 0);
	rectangle.setRotation(rotation_angle);

	window->draw(rectangle);
}

void Canon::Rotate(float angle) {
	rotation_angle += angle;
}

Canon::~Canon() {
	//stuff
}