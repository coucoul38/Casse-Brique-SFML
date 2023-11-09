
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


    sf::Vector2f size(150, 50);
    sf::Color color(255, 100, 200, 255);

    GameObject oRectangleObject = GameObject("rectangle",size,&oWindow,10.0f);
    oRectangleObject.pos = sf::Vector2f(200, 200);
    oRectangleObject.color = color;
	oRectangleObject.rectangle.setOutlineThickness(1.0f);
    oRectangleObject.rectangle.setOutlineColor(sf::Color(0, 0, 255));

    GameObject oRectangleObject2 = GameObject("rectangle", size, &oWindow, 10.0f);
    oRectangleObject2.pos = sf::Vector2f(500, 400);
    oRectangleObject2.color = color;
        oRectangleObject2.rectangle.setOutlineThickness(1.0f);
    oRectangleObject2.rectangle.setOutlineColor(sf::Color(0, 0, 255));

    gameObjectList.push_back(oRectangleObject);
    gameObjectList.push_back(oRectangleObject2);

    sf::Vector2f size2(100, 100);
    GameObject ball("rectangle", size2, &oWindow,1500.0f);
    ball.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);

    InputManager oTestInputManager(&oWindow, &ball);

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
        ball.color = sf::Color(255, 0, 0, 255);
        for (int i = 0; i < gameObjectList.size(); i++)
        {
            if (ball.AABBCollision(gameObjectList[i].bounding_box)) {
                ball.color = sf::Color(0, 255, 0, 255);
            }

            gameObjectList[i].Update(fDeltaTime);
            for (int j = 0; j < gameObjectList.size(); j++) {
                if (j != i) {
                    sf::Vector2f fDistance(gameObjectList[i].pos.x - gameObjectList[j].pos.x, gameObjectList[i].pos.y - gameObjectList[j].pos.y);
                    float normDistance = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
                    if(normDistance > 0) {
                        gameObjectList[i].AABBCollision(gameObjectList[j].bounding_box);
                    }
                }
                gameObjectList[i].AABBCollision(gameObjectList[j].bounding_box);
            }
            if (gameObjectList[i].CheckOutOfBounds()) {
                gameObjectList.erase(gameObjectList.begin() + i);
            }
        }
        

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*&oWindow);
        ball.Teleport(mouse_pos.x, mouse_pos.y);
        
        ball.Update(fDeltaTime);

        //system("cls");
        //std::cout << "Deltatime:" << fDeltaTime;

        oWindow.display();
        
        fTimer += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}


