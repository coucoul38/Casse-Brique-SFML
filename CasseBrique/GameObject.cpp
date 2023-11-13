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
	normalized_direction = Math::normalize(direction);
	
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

	float d1x = b.min.x - a.max.x;
	float d1y = b.min.y - a.max.y;
	float d2x = a.min.x - b.max.x;
	float d2y = a.min.y - b.max.y;
	//system("cls");
	if (d1x > 0.0f || d1y > 0.0f) {
		//color = sf::Color(255, 0, 0, 255);
		auto it = std::find(collidedWith.begin(), collidedWith.end(), otherObject);
		if (it != collidedWith.end()) 
		{
			//TODO Call "OnCollisionExit"
			std::cout << "Collision Exit\n";
			collidedWith.erase(it);
		}
		
		return 0;
	}

	if (d2x > 0.0f || d2y > 0.0f) {
		//color = sf::Color(255, 0, 0, 255);
		auto it = std::find(collidedWith.begin(), collidedWith.end(), otherObject);
		if (it != collidedWith.end()) 
		{
			//TODO Call "OnCollisionExit"
			std::cout << "Collision Exit\n";
			collidedWith.erase(it);
		}

		return 0;
	}

	//COLISION
	//trying to detect collisionEnter and exit, not working

	auto it = std::find(collidedWith.begin(), collidedWith.end(), otherObject);
	if (it != collidedWith.end()) 
	{
		//TODO Call "OnCollisionStay"
		return 0;
	}
	
	//if not already collided with that object
	//std::cout << "Collision entered\n";
	collidedWith.push_back(otherObject);
	

	//TODO Call "OnCollisionEnter"
	std::cout << "Collision Entered\n";

	//TODO put into class Ball
	float difXright = (a.min.x - b.max.x);
	float difXleft = (a.max.x - b.min.x);
	float difX = std::min(abs(difXleft), abs(difXright));

	float difYbottom = (a.min.y - b.max.y);
	float difYtop = (a.max.y - b.min.y);
	float difY = std::min(abs(difYtop), abs(difYbottom));

	if (difX < difY) {
		//vertical collision
		direction.x = -direction.x;
		return 2;
	}
	else {
		//horizontal collision
		direction.y = -direction.y;
		return 3;
	}
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