
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputManager.h"
#include <iostream> 

int main(int argc, char** argv)
{
    std::vector<GameObject> gameObjectList;
    
    //turn on antialiasing and create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow oWindow(sf::VideoMode(640, 480), "SFML", sf::Style::Default, settings);

    //Création d'un cercle de radius 100
    sf::CircleShape oCircle(100.f);
    oCircle.setPosition(0.f, 0.f);
    oCircle.setFillColor(sf::Color::Green);

    sf::Vector2f size(100, 10);
    GameObject oCircleObject = GameObject("circle",size,&oWindow,10.0f);
    GameObject oRectangleObject = GameObject("rectangle",size,&oWindow,10.0f);

    oRectangleObject.pos = sf::Vector2f(200, 300);
    oCircleObject.pos = sf::Vector2f(0, 0);
    oCircleObject.velocity = sf::Vector2f(0.0f,0.01f);

    sf::Color color(255, 100, 200, 255);
    oCircleObject.color = color;
    oRectangleObject.color = color;

    gameObjectList.push_back(oRectangleObject);
    gameObjectList.push_back(oCircleObject);

    InputManager oTestInputManager(&oWindow);

    sf::Clock oClock;
    float fDeltaTime;
    fDeltaTime = oClock.restart().asSeconds();
    float fTimer = 0.0f;

    //GameLoop
    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
            if (oEvent.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, oEvent.size.width, oEvent.size.height);
                oWindow.setView(sf::View(visibleArea));
            }
        }

		//Input Manager
        if (fTimer >= 0.1f) {
            oTestInputManager.isMousePressed(&gameObjectList);
            fTimer = 0.0f;
        }
        //Update every GameObject
        oWindow.clear();
        for (int i = 0; i < gameObjectList.size(); i++)
        {
            gameObjectList[i].Update(fDeltaTime);
            for (int j = 0; j < gameObjectList.size(); j++) {
                if (j != i) {
                    gameObjectList[i].AABBCollision(gameObjectList[j].bounding_box);
                }
            }
            
            if (gameObjectList[i].CheckOutOfBounds()) {
                gameObjectList.erase(gameObjectList.begin() + i);
            }
        }
        //system("cls");
        //std::cout << "Deltatime:" << fDeltaTime;

        oRectangleObject.AABBCollision(oCircleObject.bounding_box);
        oCircleObject.AABBCollision(oRectangleObject.bounding_box);


        oWindow.display();
        
        fTimer += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();

    }

    return 0;
}


