#include "Canon.h"
#include <iostream>

Canon::Canon(float new_rotation_speed, sf::Vector2f new_size, sf::RenderWindow* new_window) 
	:GameObject("rectangle", new_size, new_window, 0.0f) {
	//size = sf::Vector2f(100, 10);
	size = new_size;
	window = new_window;
	rectangle = sf::RectangleShape(size);
	rectangle.setOrigin(size.x/2, size.y);
	pos.x = window->getSize().x/2;
	pos.y = window->getSize().y-size.y;
}

void Canon::Update(float deltaTime) {
	GameObject::Update(deltaTime);
}

void Canon::LookAt(sf::Vector2i mousePos) {

}

Canon::~Canon() {
}