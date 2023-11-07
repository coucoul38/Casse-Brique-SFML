#include "InputManager.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"

InputManager::InputManager(sf::RenderWindow* window)
{
	getMousePosition(window);
}

InputManager::~InputManager()
{
}

void InputManager::isMousePressed(int (*func)()) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		(*func)();
	}
}

void InputManager::getMousePosition(sf::RenderWindow* window) {
	mousePosition = sf::Mouse::getPosition(*window);
}
