#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <string>

typedef struct
{
	sf::Vector2f min;
	sf::Vector2f max;
} AABB;

class GameObject
{
public:
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Color color;
	sf::Vector2f direction;
	sf::Vector2f normalized_direction;
	float speed;
	//float rotation;
	std::string shape;
	sf::RectangleShape rectangle;
	AABB bounding_box;
	float rotation_angle;
	std::vector<GameObject*> collidedWith;
	std::vector<GameObject*> collidingWith;

	sf::RenderWindow* window;

	GameObject(std::string new_shape, sf::Vector2f new_size, sf::RenderWindow* new_window, float new_speed);
	void Move(float deltaTime);
	void Teleport(int x, int y);
	int Draw();
	int AABBCollision(GameObject* otherObject);

	bool CheckOutOfBounds();
	void Rotate(float angle);
	void Update(float deltaTime);

	~GameObject();
};