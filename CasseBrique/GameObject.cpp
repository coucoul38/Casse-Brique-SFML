#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <cstddef>
#include <iostream>

GameObject::GameObject(std::string new_shape, sf::Vector2f new_size, sf::RenderWindow* new_window) {
	shape = new_shape;
	size = new_size;
	window = new_window;
}

int GameObject::Draw() {
	if (shape=="circle") {
		float radius = std::max(size.x,size.y);
		std::size_t pointCount = 30;
		sf::CircleShape circle = sf::CircleShape::CircleShape(radius, pointCount);

		circle.setFillColor(color);
		circle.setPosition(pos);

		window->draw(circle);
	}
	else if (shape == "rectangle") {
		sf::RectangleShape rectangle = sf::RectangleShape::RectangleShape(size);

		rectangle.setFillColor(color);
		rectangle.setPosition(pos);

		window->draw(rectangle);
	}
	else {
		return -1;
	}
	return 0;
}

void GameObject::Move() {
	pos.x += velocity.x;
	pos.y += velocity.y;
}

bool GameObject::IsCollision(GameObject object2){
	if((pos.x > object2.pos.x + object2.size.x) || (pos.x + size.x <= object2.pos.x) || (pos.y >= object2.pos.y + object2.size.y) || (pos.y + size.y <= object2.pos.y)){
		return false;
	}else{
		return true;
	}
}

GameObject::~GameObject() {
	
}