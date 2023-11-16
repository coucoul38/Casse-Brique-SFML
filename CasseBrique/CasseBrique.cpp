
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputManager.h"
#include <iostream> 
#include "Block.h"
#include "Canon.h"
#include <fstream>
#include "Ball.h"
#include <typeinfo>


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

void writeFile(std::string fileName, int combo) {
    std::fstream myFile;
    myFile.open(fileName, std::ios::out | std::ios::app);
    myFile.close();
	myFile.open(fileName, std::ios::in | std::ios::out | std::ios::app);
	std::string line;
    while (std::getline(myFile, line)){
		if (line.empty()) {
			myFile << std::to_string(combo);
		}
		else if (std::stoi(line) < combo) {
            std::cout << "new best combo";
            myFile.close();
            myFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
			myFile << std::to_string(combo);
		}
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

    //turn on antialiasing and create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int fWidth = sf::VideoMode::getDesktopMode().width;
    int fHeight = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow oWindow(sf::VideoMode(fWidth, fHeight), "SFML" , sf::Style::Fullscreen, settings);

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
                Block* blockTest = new Block(sizeOfBlock, &oWindow, listOfBlock[i][j]);
                blockTest->pos = sf::Vector2f(j*sizeOfBlock.x+3*j+1, i*sizeOfBlock.y+3*i+3);
                gameObjectList.push_back(blockTest);
            }
        }
    }

    GameObject oTopBorder = GameObject("rectangle", sf::Vector2f(oWindow.getSize().x, 1.0f), &oWindow, 0.0f);
    oTopBorder.pos = sf::Vector2f(0, 0);
    GameObject oLeftBorder = GameObject("rectangle", sf::Vector2f(1.0f, oWindow.getSize().y), &oWindow, 0.0f);
    oLeftBorder.pos = sf::Vector2f(-1.0f, 0);
    GameObject oRightBorder = GameObject("rectangle", sf::Vector2f(1.0f, oWindow.getSize().y), &oWindow, 0.0f);
    oRightBorder.pos = sf::Vector2f(oWindow.getSize().x, 0);

    sf::Vector2f canonSize(50, 150);
    Canon canon = Canon(1, canonSize, &oWindow);
    canon.color = sf::Color(100, 125, 255, 255);
    sf::Vector2f size2(100, 100);
 
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
        Ball* fakeBall = new Ball(sf::Vector2f(0,0),&oWindow,0);
        canFire = true;
        //find balls in gameObject list
        for (int i = 0; i < gameObjectList.size(); i++)
        {
            if (gameObjectList[i]->shape == "circle") {
                canFire = false;
                //its a ball !
            }
        }
        if (canFire){
            if(combo>=3)
                //charge ultimate with combo
                ultimateTime += combo/10;
            combo = 0;
        }
        //Input Manager
        if (oTestInputManager.isMousePressed() == 1 && canFire) {
            canon.Shoot(&gameObjectList, false);
        }
        else if (oTestInputManager.isMousePressed() == 3 && ultimateTime > 0.0f) {
            if (fShootTimer >= 0.2f) {
                canon.Shoot(&gameObjectList, true);
                fShootTimer = 0.0f;
            }
            ultimateTime -= fDeltaTime;
        }
        
        if (fTimer >= 2.0f) {
            if (oTestInputManager.isMousePressed() == 2) {
                canon.ShootSecondary(&gameObjectList);
                fTimer = 0.0f;
            }
        }
        // ===============================


        // UPDATE =========================
        //Update de tous les objets
        //Detection de collision

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*&oWindow);
        canon.LookAt(mouse_pos);
        canon.pos.x = oWindow.getSize().x / 2;
        canon.pos.y = oWindow.getSize().y;
        canon.rectangle.setOrigin(canon.size.x / 2, 0);

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
            gameObjectList[i]->Move(fDeltaTime);

            //COLLISIONS
            gameObjectList[i]->AABBCollision(&oLeftBorder);
            gameObjectList[i]->AABBCollision(&oTopBorder);
            gameObjectList[i]->AABBCollision(&oRightBorder);
            oRightBorder.AABBCollision(gameObjectList[i]);

            for (int j = 0; j < gameObjectList.size(); j++) {
                if (j != i) {
                    sf::Vector2f fDistance(gameObjectList[i]->pos.x - gameObjectList[j]->pos.x, gameObjectList[i]->pos.y - gameObjectList[j]->pos.y);
                    float normDistance = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
                    if (normDistance > 0) {
                        //only test collision for balls
                        if ((gameObjectList[i]->shape == "circle" && gameObjectList[j]->shape != "circle") || (gameObjectList[i]->shape != "circle" && gameObjectList[j]->shape == "circle")) {
                            int collisionReturn = gameObjectList[i]->AABBCollision(gameObjectList[j]);
                            switch (collisionReturn)
                            {
                            case 1:
                                gameObjectList.erase(gameObjectList.begin() + i);
                                break;
                            case 2:
                                combo++;
                                break;
                            case 3:
                                combo++;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
            }
    
        }

        for (size_t i = 0; i < gameObjectList.size();)
        {
            if (gameObjectList[i]->CheckOutOfBounds()) {
                //std::cout << "A";
                gameObjectList.erase(gameObjectList.begin() + i);
            }
            else {
                i++;
            }
        }

        // ===============================
        
		comboText.setString("{Combo: " + std::to_string(combo)+"]");
        ultimateText.setString("{Ultimate " + std::to_string(ultimateTime)+"]");
        ultimateText.setPosition(0, oWindow.getSize().y - 50);
        writeFile("combo.txt",combo);
        //DRAW ===========================
        oWindow.clear(sf::Color(30,30,45,255));
        oTopBorder.Draw();
        oLeftBorder.Draw();
        oRightBorder.Draw();
        for (int i = 0; i < gameObjectList.size(); i++)
        {
            gameObjectList[i]->Draw();
        }
        canon.Draw();
		oWindow.draw(comboText);
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

