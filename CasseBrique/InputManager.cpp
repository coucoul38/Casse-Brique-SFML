#include "InputManager.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include <iostream> 
#include "Canon.h"

InputManager::InputManager(sf::RenderWindow* window)
{
	oWindow = window;
	getMousePosition(window);
}

int InputManager::isMousePressed() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return 1;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		return 2;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		return 3;
	}
	return 0;
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow* window) {
	return sf::Mouse::getPosition(*window);
}

InputManager::~InputManager()
{
}