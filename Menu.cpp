#include "Menu.h"
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
using namespace std;
Menu::Menu(RenderWindow& win) :window (win)  {

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    if (!logoTexture.loadFromFile("Menu.JPG")) {
        std::cerr << "Failed to load logo image\n";
    }
    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(0.5f, 0.5f);
    logoSprite.setPosition(315, 50);
     
    

    Enter.setFont(font);
    Enter.setString("Enter - Start Game");
    Enter.setCharacterSize(40);
    Enter.setFillColor(sf::Color::Yellow);
    Enter.setPosition(300, 250);

    Quit.setFont(font);
    Quit.setString("Q  -  Quit Game");
    Quit.setCharacterSize(40);
    Quit.setFillColor(sf::Color::Yellow);
    Quit.setPosition(315, 320);
}
bool Menu:: show() {
    while (window.isOpen()) {
        Event event;
        
       while( window.pollEvent(event)) {
           if (event.type == Event::Closed)
               window.close();
           if (event.type == Event::KeyPressed) {
               if (event.key.code == Keyboard::Enter)
                   return true;

               if (event.key.code == Keyboard::Q)
                       return false;
          }
        }
           window.clear();

           window.draw(Enter);
           window.draw(Quit);
           window.draw(logoSprite);
           window.display();
           


      }
       return false;
}