
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputManager.h"
#include <iostream> 
#include "Block.h"
#include "Canon.h"
#include <fstream>
#include "Ball.h"
#include <typeinfo>
#include <string>
#include <iomanip>
#include <sstream>


std::vector<std::vector<int>> readFile(std::string fileName) {
    std::ifstream myFile;
    myFile.open(fileName);
    std::string line;
    std::vector<std::vector<int>> listOfBlock;
    while (std::getline(myFile, line))
    {
        std::vector<int> l;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] != ' ') {
                l.push_back(line[i] - '0');
            }
        }
        listOfBlock.push_back(l);
    }
    myFile.close();
    return listOfBlock;
}

std::string readBestCombo(std::string fileName) {
    std::ifstream myFile;
    myFile.open(fileName);
    std::string line;
    std::string returnValue;
    while (std::getline(myFile, line))
    {
        returnValue = line;
    }
    myFile.close();
    return returnValue;
}

void writeFile(std::string fileName, int combo) {
    std::fstream myFile;
    myFile.open(fileName, std::ios::out | std::ios::app);
    myFile.close();
	myFile.open(fileName, std::ios::in | std::ios::out | std::ios::app);
	std::string line;
    int comboInFile = 0;
    while (std::getline(myFile, line))
    {
        if (!line.empty())
        {
            comboInFile = std::stoi(line);
        }
    }
    if (comboInFile < combo) {
        myFile.close();
        myFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
        myFile << std::to_string(combo);
    }
    myFile.close();
}

