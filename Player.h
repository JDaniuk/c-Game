#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Turret.h"
#include "enemy.h"

#include "iostream"




class Player {
public:
    bool level2Unlocked;
    bool  level3Unlocked;
    int currentLevel;
    bool canShoot;
    bool boughtDash;
    bool canReverseGravitiy;
    sf::Vector2f position;
    sf::Vector2f defaultPosition;
    Player(sf::Vector2f position);
    int coins;
    float movespeedMultiplayer;
    bool fired;
    float flyMultiplayer;

    void handleCollision( std::vector<sf::Sprite> &tileSprites,  std::vector<Enemy> &enemies, std::vector<Projectile> &Projectiles, const std::vector<Enemy> &MovingPlatforms,
                         std::vector<Projectile> playerProjectiles);

    void update(float deltaTime);

    void fire(sf::Vector2f targetPosition, std::vector<Projectile> &playerProjectiles);


    void crouch();

    void Startfly();

    void Stopfly();

    void jump();

    void moveLeft();

    void moveRight();

    void dash();

    void stop();

    bool restartWhenLost();

    sf::Sprite getSprite() const;
    bool isCrouching;
    int lifes;
    void uncrouch();
private:

    sf::Vector2f velocity;
    sf::Texture texture;
    sf::Sprite  sprite;

    int lastMoveDirection;
    float gravity;
    const float jumpSpeed;
    float moveSpeed;
    const float dashDistance;
    const float dashDuration;
    const sf::Vector2f playerSize;
    bool isJumping;

    bool canDash;
    bool canReverseGrav;
};

