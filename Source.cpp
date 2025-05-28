#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Pacman.h"
#include "Wall.h"
#include "Enemy.h"
#include "Menu.h"
#include "Food.h"
#include <vector>

using namespace sf;
using namespace std;

const int ROWS = 15;
const int COLS = 20;
const float TILE_SIZE = 45.0f;

int level[ROWS][COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1},
    {1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1},
    {1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int main() {
    RenderWindow window(VideoMode(900, 675), "Pacman Maze");
    Font font;
    font.loadFromFile("arial.ttf");

    SoundBuffer buffer;
    Sound sound;

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(10.f, 10.f);

    Text finalScoreText;
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(Color::Yellow);
    finalScoreText.setPosition(10.f, 10.f);

    int score = 0;

    while (window.isOpen()) {
        Menu menu(window);

        buffer.loadFromFile("C:/Users/ha180/source/repos/SFML2.6/SFML2.6/pacman_beginning.wav");
        sound.setBuffer(buffer);
        sound.play();

        if (!menu.show())
            break;

        Pacman pacman;
        Enemy enemy(3 * TILE_SIZE, 3 * TILE_SIZE);

        vector<Wall> walls;
        vector<Food> foods;

        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                if (level[row][col] == 1) {
                    walls.emplace_back(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE);
                }
                else if (level[row][col] == 0) {
                    foods.emplace_back(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE);
                }
            }
        }

        score = 0;
        scoreText.setString("Score: 0");
        finalScoreText.setString("");

        bool isGameOver = false;

        while (window.isOpen() && !isGameOver) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }

            pacman.handleInput();
            pacman.update(walls);
            enemy.update(walls);

            bool allEaten = true;

            for (auto& food : foods) {
                if (!food.isEaten() && pacman.getBounds().intersects(food.getBounds())) {
                    food.setEaten(true);
                    buffer.loadFromFile("C:/Users/ha180/source/repos/SFML2.6/SFML2.6/pacman_chomp.wav");
                    sound.setBuffer(buffer);
                    sound.play();
                    score += 10;
                    scoreText.setString("Score: " + to_string(score));
                    finalScoreText.setString("Total Score: " + to_string(score));
                }
                if (!food.isEaten())
                    allEaten = false;
            }

            if (allEaten) {
                buffer.loadFromFile("C:/Users/ha180/source/repos/SFML2.6/SFML2.6/pacmanwin.MP3");
                sound.setBuffer(buffer);
                sound.play();

                Text winText("YOU WON!", font, 70);
                winText.setFillColor(Color::Green);
                winText.setPosition(250, 280);

                window.clear();
                window.draw(winText);
                window.draw(finalScoreText);
                window.display();
                sleep(seconds(4));
                break;
            }

            if (pacman.getBounds().intersects(enemy.getBounds())) {
                isGameOver = true;
                buffer.loadFromFile("C:/Users/ha180/source/repos/SFML2.6/SFML2.6/pacman_death.wav");
                sound.setBuffer(buffer);
                sound.play();

                Text gameOverText("GAME OVER", font, 70);
                gameOverText.setFillColor(Color::Red);
                gameOverText.setPosition(250, 280);

                window.clear();
                window.draw(gameOverText);
                window.draw(finalScoreText);
                window.display();
                sleep(seconds(2));
            }

            window.clear();
            for (auto& wall : walls) wall.draw(window);
            for (auto& food : foods) food.draw(window);
            pacman.draw(window);
            enemy.draw(window);
            window.draw(scoreText);
            window.display();
        }

        // Show final score before restarting
        window.display();
      
    }

    return 0;
}