int main(int argc, char** argv)
{
    //Text
    sf::Font font;
    font.loadFromFile("Assets/Fonts/62DRAGZ.otf");
    sf::Text comboText;
    comboText.setFont(font);
    comboText.setString("{This is a test 123}");
    comboText.setCharacterSize(25);
    comboText.setFillColor(sf::Color(255,255,255,255));

    sf::Text ultimateText;
    ultimateText.setFont(font);
    ultimateText.setString("{Ultimate charge:}");
    ultimateText.setCharacterSize(25);
    ultimateText.setFillColor(sf::Color(255, 255, 255, 255));

    sf::Text maxCombo;
    maxCombo.setFont(font);
    maxCombo.setCharacterSize(25);
    maxCombo.setFillColor(sf::Color(255, 255, 255, 255));

    //turn on antialiasing and create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int fWidth = sf::VideoMode::getDesktopMode().width;
    int fHeight = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow oWindow(sf::VideoMode(fWidth, fHeight), "SFML", sf::Style::Fullscreen, settings);

    std::vector<std::vector<int>> listOfBlock=readFile("level2.txt");

    std::vector<GameObject*> gameObjectList;
    
    if (listOfBlock.size() == 0) {
        std::cout << "Error: No Blocks in map\n";
        return -1;
    }

    sf::Vector2f sizeOfBlock((oWindow.getSize().x / listOfBlock[0].size()-3), (((oWindow.getSize().y / 3) *2)/ listOfBlock.size()-3));
    for (int i = 0; i < listOfBlock.size(); i++)
    {
        for (int j = 0; j < listOfBlock[i].size(); j++) {
            if (listOfBlock[i][j]!=0)
            {
                Block* blockTest = new Block(-1, -1, sizeOfBlock.x, sizeOfBlock.y, listOfBlock[i][j], &oWindow);
                
                float x = j * sizeOfBlock.x + 3 * j + 1;
                float y = i * sizeOfBlock.y + 3 * i + 3;

                blockTest->setPosition(x, y, 0.f, 0.f);

                gameObjectList.push_back(blockTest);
            }
        }
    }

    GameObject oTopBorder = GameObject(0.f, -1.0f, oWindow.getSize().x, 1.0f, 0.f, &oWindow);
    GameObject oLeftBorder = GameObject(-1.0f, 0, 1.0f, oWindow.getSize().y,0.f, &oWindow);
    GameObject oRightBorder = GameObject(oWindow.getSize().x, 0.f, 1.0f, oWindow.getSize().y, 0.f, &oWindow);

    Canon canon = Canon(-1, -1, 50, 150, &oWindow, &gameObjectList);
    canon.setPosition(oWindow.getSize().x / 2.f, oWindow.getSize().y, 0.5f, 1.f);
    canon.setColor(sf::Color(100, 125, 255, 255));
 
    InputManager oTestInputManager(&oWindow);

    sf::Clock oClock;
    float fDeltaTime;
    fDeltaTime = oClock.restart().asSeconds();
    float fTimer = 2.0f;
    float fShootTimer = 0.0f;
    bool canFire = true;

    float combo = 0;
    float ultimateTime = 3.0f;


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

        
        //check if ball already fired
        canFire = canon.HasBalls() == false;
        if (canFire){
            if(combo>=3)
                //charge ultimate with combo
                ultimateTime += combo/10;
            combo = 0;
        }
        //Input Manager
        if (oTestInputManager.isMousePressed() == 1 && canFire) {
            canon.Shoot();
        }
        else if (oTestInputManager.isMousePressed() == 3 && ultimateTime > 0.0f) {
            if (fShootTimer >= 0.2f) {
                canon.Shoot(true,true);
                fShootTimer = 0.0f;
            }
            ultimateTime -= fDeltaTime;
        }
        
        if (fTimer >= 2.0f) {
            if (oTestInputManager.isMousePressed() == 2) {
                canon.ShootSecondary();
                fTimer = 0.0f;
            }
        }
        // ===============================


        // UPDATE =========================
        //Update de tous les objets
        //Detection de collision

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*&oWindow);
        canon.LookAt(mouse_pos);

        std::vector<Ball*>& balls = canon.GetBalls();

        if (balls.size()>0) 
        {
            for (int i = 0; i < balls.size(); i++)
            {
                balls[i]->Move(fDeltaTime);

                balls[i]->AABBCollision(&oLeftBorder);
                balls[i]->AABBCollision(&oTopBorder);
                balls[i]->AABBCollision(&oRightBorder);

                //COLLISION WITH OTHER BALLS
                for (int k = 0; k < balls.size(); k++)
                {
                    if(i!=k)
                        balls[i]->AABBCollision(balls[k]);
                }

                //COLLISION WITH BLOCK
                for (int j = 0; j < gameObjectList.size(); j++)
                {
                    
                    int collisionReturn = balls[i]->AABBCollision(gameObjectList[j]);
                    switch (collisionReturn)
                    {
                    case 2:
                        combo++;
                        break;
                    case 3:
                        combo++;
                        break;
                    default:
                        break;
                    }
                    if (gameObjectList[j]->AABBCollision(balls[i]) == 1) {
                        gameObjectList.erase(gameObjectList.begin() + j);
                    }
                }
                /*if (balls[i]->CheckOutOfBounds()) {
                    balls.erase(balls.begin() + i);
                }*/
            }
        }

        for (int i = 0; i < gameObjectList.size(); i++)
        {
            gameObjectList[i]->Move(fDeltaTime);
        }

        for (int i = 0; i < balls.size();)
        {
            if (balls[i]->CheckOutOfBounds()) {
                balls.erase(balls.begin() + i);
            }
            else {
                i++;
            }
        }
        // ===============================
        
		
        //DRAW ===========================
        std::ostringstream comboOut;
        comboOut << std::setprecision(0) << std::fixed << combo;
        std::ostringstream ultiOut;
        ultiOut << std::setprecision(1) << std::fixed << ultimateTime;
        comboText.setString("{Combo: " + comboOut.str() + "]");
        comboText.setPosition(10, oWindow.getSize().y-100);
        ultimateText.setString("{Ultimate " + ultiOut.str() + "]");
        ultimateText.setPosition(oWindow.getSize().x-360, oWindow.getSize().y - 50);
        maxCombo.setString("{Max Combo " + readBestCombo("Combo.txt") + "]");
        maxCombo.setPosition(10, oWindow.getSize().y - 50);
        writeFile("combo.txt", combo);

        oWindow.clear(sf::Color(30,30,45,255));
        oTopBorder.Draw();
        oLeftBorder.Draw();
        oRightBorder.Draw();
        for (int i = 0; i < gameObjectList.size(); i++)
        {
            gameObjectList[i]->Draw();
        }
        for (int i = 0; i < balls.size(); i++)
        {
            balls[i]->Draw();
        }
        /*if (balls.size() > 0){}*/

        canon.Draw();
	    oWindow.draw(comboText);
	    oWindow.draw(maxCombo);
        oWindow.draw(ultimateText);
        oWindow.display();
        // ===============================
        /*system("cls");
        std::cout << "Deltatime:" << fDeltaTime<<"\n";
        std::cout << "Number of gameOjbects: " << gameObjectList.size()<<"\n";*/

        fTimer += fDeltaTime;
        fShootTimer += fDeltaTime;
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}

