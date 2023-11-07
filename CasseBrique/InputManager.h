#pragma once
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"

class InputManager
{
public:
	void isMousePressed(int (*func)());
	void getMousePosition(sf::RenderWindow* window);
	InputManager(sf::RenderWindow* window);
	~InputManager();

private:
	sf::Vector2i mousePosition;
};

