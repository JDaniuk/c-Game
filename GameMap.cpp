#include "GameMap.h"
#include "Player.h"
#include "enemy.h"
#include "Turret.h"

GameMap::GameMap(const int mapLayout[100][100]) : mapHeight(100), mapWidth(100), tileSize(16) {
    if (!brickTexture.loadFromFile("resources/Brick.png")) {
        // handle error
      //  std::cerr << "Failed to load texture: Brick.png" << std::endl;
    }

    if (!turretTexture.loadFromFile("resources/turret.png")) {
       // std::cerr << "Failed to load texture: Turret.png" << std::endl;
    }

    if (!coin.loadFromFile("resources/coin.png")) {
       // std::cerr << "Failed to load texture: Turret.png" << std::endl;
    }

    //1 for a brick, 2 for lava, 3 is the player, 4 is basic enemny


    // Populate the tileSprites vector based on the mapLayout
    generate(mapLayout);

}


void GameMap::draw(sf::RenderWindow &window) {
    for (const auto &tileSprite: tileSprites) {
        window.draw(tileSprite);
    }
    for (const auto &enemy: enemies) {
        window.draw(enemy.getSprite());
    }
    for (const auto &turret: Turrets) {
        window.draw(turret.sprite);

    }
    for (const auto &projectile: Projectiles) {
        window.draw(projectile.sprite);
    }
    for (const auto &projectile: playerProjectiles) {
        window.draw(projectile.sprite);
    }

    for(const auto  &platform : MovingTiles){
        window.draw(platform.getSprite());
    }


}

const std::vector<sf::Sprite> &GameMap::getTileSprites() const {
    return tileSprites;
}

void GameMap::update(float deltaTime, sf::Vector2f player) {
    // Update enemies
    for (auto &enemy: enemies) {
        enemy.handleCollision(tileSprites);
        enemy.update(deltaTime);
    }

    for (auto &turret: Turrets) {
        turret.update(deltaTime, player, Projectiles);
    }
    std::cout << Projectiles.size() << "\n";
    for (auto &projectile: Projectiles) {
        projectile.handleWalls(tileSprites,MovingTiles);
        projectile.update();
    }

    for (auto &projectile: playerProjectiles) {
        projectile.handleWalls(tileSprites,MovingTiles);
        projectile.update();
    }

    Projectiles.erase(
            std::remove_if(Projectiles.begin(), Projectiles.end(),
                           [](const Projectile &projectile) {
                               // Replace this condition with your logic for deciding which projectiles to remove
                               return projectile.toBeKilled;
                           }),
            Projectiles.end()
    );

    playerProjectiles.erase(
            std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
                           [](const Projectile &projectile) {
                               // Replace this condition with your logic for deciding which projectiles to remove
                               return projectile.toBeKilled;
                           }),
            playerProjectiles.end()
    );
    enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                           [](const Enemy &enemy) {
                               // Replace this condition with your logic for deciding which projectiles to remove
                               return enemy.toBeKilled;
                           }),
            enemies.end()
    );

    for(auto &platform : MovingTiles){
        platform.update(1/60.f);
        platform.handleCollision(tileSprites);
    }

}

const std::vector<sf::Sprite> &GameMap::getEnemySprites() const {
    static std::vector<sf::Sprite> enemySprites;
    enemySprites.clear();
    for (const auto &enemy: enemies) {
        enemySprites.push_back(enemy.getSprite());
    }
    return enemySprites;
}

GameMap::GameMap(GameMap const &other) {
    this->enemies = other.enemies;
    this->tileSprites = other.tileSprites;
    this->Projectiles = other.Projectiles;
    this->Turrets = other.Turrets;
    this->playerStart = other.playerStart;
    this->MovingTiles = other.MovingTiles;

}


void GameMap::generate(const int (*mapLayout)[100]) {
    enemies.clear();
    tileSprites.clear();
    Turrets.clear();
    Projectiles.clear();
    MovingTiles.clear();
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("resources/enemy.PNG");
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (mapLayout[i][j] == 1) {
                sf::Sprite brickSprite(brickTexture);
                brickSprite.setPosition(j * tileSize, i * tileSize);
                tileSprites.push_back(brickSprite);
            } else if (mapLayout[i][j] == 2) {
                sf::Sprite brickSprite(brickTexture);
                brickSprite.setPosition(j * tileSize, i * tileSize);
                brickSprite.setColor(sf::Color::Blue);
                tileSprites.push_back(brickSprite);
            } else if (mapLayout[i][j] == 3) {
                playerStart.x = j * tileSize;
                playerStart.y = i * tileSize;
            } else if(mapLayout[i][j] == 10){
                sf::Sprite brickSprite(coin);
                brickSprite.setColor(sf::Color::Yellow);
                brickSprite.setOrigin(brickSprite.getGlobalBounds().width / 2, brickSprite.getGlobalBounds().height / 2);
               // brickSprite.setScale(0.5, 0.5);
                brickSprite.setPosition(j * tileSize, i * tileSize);
                tileSprites.push_back(brickSprite);
            }
            else if(mapLayout[i][j] == 11){
                sf::Sprite brickSprite(brickTexture);
                brickSprite.setColor(sf::Color::Cyan);
                 brickSprite.setScale(0.2, 1);
                brickSprite.setPosition(j * tileSize, i * tileSize);
                tileSprites.push_back(brickSprite);
            }
        }
    }

    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (mapLayout[i][j] == 4) {
                Enemy enemy(sf::Vector2f(j * tileSize, i * tileSize), 50.f);
               // enemy.sprite.setTexture(enemyTexture);
               // enemy.isflyingEnemy = true;
                enemies.push_back(enemy);
            } else if (mapLayout[i][j] == 5) {
                Turret turret(sf::Vector2f(j * tileSize, i * tileSize), 1750.f);
                Turrets.push_back(turret);
            }else if (mapLayout[i][j] == 6) {//moving platform;
                Enemy platform(sf::Vector2f (j*tileSize,i*tileSize), 40.f);
                platform.sprite.setScale(2.0f,0.5f);
                platform.sprite.setColor(sf::Color::Red);
                platform.sprite.setTexture(brickTexture);
                MovingTiles.push_back(platform);
                //enemies.push_back(platform);
              //  tileSprites.push_back(platform.getSprite());
            } else  if (mapLayout[i][j] == 7) {
                    Enemy enemy(sf::Vector2f(j * tileSize, i * tileSize), 50.f);
                    enemy.sprite.setScale(0.7, 0.3);
                    enemy.isflyingEnemy = true;
                    enemies.push_back(enemy);
        }

    }
}}