#include "InputManager.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include <iostream> 

InputManager::InputManager(sf::RenderWindow* window)
{
	oWindow = window;
	getMousePosition(window);
}

void InputManager::isMousePressed(std::vector<GameObject>* gameObjectsList) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mouse_pos = this->getMousePosition(oWindow);
		sf::Vector2f size(100.0f, 100.0f);

		GameObject* ball=new GameObject("circle", size, oWindow,1000.0f);
		ball->color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
		float radius = std::max(size.x, size.y) / 2;
		ball->Teleport(mouse_pos.x-radius, mouse_pos.y-radius);
		ball->velocity = sf::Vector2f(1.0f, 0.0f);
		gameObjectsList->push_back(*ball);
	}
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow* window) {
	return sf::Mouse::getPosition(*window);
}

InputManager::~InputManager()
{
}