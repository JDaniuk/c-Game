#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GameMap.h"
#include "Camera.h"
#include "Level.h"
class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Camera camera;
    Player player;
    GameMap currentLevel;
    int coins;
    sf::Font font;
    sf::Text title;
    sf::Text startL1;
    sf::Text exitOption;
    sf::Text startL2;
    sf::Text startL3;
    sf::Text coinCounter;
    sf::Text shop;
    sf::Text buySpeed;
    sf::Text buyLives;
    sf::Text buyDash;
    sf::Text buyGun;
    sf::Text buyGravity;
    sf::Text lifeCounter;
    sf::Window gameWindow;
    bool shopSelected;

    void update(float deltaTime);
    void render();

};


