#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Character
{
protected:
    Sprite sprite;
    Texture texture;
    float speed;
public:
    virtual void update(const std::vector<class Wall>& walls) = 0;
    virtual void draw(sf::RenderWindow& window);
    virtual sf::FloatRect getBounds() const;
    virtual ~Character() = default;
};

