
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
    GameObject oGameObject("circle",size);
    GameObject oRectangleObject("rectangle",size);

    //Création d'un rectangle de taille 50, 50
    sf::RectangleShape oRectangle(sf::Vector2f(50.f, 50.f));
    //A la position 100, 100
    oCircle.setPosition(100.f, 100.f);
    //Et de couleur rouge
    oRectangle.setFillColor(sf::Color::Red);

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
        
        sf::Color color(200, 200, 200, 255);
        oGameObject.ChangeColor(color);
        oGameObject.Move(500, 100);
        oGameObject.Draw(&oWindow);

        oRectangleObject.ChangeColor(color);
        oRectangleObject.Move(150, 150);
        oRectangleObject.Draw(&oWindow);

        oWindow.display();
    }

    return 0;
}


