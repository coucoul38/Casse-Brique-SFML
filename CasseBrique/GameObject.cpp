#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cstddef>
#include <iostream>
#include "Math.h"

GameObject::GameObject(float x, float y, float width, float height, float speed, sf::RenderWindow* window) 
{
	//RECTANGLE
	m_shape = new sf::RectangleShape(sf::Vector2f(width, height));
	m_speed = speed;
	m_size.x = width;
	m_size.y = height;

	m_window = window;

	setPosition(x, y,0,0);
}

GameObject::GameObject(float x, float y, float radius, float speed, sf::RenderWindow* window)
{
	//CIRCLE
	m_shape = new sf::CircleShape(radius);
	m_speed = speed;
	m_size.x = radius * 2;
	m_size.y = radius * 2;

	m_window = window;

	setPosition(x, y);
}


void GameObject::setPosition(float x, float y, float ratioX, float ratioY)
{
	float originX = ratioX * m_size.x;
	float originY = ratioY * m_size.y;

	m_shape->setOrigin(originX, originY);
	m_shape->setPosition(x, y);

	m_bounding_box.min.x = x - originX;
	m_bounding_box.min.y = y - originY;
	m_bounding_box.max.x = m_bounding_box.min.x + m_size.x;
	m_bounding_box.max.y = m_bounding_box.min.y + m_size.y;
}


sf::Vector2f GameObject::getPosition(float ratioX, float ratioY)
{
	sf::Vector2f origin = m_shape->getOrigin();
	sf::Vector2f position = m_shape->getPosition();

	position.x -= origin.x;
	position.y -= origin.y;

	float originX = ratioX * m_size.x;
	float originY = ratioY * m_size.y;

	position.x += originX;
	position.y += originY;

	return position;
}

void GameObject::setDirection(sf::Vector2f direction)
{
	m_direction = Math::normalize(direction);
}

void GameObject::multiplyDirection(float x, float y)
{
	m_direction.x *= x;
	m_direction.y *= y;
}

void GameObject::setColor(sf::Color color) 
{
	m_shape->setFillColor(color);
}

void GameObject::setSpeed(float speed) {
	m_speed = speed;
}

void GameObject::Draw()
{
	m_window->draw(*m_shape);
}

void GameObject::Move(float deltaTime) {
	sf::Vector2f position = getPosition();

	position += m_direction * deltaTime * m_speed;

	setPosition(position.x, position.y);
}

int GameObject::Update(float deltaTime) {
	//collidedWith.clear();
	this->Move(deltaTime);
	this->Draw();
	return 0;
}

void GameObject::Rotate(float angle) {
	m_angle += angle;
}

int GameObject::AABBCollision(GameObject* otherObject){
	AABB a = m_bounding_box;
	AABB b = otherObject->m_bounding_box;

	float d1x = b.min.x - a.max.x;
	float d1y = b.min.y - a.max.y;
	float d2x = a.min.x - b.max.x;
	float d2y = a.min.y - b.max.y;

	//system("cls");
	if (d1x > 0.0f || d1y > 0.0f) {
		auto it = std::find(m_collidedWith.begin(), m_collidedWith.end(), otherObject);
		if (it != m_collidedWith.end())
		{
			this->onCollisionExit(a, b);
			m_collidedWith.erase(it);
		}
		return 0;
	}

	if (d2x > 0.0f || d2y > 0.0f) {
		auto it = std::find(m_collidedWith.begin(), m_collidedWith.end(), otherObject);
		if (it != m_collidedWith.end())
		{
			this->onCollisionExit(a, b);
			m_collidedWith.erase(it);
		}
		return 0;
	}

	//COLISION

	auto it = std::find(m_collidedWith.begin(), m_collidedWith.end(), otherObject);
	if (it != m_collidedWith.end())
	{
		this->onCollisionStay(a, b);
		return 0;
	}
	
	//if not already collided with that object
	m_collidedWith.push_back(otherObject);

	return this->onCollisionEnter(a, b);
}

bool GameObject::CheckOutOfBounds(){
	sf::Vector2u windowSize = m_window->getSize();
	return (m_bounding_box.min.x >= windowSize.x || m_bounding_box.max.x <= 0 || m_bounding_box.min.y >= windowSize.y || m_bounding_box.max.y <= 0);
}

GameObject::~GameObject() {
}