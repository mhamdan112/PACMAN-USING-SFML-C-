class Food {
private:
    sf::CircleShape shape;
    bool eaten;

public:
    Food(float x, float y, float size);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isEaten() const;
    void setEaten(bool value);
};