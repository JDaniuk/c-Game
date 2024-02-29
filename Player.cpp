#include "Player.h"

Player::Player(sf::Vector2f position) : position(position), defaultPosition(position), velocity(0.0f, 0.0f),
                                        canDash(true), gravity(500.0f),
                                        jumpSpeed(300.0f), moveSpeed(200.0f), dashDistance(75.0f),
                                        dashDuration(0.2f), playerSize(16.0f, 16.0f), coins(0),
                                        movespeedMultiplayer(1.f), lifes(3),
                                        isJumping(false) {
    if (!texture.loadFromFile("resources/hero.png")) {
        // handle error
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    level3Unlocked = false;
    level2Unlocked = false;
   // sprite.setColor(sf::Color::Green);
    //sprite.setScale(2.0, 2.0);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    flyMultiplayer = 0;
}

void Player::handleCollision(std::vector<sf::Sprite> &tileSprites, std::vector<Enemy> &enemies,
                             std::vector<Projectile> &Projectiles, const std::vector<Enemy> &MovingPlatforms,
                             std::vector<Projectile> playerProjectiles) {
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    bool touchingGround = false;
    for (auto &tileSprite: tileSprites) {
        sf::FloatRect tileBounds = tileSprite.getGlobalBounds();
        sf::FloatRect area;

        if (playerBounds.intersects(tileBounds, area)) {

            if (tileSprite.getColor() == sf::Color::Yellow) {
                coins += 1;
                //  tileSprite.setColor(sf::Color::Transparent);
                // sf::Texture texture1;
                //tileSprite.setTexture(texture1);
                tileSprite.setScale(0, 0);
                continue;
                //tileSprites.erase(tileSprite);
            } else if (tileSprite.getColor() == sf::Color::Cyan) {
                if (currentLevel == 2) {
                    level3Unlocked = true;
                } else if (currentLevel == 1) {
                    level2Unlocked = true;
                }
            }

            //std::cout << "collision!" << '\n';
            if (tileSprite.getColor() == sf::Color::Blue) {
                position = defaultPosition;
                lifes--;
            }
            if (area.width > area.height) {
                //up
                if (area.contains({area.left, playerBounds.getPosition().y})) {
                    position.y += area.height;
                    velocity.y = 0;
                } else { //down
                    if (touchingGround) continue;
                    position.y -= area.height;
                    if (velocity.y > 0) {
                        velocity.y = 0;
                        isJumping = false;
                        //gravity = 0;
                        touchingGround = true;
                    }
                    gravity = 500;
                }
            } else { // left
                if (area.contains(playerBounds.getPosition().x + sprite.getGlobalBounds().width - 1.f,
                                  area.top + 1.f)) {
                    position.x -= area.width;
                    stop();
                } else
                    position.x += area.width;
                stop();
            }
        }
    }//touchingGround = false;


    for (Enemy &enemy: enemies) {
        enemy.hasProtection = false;

        for (Projectile &projectile: playerProjectiles) {
            int hpBefore = enemy.hp;
            if(!enemy.hasProtection){
            if (projectile.sprite.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())) {
                std::cout<<enemy.hp;
                if (enemy.hp > 0 and !enemy.hasProtection) {
                    enemy.hp = hpBefore-1;
                    projectile.toBeKilled = true;
                    enemy.hasProtection = true;
                  continue;
                } else if(!enemy.hasProtection){ enemy.toBeKilled = true; }
                projectile.toBeKilled = true;
                coins += 1;
            }
        }}


        sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();
        sf::FloatRect area;

        if (playerBounds.intersects(enemyBounds, area)) {
            if ((area.width > area.height) && !(area.contains({area.left, playerBounds.getPosition().y}))) {
                enemy.toBeKilled = true;
                coins += 1;
                isJumping = false;
                break;
            }
            // Player touched an enemy, reset position
            position = defaultPosition;
            lifes--;
            stop();
            gravity = 500.0f;
        }
    }

    bool playerHit = false;
    for (const auto &projectile: Projectiles) {
        sf::FloatRect projectileBounds = projectile.sprite.getGlobalBounds();
        sf::FloatRect area;

        if (playerBounds.intersects(projectileBounds, area)) {
            position = defaultPosition;
            lifes--;
            playerHit = true;
            stop();
            gravity = 500.0f;
        }

    }
    if (playerHit) {
        Projectiles.clear();
    }


    for (const auto &platform: MovingPlatforms) {
        sf::FloatRect tileBounds = platform.sprite.getGlobalBounds();
        sf::FloatRect area;

        if (playerBounds.intersects(tileBounds, area)) {
            //std::cout << "collision!" << '\n';

            if (area.width > area.height) {
                //up
                if (area.contains({area.left, playerBounds.getPosition().y})) {
                    position.y += area.height;
                    velocity.y = 0;
                } else { //down
                    if (touchingGround) continue;
                    position.y -= area.height;
                    if (velocity.y > 0) {
                        velocity.y = 0;
                        isJumping = false;
                        //gravity = 0;
                        touchingGround = true;
                    }
                    gravity = 500;
                }
            } else { // left
                if (area.contains(playerBounds.getPosition().x + sprite.getGlobalBounds().width - 1.f,
                                  area.top + 1.f)) {
                    position.x -= area.width;
                    stop();
                } else
                    position.x += area.width;
                stop();
            }
        }
    }//touchingGround = false;
}


