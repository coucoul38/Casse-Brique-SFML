#include "Math.h"
#include <math.h>
namespace Math {
	sf::Vector2f normalize(sf::Vector2f direction) {
		sf::Vector2f normalized_direction;
		float norm = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (norm != 0.0f) {
			normalized_direction = sf::Vector2f(direction.x / norm, direction.y / norm);
		}
		return(normalized_direction);
	}

	bool between(int x, int a, int b) {
		if (x >= b)
			return false;
		if (x <= a)
			return false;
		return true;
	}

	bool between(float x, float a, float b) {
		if (x >= b)
			return false;
		if (x <= a)
			return false;
		return true;
	}

	float findAngle(sf::Vector2f vect1, sf::Vector2f vect2) {
		
	}
}