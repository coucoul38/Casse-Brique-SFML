#include "Canon.h"
#include <iostream>
#include <math.h>
#include "Math.h"

Canon::Canon(float new_rotation_speed, sf::Vector2f new_size, sf::RenderWindow* new_window) 
	:GameObject("rectangle", new_size, new_window, 0.0f) {
	//size = sf::Vector2f(100, 10);
	size = new_size;
	window = new_window;
	rectangle.setOrigin(size.x, size.y);
	pos.x = window->getSize().x/2;
	pos.y = window->getSize().y;
}

void Canon::Update(float deltaTime) {
	GameObject::Update(deltaTime);
}

void Canon::LookAt(sf::Vector2i mousePos) {
	sf::Vector2f oppositeCoordinates(mousePos.x - pos.x, window->getSize().y - mousePos.y);
	sf::Vector2f adjacentCoordinates(mousePos.x - pos.x, pos.y);
	
	float opposite = Math::getNorm(oppositeCoordinates);
	float adjacent = Math::getNorm(adjacentCoordinates);

	float angle = atan2(mousePos.x - pos.x, mousePos.y - pos.y);
	rotation_angle = -Math::radToDeg(angle)+180;
}

Canon::~Canon() {
}