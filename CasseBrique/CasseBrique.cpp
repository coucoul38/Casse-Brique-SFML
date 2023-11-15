
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputManager.h"
#include <iostream> 
#include "Block.h"
#include "Canon.h"

int main(int argc, char** argv)
{
    std::vector<GameObject> gameObjectList;
    
    //turn on antialiasing and create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow oWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML", sf::Style::Fullscreen, settings);


    sf::Vector2f size(150, 50);
    sf::Color color(255, 100, 200, 255);

    GameObject oTopBorder = GameObject("rectangle", sf::Vector2f(oWindow.getSize().x,1.0f),&oWindow, 0.0f);
    oTopBorder.pos = sf::Vector2f(0,0);

	GameObject oLeftBorder = GameObject("rectangle", sf::Vector2f( 1.0f, oWindow.getSize().y), &oWindow, 0.0f);
	oLeftBorder.pos = sf::Vector2f(-1.0f,0);

	GameObject oRightBorder = GameObject("rectangle", sf::Vector2f( 1.0f, oWindow.getSize().y), &oWindow, 0.0f);
	oRightBorder.pos = sf::Vector2f(oWindow.getSize().x, 0);


    Block block1 = Block(size, &oWindow, 1);
    block1.pos = sf::Vector2f(200, 200);
    block1.speed = 10.0f;
    block1.direction = sf::Vector2f(1.0f, 0.0f);

    //Block block2 = Block(size, &oWindow, 1);
    GameObject block2 = GameObject("rectangle", size, &oWindow, 100.0f);
    block2.pos = sf::Vector2f(300, 300);
    block2.color = sf::Color(255, 0, 0, 255);

    gameObjectList.push_back(block1);
    gameObjectList.push_back(block2);


    sf::Vector2f canonSize (50, 150);
    Canon canon = Canon(1, canonSize, &oWindow);
    canon.color = sf::Color(100, 125, 255, 255);

    sf::Vector2f size2(100, 100);
    /*GameObject ball("rectangle", size2, &oWindow,1500.0f);
    ball.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);*/

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
	        if (oEvent.type == sf::Event::KeyPressed && oEvent.key.code == sf::Keyboard::Escape)
   		        oWindow.close();
            if (oEvent.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, oEvent.size.width, oEvent.size.height);
                oWindow.setView(sf::View(visibleArea));
            }
        }

		//Input Manager
        if (fTimer >= 0.5f) {
            if (oTestInputManager.isMousePressed() == 1) {
                canon.Shoot(&gameObjectList);
            }
            fTimer = 0.0f;
        }

        
        //Update every GameObject
        oWindow.clear();
        for (int i = 0; i < gameObjectList.size(); i++)
        {            
            gameObjectList[i].AABBCollision(&oLeftBorder);
            gameObjectList[i].AABBCollision(&oTopBorder);
            gameObjectList[i].AABBCollision(&oRightBorder);

            // COLLISION BETWEEN BRICKS
            for (int j = 0; j < gameObjectList.size(); j++) {
                if (j != i) {
                    sf::Vector2f fDistance(gameObjectList[i].pos.x - gameObjectList[j].pos.x, gameObjectList[i].pos.y - gameObjectList[j].pos.y);
                    float normDistance = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
                    if(normDistance > 0) {
                        gameObjectList[i].AABBCollision(&gameObjectList[j]);
                    }
                }
            }
            if (gameObjectList[i].CheckOutOfBounds()) {
                gameObjectList.erase(gameObjectList.begin() + i);
            }
            else {
                /*GIVE COLOR TO BALLS       
                Ball* ballPtr = new Ball();
                if(GameObject * d_ptr = typeid(Ball){
                }*/ 
                gameObjectList[i].Update(fDeltaTime);

                if (gameObjectList[i].Update(fDeltaTime) == 1) {
                    gameObjectList.erase(gameObjectList.begin() + i);
                }
            }
        }
        

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*&oWindow);
        //ball.Teleport(mouse_pos.x, mouse_pos.y);
        canon.LookAt(mouse_pos);

        oTopBorder.size = sf::Vector2f(oWindow.getSize().x, 1.0f);
        oLeftBorder.size = sf::Vector2f(1.0f, oWindow.getSize().y);
        oRightBorder.size = sf::Vector2f(1.0f, oWindow.getSize().y);
        oRightBorder.Teleport(oWindow.getSize().x, 0);

	    canon.pos.x = oWindow.getSize().x /2;
        canon.pos.y = oWindow.getSize().y;
	    
        /*ball.Update(fDeltaTime);*/
        canon.Update(fDeltaTime);
        oRightBorder.Update(fDeltaTime);
        oTopBorder.Update(fDeltaTime);
        oLeftBorder.Update(fDeltaTime);

        /*system("cls");
        std::cout << "Deltatime:" << fDeltaTime<<"\n";
        std::cout << "Number of gameOjbects: " << gameObjectList.size()<<"\n";*/

        oWindow.display();
        
        fTimer += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}


