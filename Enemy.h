#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include"Character.h"
#include <vector>
using namespace sf;
enum Direction { UP, DOWN, LEFT, RIGHT };
class Enemy:public Character
{
	Direction direction;
	Vector2i gridPosition;
	float cellSize;
	float speed;
	bool moving;
	Vector2f targetPosition;
public:
	Enemy(float startX, float startY);
	void update(const std::vector<Wall>& walls) override;
	void draw(sf::RenderWindow& window)override;
	virtual FloatRect getBounds() const;

};