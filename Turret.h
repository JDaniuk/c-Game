#pragma once
#include <SFML/Graphics.hpp>
#include "vector"
#include "Projectile.h"
#include <cmath>
class Turret{
public:
    float range;
    float projectileSpeed;
    sf::Vector2f position;
    sf::Texture turretTexture;
    sf::Sprite sprite;
    Turret(sf::Vector2f position, float range);
    void update(float deltaTime, sf::Vector2f player, std::vector<Projectile> &projectileList);
    void handleCollision(const std::vector<sf::Sprite>& tileSprites);
    auto calcRange(sf::Vector2f targetPosition);
    void shoot(sf::Vector2f targetPosition,std::vector<Projectile> &projectileList);
    int clock = 0;

};


