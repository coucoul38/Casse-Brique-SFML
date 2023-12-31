#include "Canon.h"
#include <iostream>
#include <math.h>
#include "Math.h"
#include "Ball.h"
#include "Block.h"

Canon::Canon(float x, float y, float width, float height, sf::RenderWindow* window, std::vector<GameObject*>* gameObjectList)
	:GameObject(x, y, width, height, 0.f, window) {
	gameobjects = gameObjectList;
}

int Canon::Update(float deltaTime) {
	GameObject::Update(deltaTime);
	return 0;
}

void Canon::LookAt(sf::Vector2i mousePos) {

	float ratioX = 0.5f;
	float ratioY = 1.f;

	sf::Vector2f position = getPosition(0.5f, 1.f);

	sf::Vector2f direction;
	direction.x = mousePos.x - position.x;
	direction.y = mousePos.y - position.y;

	sf::Vector2f oppositeCoordinates(mousePos.x - position.x, m_window->getSize().y - mousePos.y);
	sf::Vector2f adjacentCoordinates(mousePos.x - position.x, position.y);
	
	float opposite = Math::getNorm(oppositeCoordinates);
	float adjacent = Math::getNorm(adjacentCoordinates);

	float angle = atan2(mousePos.x - position.x, mousePos.y - position.y);

	m_angle = -Math::radToDeg(angle);

	m_shape->setOrigin(ratioX * m_size.x, ratioY * m_size.y);
	m_shape->setRotation(180 + m_angle);

	setDirection(direction);
}


bool Canon::HasBalls()
{
	return (balls.size() > 0);
}

void Canon::Shoot(bool rainbow, bool ultimate) {
	
	if (HasBalls() && !ultimate)
		return;

	Ball* ball = new Ball(-1,-1, 20.f, 500.0f, m_window);

	ball->setColor(sf::Color(255, 255, 255, 255));
	if (rainbow) 
	{
		ball->setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
	}

	sf::Vector2f position = getPosition(0.5f, 1.f);
	position.x += m_direction.x * m_size.y;
	position.y += m_direction.y * m_size.y;
	ball->setPosition(position.x, position.y, 0.5f, 1.f);
	ball->setDirection(m_direction);
	balls.push_back(ball);
	//gameobjects->push_back(ball);
}
void Canon::ShootSecondary() {
	GameObject* arc = new GameObject(-1, -1, 500, 10, 2000.f, m_window);
	arc->setColor(sf::Color(255, 255, 255, 255));

	sf::Vector2f position = getPosition(0.5f, 1.f);
	position.x += m_direction.x * m_size.y;
	position.y += m_direction.y * m_size.y;
	arc->setPosition(position.x, position.y, 0.5f, 1.f);
	arc->setDirection(m_direction);
	//block->direction = sf::Vector2f(cos(Math::degToRad(rotation_angle + 90)), sin(Math::degToRad(rotation_angle + 90)));
	arc->setSpeed(2000.0f);
	gameobjects->push_back(arc);
}


std::vector<Ball*>& Canon::GetBalls()
{
	return balls;
}

Canon::~Canon() {
}