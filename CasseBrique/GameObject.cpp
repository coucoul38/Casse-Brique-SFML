#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cstddef>
#include <iostream>
#include "Math.h"

GameObject::GameObject(std::string new_shape, sf::Vector2f new_size, sf::RenderWindow* new_window, float new_speed) {
	shape = new_shape;
	size = new_size;
	window = new_window;
	speed = new_speed;
	//initialize bounding box
	sf::Vector2f posMax;
	float radius = std::max(size.x, size.y) / 2;
	if (shape == "circle") {
		posMax.x = pos.x + radius * 2;
		posMax.y = pos.y + radius * 2;
		bounding_box.min = pos;
		bounding_box.max = posMax;
	}
	else {
		posMax.x = pos.x + size.x;
		posMax.y = pos.y + size.y;
		bounding_box.min = pos;
		bounding_box.max = posMax;
	}
	rectangle.setOrigin(size.x / 2, 0);
}

int GameObject::Draw() {
	if (shape=="circle") {
		float radius = std::max(size.x,size.y)/2;
		std::size_t pointCount = 30;
		sf::CircleShape circle = sf::CircleShape::CircleShape(radius, pointCount);
		circle.setFillColor(color);
		circle.setPosition(pos);
		window->draw(circle);
	}
	else if (shape == "rectangle") {
		rectangle = sf::RectangleShape::RectangleShape(size);
		rectangle.setFillColor(color);
		rectangle.setPosition(pos);
		rectangle.setRotation(rotation_angle);

		window->draw(rectangle);
	}
	else {
		return -1;
	}
	return 0;
}

void GameObject::Move(float deltaTime) {
	normalized_direction = Math::normalize(direction);
	
	pos.x += normalized_direction.x * deltaTime * speed;
	pos.y += normalized_direction.y * deltaTime * speed;

	//update bounding box
	sf::Vector2f posMax;
	float radius = std::max(size.x, size.y) / 2;
	if (shape == "circle") {
		posMax.x = pos.x + radius * 2;
		posMax.y = pos.y + radius * 2;
		bounding_box.min = pos;
		bounding_box.max = posMax;
	}
	else {
		posMax.x = pos.x + size.x;
		posMax.y = pos.y + size.y;
		bounding_box.min = pos;
		bounding_box.max = posMax;
	}
}

void GameObject::Teleport(int x, int y) {
	pos.x = x;
	pos.y = y;

	//update bounding box
	sf::Vector2f posMax;
	float radius = std::max(size.x, size.y) / 2;
	if (shape == "circle") {
		posMax.x = pos.x + radius * 2;
		posMax.y = pos.y + radius * 2;
		bounding_box.min = pos;
		bounding_box.max = posMax;
	}
	else {
		posMax.x = pos.x + size.x;
		posMax.y = pos.y + size.y;
		bounding_box.min = pos;
		bounding_box.max = posMax;
	}
}

int GameObject::Update(float deltaTime) {
	//collidedWith.clear();
	this->Move(deltaTime);
	this->Draw();
	return 0;
}

void GameObject::Rotate(float angle) {
	rotation_angle += angle;
}

int GameObject::AABBCollision(GameObject* otherObject){
	AABB a = bounding_box;
	AABB b = otherObject->bounding_box;

	float d1x = b.min.x - a.max.x;
	float d1y = b.min.y - a.max.y;
	float d2x = a.min.x - b.max.x;
	float d2y = a.min.y - b.max.y;
	//system("cls");
	if (d1x > 0.0f || d1y > 0.0f) {
		auto it = std::find(collidedWith.begin(), collidedWith.end(), otherObject);
		if (it != collidedWith.end()) 
		{
			this->onCollisionExit(a, b);
			collidedWith.erase(it);
		}
		return 0;
	}

	if (d2x > 0.0f || d2y > 0.0f) {
		auto it = std::find(collidedWith.begin(), collidedWith.end(), otherObject);
		if (it != collidedWith.end()) 
		{
			this->onCollisionExit(a, b);
			collidedWith.erase(it);
		}
		return 0;
	}

	//COLISION

	auto it = std::find(collidedWith.begin(), collidedWith.end(), otherObject);
	if (it != collidedWith.end()) 
	{
		this->onCollisionStay(a, b);
		return 0;
	}
	
	//if not already collided with that object
	collidedWith.push_back(otherObject);

	return this->onCollisionEnter(a, b);
}

bool GameObject::CheckOutOfBounds(){
	sf::Vector2u windowSize = window->getSize();

	if (pos.x >= windowSize.x ||( pos.x + size.x) <= 0 || pos.y >= windowSize.y || (pos.y + size.y) <= 0){
		return true;
	}
	/*if (pos.y > windowSize.y) {
		return true;
	}*/

	return false;
}

GameObject::~GameObject() {
}