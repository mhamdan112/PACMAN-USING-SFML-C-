#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Character.h"
#include <vector>

class Pacman :public Character{
private:
    float cellSize;

    sf::Vector2i gridPosition;
    sf::Vector2f targetPosition;
    bool moving;

    int frame;
    int maxFrames;
    float speed;
    float frameWidth;
    float frameHeight;
    float frameDuration;
    sf::Clock animationClock;

    enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
    Direction currentDirection;
    Direction desiredDirection;

public:
    Pacman();
    void handleInput();
    void update(const std::vector<Wall>& walls) override;
    void animate();
    void updateRotation();
    void draw(sf::RenderWindow& window)override;
    sf::FloatRect getBounds() const;
};
