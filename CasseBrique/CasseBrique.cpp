
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputManager.h"
#include <iostream> 
#include "Block.h"
#include "Canon.h"

int main(int argc, char** argv)
{


    //turn on antialiasing and create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int fWidth = 800;//sf::VideoMode::getDesktopMode().width
    int fHeight = 600;//sf::VideoMode::getDesktopMode().height


    sf::RenderWindow oWindow(sf::VideoMode(fWidth, fHeight), "SFML");// , sf::Style::Fullscreen, settings);

    std::vector<std::vector<int>> listOfBlock = { {1,1,0,1} ,{0,1,0,1} };

    std::vector<GameObject> gameObjectList;
    
    sf::Vector2f sizeOfBlock((oWindow.getSize().x / listOfBlock[0].size()-10), (((oWindow.getSize().y / 3) *2)/ listOfBlock.size()-10));
    for (int i = 0; i < listOfBlock.size(); i++)
    {
        for (int j = 0; j < listOfBlock[i].size(); j++) {
            if (listOfBlock[i][j]!=0)
            {
                Block blockTest(sizeOfBlock, &oWindow, listOfBlock[i][j]);
                blockTest.pos = sf::Vector2f(j*sizeOfBlock.x+10*j, i*sizeOfBlock.y+10*i);
                blockTest.color= sf::Color(255, 0, 0, 255);
                gameObjectList.push_back(blockTest);
            }
        }
    }
    
    //sf::Vector2f size(150, 50);
    //sf::Color color(255, 100, 200, 255);

    GameObject oTopBorder = GameObject("rectangle", sf::Vector2f(oWindow.getSize().x, 1.0f), &oWindow, 0.0f);
    oTopBorder.pos = sf::Vector2f(0, 0);

    GameObject oLeftBorder = GameObject("rectangle", sf::Vector2f(1.0f, oWindow.getSize().y), &oWindow, 0.0f);
    oLeftBorder.pos = sf::Vector2f(-1.0f, 0);

    GameObject oRightBorder = GameObject("rectangle", sf::Vector2f(1.0f, oWindow.getSize().y), &oWindow, 0.0f);
    oRightBorder.pos = sf::Vector2f(oWindow.getSize().x, 0);

    /*
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

    */
    sf::Vector2f canonSize(50, 150);
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
        //EVENT =======================
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
            if (oEvent.type == sf::Event::KeyPressed && oEvent.key.code == sf::Keyboard::Escape)
                oWindow.close();
            if (oEvent.type == sf::Event::Resized)
            {
                // Update the view to the new size of the window
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
        // ===============================

        

        // UPDATE =========================
        //Update de tous les objets
        //Detection de collision

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*&oWindow);
        canon.LookAt(mouse_pos);
        canon.pos.x = oWindow.getSize().x / 2;
        canon.pos.y = oWindow.getSize().y;

        //update window borders
        oTopBorder.size = sf::Vector2f(oWindow.getSize().x, 1.0f);
        oLeftBorder.size = sf::Vector2f(1.0f, oWindow.getSize().y);
        oRightBorder.size = sf::Vector2f(1.0f, oWindow.getSize().y);
        oRightBorder.Teleport(oWindow.getSize().x, 0);
        oTopBorder.Teleport(0,0);
        oRightBorder.Teleport(oWindow.getSize().x, 0);
        oRightBorder.Move(fDeltaTime);
        oLeftBorder.Move(fDeltaTime);
        oTopBorder.Move(fDeltaTime);

        for (int i = 0; i < gameObjectList.size(); i++)
        {
            gameObjectList[i].Move(fDeltaTime);

            //COLLISIONS
            gameObjectList[i].AABBCollision(&oLeftBorder);
            gameObjectList[i].AABBCollision(&oTopBorder);
            gameObjectList[i].AABBCollision(&oRightBorder);
            oRightBorder.AABBCollision(&gameObjectList[i]);

            for (int j = 0; j < gameObjectList.size(); j++) {
                if (j != i) {
                    sf::Vector2f fDistance(gameObjectList[i].pos.x - gameObjectList[j].pos.x, gameObjectList[i].pos.y - gameObjectList[j].pos.y);
                    float normDistance = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
                    if (normDistance > 0) {
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

                /*if (gameObjectList[i].Update(fDeltaTime) == 1) {
                    gameObjectList.erase(gameObjectList.begin() + i);
                }*/
            }
        }

        // ===============================
        

        //DRAW ===========================
        oWindow.clear();
        oTopBorder.Draw();
        oLeftBorder.Draw();
        oRightBorder.Draw();
        canon.Draw();
        for (int i = 0; i < gameObjectList.size(); i++)
        {
            gameObjectList[i].Draw();
        }
        oWindow.display();
        // ===============================
        /*system("cls");
        std::cout << "Deltatime:" << fDeltaTime<<"\n";
        std::cout << "Number of gameOjbects: " << gameObjectList.size()<<"\n";*/

        fTimer += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}

