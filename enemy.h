#pragma once
#include <SFML/Graphics.hpp>
#include "vector"


class Enemy{
public:
    Enemy(sf::Vector2f position, float moveSpeed);
    void update(float deltaTime);
    void handleCollision(const std::vector<sf::Sprite>& tileSprites);
    sf::Sprite getSprite() const;
    bool toBeKilled;
    bool isflyingEnemy;
    int clock;
    int hp;
    bool hasProtection;
    bool goingUp;
    sf::Sprite sprite;

static sf::Texture textureLoader;
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float moveSpeed;
    sf::Texture texture;
};

