#include "enemy.h"


Enemy::Enemy(sf::Vector2f position, float moveSpeed) : position(position), velocity(moveSpeed, moveSpeed), moveSpeed(moveSpeed), texture() {
    if (!texture.loadFromFile("resources/Enemy.png")) {
        // handle error
     //   std::cerr << "Failed to load texture: EnemyTexture.png" << std::endl;
    }
    toBeKilled = false;
    goingUp = false;
    clock = 0;
    sprite.setTexture(texture);
    sprite.setPosition(position);
    hp = 0;
    sprite.setColor(sf::Color::Magenta);
    //sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Enemy::update(float deltaTime) {
    if(!isflyingEnemy){
    position.x += velocity.x * deltaTime;
    sprite.setPosition(position);}
    else if(isflyingEnemy){
        if(goingUp){
            if(clock<30){
                clock++;
                position.x += velocity.x * deltaTime;
                position.y -= velocity.y * deltaTime;
                sprite.setPosition(position);
            }if(clock == 30){
                position.x += velocity.x * deltaTime;
                position.y -= velocity.y * deltaTime;
                clock = 0;
                goingUp = false;
                sprite.setPosition(position);
            }
        }else if (!goingUp){
            if(clock<30){
                clock++;
                position.x += velocity.x * deltaTime;
                position.y += velocity.y * deltaTime;
                sprite.setPosition(position);
            }if(clock == 30){
                position.x += velocity.x * deltaTime;
                position.y += velocity.y * deltaTime;
                sprite.setPosition(position);
                clock = 0;
                goingUp = true;
            }
        }
    }

}



void Enemy::handleCollision(const std::vector<sf::Sprite>& tileSprites) {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();
    for (const auto& tileSprite : tileSprites) {
        sf::FloatRect tileBounds = tileSprite.getGlobalBounds();
        sf::FloatRect intersection;
        if (enemyBounds.intersects(tileBounds, intersection)) {
            // Collision handling, change direction upon hitting a wallif (tileSprite.getColor() == sf::Color::Blue) {
                if (intersection.width < intersection.height) {
                    // Horizontal collision
                    velocity.x = -velocity.x; // Change direction

            } else {goingUp = !goingUp;
                clock = 0;}
        }
    }
    }


sf::Sprite Enemy::getSprite() const {
    return sprite;
}


//turret

