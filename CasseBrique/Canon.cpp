#include "Canon.h"
#include <iostream>
#include <math.h>
#include "Math.h"
#include "Ball.h"

Canon::Canon(float new_rotation_speed, sf::Vector2f new_size, sf::RenderWindow* new_window) 
	:GameObject("rectangle", new_size, new_window, 0.0f) {
	//size = sf::Vector2f(100, 10);
	size = new_size;
	window = new_window;
	rectangle.setOrigin(size.x, 0);

	pos.x = window->getSize().x/2;
	pos.y = window->getSize().y;
}

int Canon::Update(float deltaTime) {
	GameObject::Update(deltaTime);
	return 0;
}

void Canon::LookAt(sf::Vector2i mousePos) {
	sf::Vector2f oppositeCoordinates(mousePos.x - pos.x, window->getSize().y - mousePos.y);
	sf::Vector2f adjacentCoordinates(mousePos.x - pos.x, pos.y);
	
	float opposite = Math::getNorm(oppositeCoordinates);
	float adjacent = Math::getNorm(adjacentCoordinates);

	float angle = atan2(mousePos.x - pos.x, mousePos.y - pos.y);
	rotation_angle = -Math::radToDeg(angle);
}

void Canon::Shoot(std::vector<GameObject*>* gameObjectsList) {
	sf::Vector2f size(20, 20);
	Ball* ball = new Ball(size, window, 100.0f);
	ball->color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
	float radius = std::max(size.x, size.y) / 2;
	ball->Teleport(pos.x-size.x, pos.y-size.y);
	//ball->setOrigin(size.x, size.y);
	ball->direction = sf::Vector2f(cos(Math::degToRad(rotation_angle+90)),sin(Math::degToRad(rotation_angle+90)));
	ball->speed = 1000.0f;
	gameObjectsList->push_back(ball);
}

Canon::~Canon() {
}