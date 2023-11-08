#pragma once
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"

class InputManager
{
public:
	sf::RenderWindow* oWindow;
	InputManager(sf::RenderWindow* window);
	void isMousePressed(std::vector<GameObject> gameObjectsList);
	//std::string text, int (*func)(std::string text)
	sf::Vector2i getMousePosition(sf::RenderWindow* window);
	~InputManager();

private:
	sf::Vector2i mousePosition;
};

