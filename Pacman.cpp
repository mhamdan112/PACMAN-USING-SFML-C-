#include "Pacman.h"
#include <cmath>

Pacman::Pacman() :
    cellSize(45.0f),
    speed(0.3f),
    moving(false),
    currentDirection(NONE),
    desiredDirection(NONE),
    frame(0),
    maxFrames(3),
    frameWidth(37.5f),
    frameHeight(37.5f),
    frameDuration(0.1f)
{
    texture.loadFromFile("C:/Users/ha180/source/repos/SFML2.6/SFML2.6/pac.PNG");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, (int)frameWidth, (int)frameHeight));
    sprite.setScale(0.85f, 0.85f);
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);

    gridPosition = { 1, 1 }; // Starting grid cell
    targetPosition = sf::Vector2f(
        gridPosition.x * cellSize + cellSize / 2,
        gridPosition.y * cellSize + cellSize / 2
    );
    sprite.setPosition(targetPosition);
}

void Pacman::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) desiredDirection = UP;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) desiredDirection = DOWN;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) desiredDirection = LEFT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) desiredDirection = RIGHT;
}

void Pacman::update(const std::vector<Wall>& walls) {
    handleInput();

    if (!moving && sprite.getPosition() == targetPosition) {
        gridPosition = {
            static_cast<int>((targetPosition.x - cellSize / 2) / cellSize),
            static_cast<int>((targetPosition.y - cellSize / 2) / cellSize)

        };

        sf::Vector2i nextCell = gridPosition;
        switch (desiredDirection) {
        case LEFT:  nextCell.x--; break;
        case RIGHT: nextCell.x++; break;
        case UP:    nextCell.y--; break;
        case DOWN:  nextCell.y++; break;
        default: break;
        }

        sf::FloatRect testBounds(
            nextCell.x * cellSize,
            nextCell.y * cellSize,
            cellSize,
            cellSize
        );

        bool canMove = true;
        for (const auto& wall : walls) {
            if (testBounds.intersects(wall.getBounds())) {
                canMove = false;
                break;
            }
        }

        if (canMove) {
            currentDirection = desiredDirection;
            targetPosition = sf::Vector2f(
                nextCell.x * cellSize + cellSize / 2,
                nextCell.y * cellSize + cellSize / 2
               
            );
            updateRotation();
            moving = true;
        }
    }

    if (moving) {
        sf::Vector2f currentPos = sprite.getPosition();
        sf::Vector2f movement(0.f, 0.f);

        if (currentPos.x != targetPosition.x) {
            float dir = (targetPosition.x > currentPos.x) ? 1.f : -1.f;
            movement.x = dir * speed;
            if (std::abs(targetPosition.x - currentPos.x) < std::abs(movement.x)) {
                movement.x = targetPosition.x - currentPos.x;
            }
        }

        if (currentPos.y != targetPosition.y) {
            float dir = (targetPosition.y > currentPos.y) ? 1.f : -1.f;
            movement.y = dir * speed;
            if (std::abs(targetPosition.y - currentPos.y) < std::abs(movement.y)) {
                movement.y = targetPosition.y - currentPos.y;
            }
        }

        sprite.move(movement);
        animate();

        if (sprite.getPosition() == targetPosition) {
            moving = false;
        }
    }
}

void Pacman::animate() {
    if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
        frame = (frame + 1) % maxFrames;
        sprite.setTextureRect(sf::IntRect(
            static_cast<int>(frame * frameWidth),
            0,
            static_cast<int>(frameWidth),
            static_cast<int>(frameHeight)
        ));
        animationClock.restart();
    }
}
void Pacman::updateRotation() {
    switch (currentDirection) {
    case LEFT:
        sprite.setRotation(180.f);
        break;
    case RIGHT:
        sprite.setRotation(0.f);
        break;
    case UP:
        sprite.setRotation(270.f);
        break;
    case DOWN:
        sprite.setRotation(90.f);
        break;
    default:
        break;
    }
}


sf::FloatRect Pacman::getBounds() const {
    return sprite.getGlobalBounds();
}

void Pacman::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
