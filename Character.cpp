#include "Character.h"
void Character::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Character::getBounds() const {
    return sprite.getGlobalBounds();
}