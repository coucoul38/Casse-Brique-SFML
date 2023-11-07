
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputManager.h"

int main(int argc, char** argv)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(640, 480), "SFML", sf::Style::Default, settings);

    //Création d'un cercle de radius 100
    sf::CircleShape oCircle(100.f);
    //A la position 0, 0
    oCircle.setPosition(0.f, 0.f);
    //Et de couleur verte
    oCircle.setFillColor(sf::Color::Green);

    sf::Vector2f size(100, 10);
    GameObject oGameObject("circle",size,&oWindow);
    GameObject oRectangleObject("rectangle",size,&oWindow);
    sf::RectangleShape rectangle(size);

    oRectangleObject.pos = sf::Vector2f(200, 300);
    oGameObject.pos = sf::Vector2f(0, 0);
    oGameObject.velocity = sf::Vector2f(0.0f,0.01f);

    sf::Color color(255, 100, 200, 255);

    oGameObject.color = color;

    oRectangleObject.color = color;

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

        //UPDATE

		 //Input Manager
		sf::Vector2f newSize(100, 100);
		GameObject newRect("rectangle", newSize, &oWindow);
		InputManager testInputManager(&oWindow);
		newRect.pos = sf::Vector2f(0.3f, 0.3f);
		//testInputManager.isMousePressed((*newRect.Draw)());

        //DRAW
        oWindow.clear();
        
        //oRectangleObject.Rotate(0.01f);
        
        oRectangleObject.Update();
        oGameObject.Update();

        oRectangleObject.AABBCollision(oGameObject.bounding_box);
        oGameObject.AABBCollision(oRectangleObject.bounding_box);


        oWindow.display();
    }

    return 0;
}


