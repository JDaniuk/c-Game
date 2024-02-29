//
// Created by Kuba on 04/01/2024.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "enemy.h"


class Projectile {
public:
    Projectile(sf::Vector2f position, sf::Vector2f direction, float maxRange, sf::Vector2f origin);
    void checkRange();
    void handleWalls(const std::vector<sf::Sprite> &tileSprites,const std::vector<Enemy> &MovingPlatforms);
    void update();
    float maxRange;
    bool toBeKilled;
    sf::Vector2f origin;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f direction;
    sf::Vector2f position;
};


