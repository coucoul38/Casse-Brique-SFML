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

void InputManager::isMousePressed(std::vector<GameObject> gameObjectsList) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mouse_pos = this->getMousePosition(oWindow);
		sf::Vector2f size(100.0f, 100.0f);

		GameObject ball("circle", size, oWindow);
		ball.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
		ball.velocity = sf::Vector2f(1.0f, 0.0f);
		gameObjectsList.push_back(ball);
		system("cls");
		std::cout << "Created ball at " << mouse_pos.x << ", " << mouse_pos.y << "\n";
	}
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow* window) {
	return sf::Mouse::getPosition(*window);
}

InputManager::~InputManager()
{
}