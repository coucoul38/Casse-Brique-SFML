#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Canon : public GameObject
{
public:
	float rotation_speed;

	Canon(float new_rotation_speed, sf::Vector2f new_size, sf::RenderWindow* new_window);
	int Update(float deltaTime) override;
	void LookAt(sf::Vector2i mousePos);
	void Shoot(std::vector<GameObject*>* gameObjectsList, bool rainbow);
	void ShootSecondary(std::vector<GameObject*>* gameObjectsList);
	~Canon();
};

