#// Wall.cpp
#include "Wall.h"
#include <SFML/Graphics.hpp>  // (This is optional here since Wall.h already includes it)

Wall::Wall(float x, float y, float tileSize) {
    shape.setSize(sf::Vector2f(tileSize, tileSize));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Blue);
}

void Wall::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
