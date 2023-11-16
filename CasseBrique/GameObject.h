#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <iostream>

typedef struct
{
	sf::Vector2f min;
	sf::Vector2f max;
} AABB;

class GameObject
{
protected:
	sf::Vector2f m_size;
	sf::Vector2f m_direction;
	float m_speed;
	AABB m_bounding_box;
	float m_angle;
	std::vector<GameObject*> m_collidedWith;
	sf::RenderWindow* m_window;
	sf::Shape* m_shape;

public:

	GameObject(float x, float y, float width, float height, float speed, sf::RenderWindow* window);
	GameObject(float x, float y, float radius, float speed, sf::RenderWindow* window);

	void setPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	sf::Vector2f getPosition(float ratioX = 0.5f, float ratioY = 0.5f);
	void setDirection(sf::Vector2f direction);
	void multiplyDirection(float x, float y);
	void setColor(sf::Color color);
	void setSpeed(float speed);

	void Move(float deltaTime);
	void Draw();


	bool CheckOutOfBounds();
	void Rotate(float angle);
	
	virtual int Update(float deltaTime);

	int AABBCollision(GameObject* otherObject);
	virtual int onCollisionEnter(AABB a, AABB b) { /*std::cout << "onCollisionEnter" << std::endl;*/ return 0; };
	virtual int onCollisionStay(AABB a, AABB b) { /*std::cout << "onCollisionStay" << std::endl; */ return 0; };
	virtual int onCollisionExit(AABB a, AABB b) { /*std::cout << "onCollisionExit" << std::endl;*/ return 0; };

	~GameObject();
};