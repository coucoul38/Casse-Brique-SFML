#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Ball;

class Canon : public GameObject
{
private:
	Ball* ball;

public:
	float rotation_speed;

	Canon(float x, float y, float width, float height, sf::RenderWindow* window);
	int Update(float deltaTime) override;
	void LookAt(sf::Vector2i mousePos);
	void Shoot(bool rainbow);
	void ShootSecondary(std::vector<GameObject*>* gameObjectsList);

	Ball* GetBall();

	bool HasBall();

	~Canon();
};

