#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cstddef>
#include <iostream>

GameObject::GameObject(std::string new_shape, sf::Vector2f new_size, sf::RenderWindow* new_window, float new_speed) {
	shape = new_shape;
	size = new_size;
	window = new_window;
	speed = new_speed;
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
		//rectangle.setOrigin(size.x/2,0);
		rectangle.setRotation(rotation_angle);

		//create AABB bounding box
		posMax.x = pos.x + size.x;
		posMax.y = pos.y + size.y;
		bounding_box.min = pos;
		bounding_box.max = posMax;


		//show bounding box on top of shape (funny recolor)
		sf::ConvexShape rectBoundingBox;
		rectBoundingBox.setPointCount(4);
		rectBoundingBox.setPoint(0, bounding_box.min);
		rectBoundingBox.setPoint(1, sf::Vector2f(bounding_box.max.x,bounding_box.min.y));
		rectBoundingBox.setPoint(2, bounding_box.max);
		rectBoundingBox.setPoint(3, sf::Vector2f(bounding_box.min.x, bounding_box.max.y));
		rectBoundingBox.setFillColor(sf::Color(255, 255, 255, 100));
		

		
		window->draw(rectangle);
		window->draw(rectBoundingBox);
	}
	else {
		return -1;
	}
	return 0;
}

void GameObject::Move(float deltaTime) {
	float norm = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (norm != 0.0f) {
		normalized_direction = sf::Vector2f(direction.x / norm, direction.y / norm);
	}
	
	pos.x += normalized_direction.x * deltaTime * speed;
	pos.y += normalized_direction.y * deltaTime * speed;
}

void GameObject::Teleport(int x, int y) {
	pos.x = x;
	pos.y = y;
}

void GameObject::Update(float deltaTime) {
	//collidedWith.clear();
	this->Move(deltaTime);
	this->Draw();
}

void GameObject::Rotate(float angle) {
	rotation_angle += angle;
}

int GameObject::AABBCollision(GameObject* otherObject){
	AABB a = bounding_box;
	AABB b = otherObject->bounding_box;

	collidedWith.clear();
	for (int i = 0; i < collidingWith.size(); i++)
	{
		collidedWith.push_back(collidingWith[i]);
	}
	collidingWith.clear();

	float d1x = b.min.x - a.max.x;
	float d1y = b.min.y - a.max.y;
	float d2x = a.min.x - b.max.x;
	float d2y = a.min.y - b.max.y;

	if (d1x > 0.0f || d1y > 0.0f) {
		//color = sf::Color(255, 0, 0, 255);
		return 0;
	}

	if (d2x > 0.0f || d2y > 0.0f) {
		//color = sf::Color(255, 0, 0, 255);
		return 0;
	}

	//trying to detect collisionEnter and exit, not working
	for (int i = 0; i < collidedWith.size(); i++)
	{
		if (collidedWith[i] == otherObject) {
			//return 0; //for some reasons this disables vertical collsions on the 'ball'
		}
	}
	
	//if not already collided with that object
	collidingWith.push_back(otherObject);
		
		
	sf::Vector2i hitDirection(0, 0);
	float difXright = (a.min.x - b.max.x);
	float difXleft = (a.max.x - b.min.x);
	float difX = std::min(abs(difXleft), abs(difXright));

	float difYbottom = (a.min.y - b.max.y);
	float difYtop = (a.max.y - b.min.y);
	float difY = std::min(abs(difYtop), abs(difYbottom));

	if (difX < difY) {
		direction.x = -direction.x;
		return 2;
	}
	else {
		direction.y = -direction.y;
		return 3;
	}
	
	color = sf::Color(255, 0, 0, 255);
	return 0;
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