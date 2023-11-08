#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

class Canon
{
public:
	float rotation_speed;
	float rotation_angle;
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Color color;
	sf::RenderWindow* window;
	sf::RectangleShape rectangle;


	Canon(float new_rotation_speed, sf::Color new_color);
	void LookAt(float x, float y);
	void Draw();
	void Rotate(float angle);
	~Canon();
};

