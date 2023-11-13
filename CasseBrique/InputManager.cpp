#include "InputManager.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include <iostream> 
#include "Ball.h"

InputManager::InputManager(sf::RenderWindow* window, GameObject* in_ball)
{
	oWindow = window;
	getMousePosition(window);
	ball = in_ball;
}

void InputManager::isMousePressed(std::vector<GameObject>* gameObjectsList) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mouse_pos = this->getMousePosition(oWindow);
		sf::Vector2f size(100.0f, 100.0f); 
		

		Ball* ball=new Ball(size, oWindow,100.0f); 
		ball->color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255); 
		float radius = std::max(size.x, size.y) / 2;
		ball->Teleport(mouse_pos.x-radius, mouse_pos.y-radius);
		ball->direction = sf::Vector2f(0.0f, -1.0f);
		//ball->speed = 100.0f;
		gameObjectsList->push_back(*ball);
	}
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow* window) {
	return sf::Mouse::getPosition(*window);
}

InputManager::~InputManager()
{
}