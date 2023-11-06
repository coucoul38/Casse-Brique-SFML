
#include <SFML/Graphics.hpp>
#include "GameObject.h"

int main(int argc, char** argv)
{
    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(640, 480), "SFML");

    //Création d'un cercle de radius 100
    sf::CircleShape oCircle(100.f);
    //A la position 0, 0
    oCircle.setPosition(0.f, 0.f);
    //Et de couleur verte
    oCircle.setFillColor(sf::Color::Green);

    sf::Vector2f size(10, 100);
    GameObject oGameObject("circle",size,&oWindow);
    GameObject oRectangleObject("rectangle",size,&oWindow);

    //Création d'un rectangle de taille 50, 50
    sf::RectangleShape oRectangle(sf::Vector2f(50.f, 50.f));
    //A la position 100, 100
    oCircle.setPosition(100.f, 100.f);
    //Et de couleur rouge
    oRectangle.setFillColor(sf::Color::Red);


    oRectangleObject.pos = sf::Vector2f(0, 0);
    oGameObject.pos = sf::Vector2f(0, 0);
    oRectangleObject.velocity = sf::Vector2f(0.1f,0.1f);


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

        //DRAW
        oWindow.clear();

        //oWindow.draw(oCircle);
        oWindow.draw(oRectangle);
        
        sf::Color color(255, 100, 200, 255);

        oGameObject.color = color;

        oRectangleObject.color = color;

        oRectangleObject.Update();
        oGameObject.Update();

        oWindow.display();
    }

    return 0;
}


