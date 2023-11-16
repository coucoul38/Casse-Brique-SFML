#include "Canon.h"
#include <iostream>
#include <math.h>
#include "Math.h"
#include "Ball.h"
#include "Block.h"

Canon::Canon(float x, float y, float width, float height, sf::RenderWindow* window)
	:GameObject(x, y, width, height, 0.f, window) {
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

void Canon::Shoot(bool rainbow) {
	
	if (HasBalls())
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
}
void Canon::ShootSecondary(std::vector<GameObject*>* gameObjectsList) {
	sf::Vector2f size(500, 10);
	sf::Vector2f position = getPosition(0.5f, 1.f);
	Block* block = new Block(position.x, position.y, size.x, size.y, -1, m_window);
	//sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
	block->setColor(sf::Color(255, 255, 255, 255));
	//block->rectangle.setOrigin(size.x / 2, size.y / 2);
	//block->Teleport(pos.x - size.x, pos.y - size.y);
	//ball->setOrigin(size.x, size.y

	block->setDirection(m_direction);
	//block->direction = sf::Vector2f(cos(Math::degToRad(rotation_angle + 90)), sin(Math::degToRad(rotation_angle + 90)));
	//block->speed = 2000.0f;
	gameObjectsList->push_back(block);
}


std::vector<Ball*>& Canon::GetBalls()
{
	return balls;
}

Canon::~Canon() {
}