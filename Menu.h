#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace sf;
using namespace std;
class Menu
{
private:
	RenderWindow& window;
	Font font;
	Text Enter;
	Text Quit;
	Text gameover;
	Texture logoTexture;
	Sprite logoSprite;
public:
	Menu(RenderWindow& window);
	bool show();
};

