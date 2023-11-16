#pragma once
#include <SFML/System/Vector2.hpp>

namespace Math {
	sf::Vector2f normalize(sf::Vector2f vector);

	bool between(int x, int a, int b);
	bool between(float x, float a, float b);

	float findAngle(sf::Vector2f vect1, sf::Vector2f vect2);

	float degToRad(float degrees);
	float radToDeg(float radians);

	//float round(float number, int digits=2);

	float getNorm(sf::Vector2f);
}

