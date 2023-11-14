#include "Math.h"
#include <math.h>
namespace Math {
	float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164;
	sf::Vector2f normalize(sf::Vector2f direction) {
		sf::Vector2f normalized_direction;
		float norm = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (norm != 0.0f) {
			normalized_direction = sf::Vector2f(direction.x / norm, direction.y / norm);
		}
		return(normalized_direction);
	}

	float getNorm(sf::Vector2f vector) {
		return(sqrt(vector.x * vector.x + vector.y * vector.y));
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
		return 0;
	}

	float degToRad(float degrees) {
		return degrees * pi / 180;
	}
	float radToDeg(float radians) {
		return radians * 180/pi;
	}
}