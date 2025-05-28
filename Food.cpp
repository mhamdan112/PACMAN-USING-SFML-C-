
#include<SFML/Graphics.hpp>
using namespace sf;
#include "Food.h"
Food::Food(float x, float y, float size) {
    shape.setRadius(size / 6);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x + size / 2 - shape.getRadius(), y + size / 2 - shape.getRadius());
    eaten = false;
}

void Food::draw(sf::RenderWindow& window) {
    if (!eaten)
        window.draw(shape);
}

sf::FloatRect Food::getBounds() const {
    return shape.getGlobalBounds();
}

bool Food::isEaten() const {
    return eaten;
}

void Food::setEaten(bool value) {
    eaten = value;
}