void Player::update(float deltaTime) {
    velocity.y += (gravity  * deltaTime)+ flyMultiplayer; // Apply gravity
    position += velocity * deltaTime;  // Update position

    sprite.setPosition(position);
}

void Player::jump() {
    if (!isJumping && !isCrouching) {
        std::cout << "JUMPING!" << "\n";
        velocity.y = -jumpSpeed;
        isJumping = true;
        canDash = true; // Reset dash ability when jumping
    }
}

void Player::crouch() {
    sprite.setScale(2.0f, 0.5f);
    moveSpeed = 150.f;
    isCrouching = true;
}

void Player::uncrouch() {
    sprite.setScale(1.0f, 1.0f);
    isCrouching = false;
    moveSpeed = 200.f;
}

void Player::moveLeft() {
    velocity.x = -(moveSpeed * movespeedMultiplayer);
    lastMoveDirection = -1;
}

void Player::moveRight() {
    velocity.x = (moveSpeed * movespeedMultiplayer);
    lastMoveDirection = 1;
}


void Player::stop() {
    velocity.x = 0.0f;
}

sf::Sprite Player::getSprite() const {
    return sprite;
}

void Player::Startfly() {
    flyMultiplayer = -10.f;
}

void Player::Stopfly() {
    flyMultiplayer = 0;
}
void Player::dash() {
    if (isJumping && canDash) {
        velocity.x = lastMoveDirection * dashDistance / dashDuration;
        canDash = false;
    }
}


void Player::fire(sf::Vector2f targetPosition, std::vector<Projectile> &playerProjectiles) {
    if (!fired) {
        //idea: https://en.sfml-dev.org/forums/index.php?topic=27150.0
        float destinationY, destinationX = 0;
        //wyliczamy i normalizujemy wektor kierunku pocisku
        sf::Vector2f direction = sf::Vector2f(targetPosition.x - position.x, targetPosition.y - position.y);
        auto length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
        if (length != 0) {
            direction = sf::Vector2f(direction.x / length, direction.y / length);
        } else direction = sf::Vector2f(0, 0);
        direction = sf::Vector2f(direction.x * 5, direction.y * 5);
        //tworzymy pocisk
        Projectile projectile(position, direction, 1000.f, position);
        playerProjectiles.push_back(projectile);
        fired = true;
    }
}

bool Player::restartWhenLost() {
    if(lifes  <= 0){
        currentLevel = 1;
        level2Unlocked = false;
        level3Unlocked = false;
        boughtDash = false;
        canReverseGravitiy = false;
        canShoot = false;
        coins = 0;
        lifes = 3;
        movespeedMultiplayer = 1.f;
        return true;
    }else return false;



}
