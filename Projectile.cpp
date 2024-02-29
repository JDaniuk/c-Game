//
// Created by Kuba on 04/01/2024.
//

#include "Projectile.h"
#include "iostream"


Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, float maxRange, sf::Vector2f origin) : direction(direction), position(position), maxRange(maxRange), origin(origin) {
    if (!texture.loadFromFile("resources/Brick.png")) {}
    sprite.setTexture(texture);
    sprite.setColor(sf::Color::Red);
    sprite.setPosition(position);
    sprite.setScale(0.3f,0.3f);
    toBeKilled = false;
   // std::cout<<"Pocisk stworzony"<<"\n";
}

void Projectile::checkRange() {
    auto currentDist = std::sqrt(((origin.x - position.x ) * (origin.x - position.x ))  +((origin.y - position.y ) * (origin.y - position.y ) )) ;
    if(currentDist > 2* maxRange){
        toBeKilled = true;
    }
}

void Projectile::update() {
    std::cout<<position.x<<position.y<<'\n';
    position.y += direction.y;
    position.x += direction.x;
    sprite.setPosition(position);
    checkRange();

}


void Projectile::handleWalls(const std::vector<sf::Sprite> &tileSprites, const std::vector<Enemy> &MovingPlatforms) {
    sf::FloatRect projectileBounds = sprite.getGlobalBounds();
    bool touchingGround = false;
    for (const auto &tileSprite: tileSprites) {
        sf::FloatRect tileBounds = tileSprite.getGlobalBounds();
        sf::FloatRect area;

        if (projectileBounds.intersects(tileBounds, area)){
            toBeKilled = true;
        }
    }

    for (const auto &platform: MovingPlatforms) {
        sf::FloatRect tileBounds = platform.sprite.getGlobalBounds();
        sf::FloatRect area;

        if (projectileBounds.intersects(tileBounds, area)){
            toBeKilled = true;
        }
    }

}