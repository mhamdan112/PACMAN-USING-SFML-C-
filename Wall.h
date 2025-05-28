// Wall.h
#pragma once
#include <SFML/Graphics.hpp>

class Wall {
private:
    sf::RectangleShape shape;

public:
    Wall(float x, float y, float tileSize);  // Constructor
    void draw(sf::RenderWindow& window);     // Draw function
    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();  // Assuming `shape` is an sf::RectangleShape
    }
};
