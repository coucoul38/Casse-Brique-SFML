#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cstddef>
#include <iostream>

GameObject::GameObject(std::string new_shape, sf::Vector2f new_size, sf::RenderWindow* new_window) {
	shape = new_shape;
	size = new_size;
	window = new_window;
}

int GameObject::Draw() {
	sf::Vector2f posMax;

	if (shape=="circle") {
		float radius = std::max(size.x,size.y)/2;
		std::size_t pointCount = 30;
		sf::CircleShape circle = sf::CircleShape::CircleShape(radius, pointCount);

		circle.setFillColor(color);
		circle.setPosition(pos);

		//create AABB bounding box
		posMax.x = pos.x + radius*2;
		posMax.y = pos.y + radius*2;
		bounding_box.min = pos;
		bounding_box.max = posMax;

		window->draw(circle);
	}
	else if (shape == "rectangle") {
		rectangle = sf::RectangleShape::RectangleShape(size);
		rectangle.setFillColor(color);
		rectangle.setPosition(pos);
		rectangle.setOrigin(size.x/2,0);
		rectangle.setRotation(rotation_angle);

		//create AABB bounding box
		posMax.x = pos.x + size.x;
		posMax.y = pos.y + size.y;
		bounding_box.min = pos;
		bounding_box.max = posMax;

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

void GameObject::Teleport(int x, int y) {
	pos.x = x;
	pos.y = y;
}

void GameObject::Rotate(float angle) {
	rotation_angle += angle;
}

bool GameObject::AABBCollision(AABB external_bounding_box){
	bool colliding = false;

	AABB a = bounding_box;
	AABB b = external_bounding_box;
	float d1x = b.min.x - a.max.x;
	float d1y = b.min.y - a.max.y;
	float d2x = a.min.x - b.max.x;
	float d2y = a.min.y - b.max.y;

	if (d1x > 0.0f || d1y > 0.0f) {
		colliding = false;
		color = sf::Color(255, 0, 0, 255);
		return true;
	}

	if (d2x > 0.0f || d2y > 0.0f) {
		colliding = false;
		color = sf::Color(255, 0, 0, 255);
		return false;
	}
		
	color = sf::Color(0, 255, 0, 255);
	return true;
}

bool GameObject::CheckOutOfBounds(){
	sf::Vector2u windowSize = window->getSize();
	if (pos.x >= windowSize.x || pos.x <= 0 || pos.y >= windowSize.y || pos.y <= 0){
		return true;
	}
	return false;
}

GameObject::~GameObject() {
}