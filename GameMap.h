#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "enemy.h"
#include "Turret.h"
class GameMap {
public:
    sf::Vector2<float> playerStart;
    std::vector<sf::Sprite> tileSprites;
    const std::vector<sf::Sprite>& getEnemySprites() const;
    GameMap( int const mapLayout[100][100]);
    GameMap(GameMap const& other);

    void draw(sf::RenderWindow& window);
    void generate(int const mapLayout[100][100]);
    const std::vector<sf::Sprite>& getTileSprites() const;
    void update(float deltaTime, sf::Vector2f player);
    std::vector<Enemy> enemies;
    std::vector<Turret> Turrets;
    std::vector<Projectile> Projectiles;
    std::vector<Projectile> playerProjectiles;
    std::vector<Enemy> MovingTiles;

private:

     int mapWidth;
     int mapHeight;
     int tileSize;
     sf::Texture enemyTexture;
     sf::Texture turretTexture;
    sf::Texture coin;
    sf::Texture brickTexture;

};
