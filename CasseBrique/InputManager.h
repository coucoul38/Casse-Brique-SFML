#pragma once
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include "Canon.h"

class InputManager
{
public:
	sf::RenderWindow* oWindow;
	InputManager(sf::RenderWindow* window);
	int isMousePressed();
	//std::string text, int (*func)(std::string text)
	sf::Vector2i getMousePosition(sf::RenderWindow* window);
	~InputManager();

private:
	sf::Vector2i mousePosition;
};

