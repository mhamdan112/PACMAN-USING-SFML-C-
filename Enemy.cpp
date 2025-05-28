#include "Enemy.h"
#include <cmath> // for abs()

Enemy::Enemy(float startX, float startY) :
    cellSize(45.0f), // Match this to your maze tile size
    speed(0.3f),    // Adjust this value for proper movement speed
    moving(false)
{
    texture.loadFromFile("C:/Users/ha180/OneDrive/Pictures/pac.png");
    IntRect redGhostRect(52, 38, 15, 14);
    sprite.setTexture(texture);
    sprite.setTextureRect(redGhostRect);
    sprite.setScale(2.0f, 2.0f);

    // Center the sprite origin
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    // Initialize grid-aligned position
    gridPosition.x = static_cast<int>(startX / cellSize);
    gridPosition.y = static_cast<int>(startY / cellSize);
    sprite.setPosition(
        gridPosition.x * cellSize + cellSize / 2,
        gridPosition.y * cellSize + cellSize / 2
    );
    targetPosition = sprite.getPosition();
    direction = static_cast<Direction>(rand() % 4);
}

void Enemy::update(const std::vector<Wall>& walls) {
    // If reached center of current cell, choose new direction
    if (!moving && sprite.getPosition() == targetPosition) {
        gridPosition = Vector2i(
            static_cast<int>((targetPosition.x - cellSize / 2) / cellSize),
            static_cast<int>((targetPosition.y - cellSize / 2) / cellSize)
        );

        std::vector<Direction> possibleDirections;

        // Test possible directions
        for (int i = 0; i < 4; ++i) {
            Direction testDir = static_cast<Direction>(i);

            // Skip reverse direction (unless stuck)
            if ((direction == LEFT && testDir == RIGHT) ||
                (direction == RIGHT && testDir == LEFT) ||
                (direction == UP && testDir == DOWN) ||
                (direction == DOWN && testDir == UP)) {
                continue;
            }

            Vector2i testPos = gridPosition;
            switch (testDir) {
            case LEFT:  testPos.x--; break;
            case RIGHT: testPos.x++; break;
            case UP:    testPos.y--; break;
            case DOWN:  testPos.y++; break;
            }

            // Check if next cell is walkable
            FloatRect testBounds(
                testPos.x * cellSize,
                testPos.y * cellSize,
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

            if (canMove) possibleDirections.push_back(testDir);
        }

        // If no directions available, allow reverse
        if (possibleDirections.empty()) {
            switch (direction) {
            case LEFT: possibleDirections.push_back(RIGHT); break;
            case RIGHT: possibleDirections.push_back(LEFT); break;
            case UP: possibleDirections.push_back(DOWN); break;
            case DOWN: possibleDirections.push_back(UP); break;
            }
        }

        if (!possibleDirections.empty()) {
            direction = possibleDirections[rand() % possibleDirections.size()];
            moving = true;

            // Calculate target position (center of next cell)
            targetPosition = sprite.getPosition();
            switch (direction) {
            case LEFT:  targetPosition.x -= cellSize; break;
            case RIGHT: targetPosition.x += cellSize; break;
            case UP:    targetPosition.y -= cellSize; break;
            case DOWN:  targetPosition.y += cellSize; break;
            }
        }
    }

    // Smooth movement toward target
    if (moving) {
        Vector2f currentPos = sprite.getPosition();
        Vector2f movement(0.f, 0.f);

        // Calculate movement with proper speed and clamping
        if (currentPos.x != targetPosition.x) {
            float dir = (targetPosition.x > currentPos.x) ? 1.0f : -1.0f;
            movement.x = dir * speed;

            // Don't overshoot target
            if (std::abs(targetPosition.x - currentPos.x) < std::abs(movement.x)) {
                movement.x = targetPosition.x - currentPos.x;
            }
        }

        if (currentPos.y != targetPosition.y) {
            float dir = (targetPosition.y > currentPos.y) ? 1.0f : -1.0f;
            movement.y = dir * speed;

            if (std::abs(targetPosition.y - currentPos.y) < std::abs(movement.y)) {
                movement.y = targetPosition.y - currentPos.y;
            }
        }

        sprite.move(movement);

        // Check if reached target
        if (sprite.getPosition() == targetPosition) {
            moving = false;
        }
    }
}

FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

void Enemy::draw(RenderWindow& window) {
    window.draw(sprite);
}