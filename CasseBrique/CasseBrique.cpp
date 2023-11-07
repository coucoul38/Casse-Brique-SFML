
#include <SFML/Graphics.hpp>
#include "GameObject.h"

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

    sf::Vector2f size(10, 100);
    GameObject oGameObject("circle",size,&oWindow);
    GameObject oRectangleObject("rectangle",size,&oWindow);
    sf::RectangleShape rectangle(size);

    oRectangleObject.pos = sf::Vector2f(0, 0);
    oGameObject.pos = sf::Vector2f(0, 0);
    oGameObject.velocity = sf::Vector2f(0.1f,0.1f);


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
        
        sf::Color color(255, 100, 200, 255);

        oGameObject.color = color;

        oRectangleObject.color = color;
        oRectangleObject.Rotate(0.1f);
        //oRectangleObject.rectangle.rotate(0.1f);
        
        oRectangleObject.Update();
        oGameObject.Update();

        rectangle.rotate(0.1f);
        //oWindow.draw(rectangle);

        oWindow.display();
    }

    return 0;
}


