
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputManager.h"
#include <iostream> 

int main(int argc, char** argv)
{
    std::vector<GameObject> gameObjectList;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(640, 480), "SFML", sf::Style::Default, settings);

    //Création d'un cercle de radius 100
    sf::CircleShape oCircle(100.f);
    oCircle.setPosition(0.f, 0.f);
    oCircle.setFillColor(sf::Color::Green);

    sf::Vector2f size(100, 10);
    GameObject oCircleObject("circle",size,&oWindow);
    GameObject oRectangleObject("rectangle",size,&oWindow);
    sf::RectangleShape rectangle(size);

    oRectangleObject.pos = sf::Vector2f(200, 300);
    oCircleObject.pos = sf::Vector2f(0, 0);
    oCircleObject.velocity = sf::Vector2f(0.0f,0.01f);

    sf::Color color(255, 100, 200, 255);
    oCircleObject.color = color;
    oRectangleObject.color = color;

    gameObjectList.push_back(oRectangleObject);
    gameObjectList.push_back(oCircleObject);

    InputManager testInputManager(&oWindow);

    //GameLoop
    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
        }

		//Input Manager
		testInputManager.isMousePressed(gameObjectList);

        //Update every GameObject
        oWindow.clear();
        for (int i = 0; i < gameObjectList.size(); i++)
        {
            gameObjectList[i].Update();
        }
        GameObject ball("circle", size, &oWindow);
        ball.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
        ball.velocity = sf::Vector2f(1.0f,0.0f);
        gameObjectList.push_back(ball);

        oRectangleObject.AABBCollision(oCircleObject.bounding_box);
        oCircleObject.AABBCollision(oRectangleObject.bounding_box);


        oWindow.display();
    }

    return 0;
}


