#include "Game.h"


Game::Game() : window(sf::VideoMode(800, 600), "title"), camera(300.f), currentLevel(Level::level1),
               player(currentLevel.playerStart) {
    window.setFramerateLimit(60);
    player.position = currentLevel.playerStart;
    player.defaultPosition = currentLevel.playerStart;
    camera.position = player.position;
    player.currentLevel = 0;
    player.canReverseGravitiy = false;
    player.canShoot = false;
    player.boughtDash = false;
    if (!font.loadFromFile("resources/arial.ttf")) {

    }
    title.setFont(font);
    title.setString("TYTUL!");
    title.setFillColor(sf::Color::Red);
    title.setCharacterSize(25);
    title.setPosition(0.f, 0.f);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().top / 2);

    startL1.setFont(font);
    startL1.setString("1: poziom pierwszy");
    startL1.setCharacterSize(15);
    startL1.setPosition(0.f, 100.f);
    startL1.setOrigin(startL1.getGlobalBounds().width / 2, startL1.getGlobalBounds().top / 2);

    startL2.setFont(font);
    startL2.setString("2: poziom drugi");
    startL2.setCharacterSize(15);
    startL2.setPosition(0.f, 200.f);
    startL2.setOrigin(startL2.getGlobalBounds().width / 2, startL2.getGlobalBounds().top / 2);

    startL3.setFont(font);
    startL3.setString("3: poziom trzeci");
    startL3.setCharacterSize(15);
    startL3.setPosition(0.f, 300.f);
    startL3.setOrigin(startL3.getGlobalBounds().width / 2, startL3.getGlobalBounds().top / 2);


    exitOption.setFont(font);
    exitOption.setString("6. aby wyjsc");
    exitOption.setCharacterSize(15);
    exitOption.setPosition(0.f, 500.f);
    exitOption.setOrigin(exitOption.getGlobalBounds().width / 2, exitOption.getGlobalBounds().top / 2);


    coinCounter.setFont(font);
    coinCounter.setString("Coins: " + std::to_string(player.coins));
    coinCounter.setCharacterSize(15);
    coinCounter.setPosition(-200, 0.f);


    lifeCounter.setFont(font);
    lifeCounter.setString("Lives: " + std::to_string(player.lifes));
    lifeCounter.setCharacterSize(15);
    lifeCounter.setPosition(150, 0.f);
    //lifeCounter.setOrigin(lifeCounter.getGlobalBounds().left+lifeCounter.getGlobalBounds().getSize().x, lifeCounter.getGlobalBounds().top)

    shop.setFont(font);
    shop.setString("4. Aby zobaczyc Sklep");
    shop.setCharacterSize(15);
    shop.setPosition(0.f, 400.f);
    shop.setOrigin(shop.getGlobalBounds().width / 2, shop.getGlobalBounds().top / 2);


    buySpeed.setFont(font);
    buySpeed.setString("1. Aby zwiekszyc prekosc ruchu. \n          cena: 1 coin");
    buySpeed.setCharacterSize(15);
    buySpeed.setPosition(0.f, 100.f);
    buySpeed.setOrigin(buySpeed.getGlobalBounds().width / 2, buySpeed.getGlobalBounds().top / 2);


    buyLives.setFont(font);
    buyLives.setString("2. Aby kupic dodatkowe zycie. \n               cena: 2 coin'y");
    buyLives.setCharacterSize(15);
    buyLives.setPosition(0.f, 200.f);
    buyLives.setOrigin(buyLives.getGlobalBounds().width / 2, buyLives.getGlobalBounds().top / 2);

    buyDash.setFont(font);
    buyDash.setString("3. Aby odblokowac Dash'e. \n               cena: 3 coin'y");
    buyDash.setCharacterSize(15);
    buyDash.setPosition(0.f, 300.f);
    buyDash.setOrigin(buyDash.getGlobalBounds().width / 2, buyDash.getGlobalBounds().top / 2);

    buyGun.setFont(font);
    buyGun.setString("4. Aby odblowowac strzelanie. \n                cena: 4 coin'y");
    buyGun.setCharacterSize(15);
    buyGun.setPosition(0.f, 400);
    buyGun.setOrigin(buyGun.getGlobalBounds().width / 2, buyGun.getGlobalBounds().top / 2);

    buyGravity.setFont(font);
    buyGravity.setString("5. Aby odblowowac Latanie. \n                cena: 4 coin'y");
    buyGravity.setCharacterSize(15);
    buyGravity.setPosition(0.f, 500);
    buyGravity.setOrigin(buyGravity.getGlobalBounds().width / 2, buyGravity.getGlobalBounds().top / 2);


}


void Game::run() {
    bool playselected = false;
    shopSelected = false;
    while (window.isOpen()) {


        sf::Event event;
        if (!playselected and !shopSelected) {
            while (!playselected and !shopSelected) {
                coinCounter.setString("Coins: " + std::to_string(player.coins));
                lifeCounter.setString("Lives: " + std::to_string(player.lifes));
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::KeyPressed) {

                        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                            startL1.setFillColor(sf::Color::Green);


                        } else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                            startL2.setFillColor(sf::Color::Green);


                        } else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6 || event.key.code == sf::Keyboard::Escape) {
                            window.close();
                        } else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                            shopSelected = true;
                        } else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                            startL3.setFillColor(sf::Color::Green);
                        }
                    } else if (event.type == sf::Event::KeyReleased) {
                        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                            startL1.setFillColor(sf::Color::White);
                            if (player.currentLevel != 1) {
                                playselected = true;
                                currentLevel.generate(Level::level1);
                                player.currentLevel = 1;
                                //this->currentLevel =  GameMap(Level::level2);
                                player.position = currentLevel.playerStart;
                                player.defaultPosition = currentLevel.playerStart;
                                camera.position = player.position;
                            } else {
                                playselected = true;
                            }
                        } else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                            startL2.setFillColor(sf::Color::White);
                            if (player.level2Unlocked) {

                                playselected = true;
                                if (player.currentLevel != 2) {
                                    currentLevel.generate(Level::level2);
                                    player.currentLevel = 2;
                                    //this->currentLevel =  GameMap(Level::level2);
                                    player.position = currentLevel.playerStart;
                                    player.defaultPosition = currentLevel.playerStart;
                                    camera.position = player.position;
                                }
                            }
                        } else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                            startL3.setFillColor(sf::Color::White);
                            if (player.level3Unlocked) {
                                playselected = true;
                                if (player.currentLevel != 3) {

                                    currentLevel.generate(Level::level3);
                                    player.currentLevel = 3;
                                    //this->currentLevel =  GameMap(Level::level2);
                                    player.position = currentLevel.playerStart;
                                    player.defaultPosition = currentLevel.playerStart;
                                    camera.position = player.position;
                                }
                            }
                        }

                    }


                    window.clear();

                    window.draw(title);
                    window.draw(startL1);
                    window.draw(startL2);
                    window.draw(startL3);
                    window.draw(exitOption);
                    window.draw(coinCounter);
                    window.draw(shop);
                    window.draw(lifeCounter);
                    window.setView(
                            camera.GetView(window.getSize(),
                                           sf::Vector2f(title.getPosition().x, title.getPosition().y + 150)));
                    window.display();
                }
//***********************SKLEP**************************\\
                if (!playselected and shopSelected) {
                while (!playselected and shopSelected) {
                    coinCounter.setString("Coins: " + std::to_string(player.coins));
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();
                        else if (event.type == sf::Event::KeyPressed) {

                            if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                                //playselected = true;
                                if (player.coins > 0) {
                                    player.movespeedMultiplayer += 0.1f;
                                    player.coins--;
                                    coinCounter.setString("Coins: " + std::to_string(player.coins));
                                }

                            } else if (event.key.code == sf::Keyboard::Num2 ||
                                       event.key.code == sf::Keyboard::Numpad2) {
                                //playselected = true;
                                if (player.coins > 1) {
                                    player.coins = player.coins - 2;
                                    player.lifes++;
                                    coinCounter.setString("Coins: " + std::to_string(player.coins));
                                    lifeCounter.setString("Lives: " + std::to_string(player.lifes));
                                }


                            } else if (event.key.code == sf::Keyboard::Num3 ||
                                       event.key.code == sf::Keyboard::Numpad3) {
                                if (player.coins > 2 and !player.boughtDash) {
                                    player.coins = player.coins - 3;
                                    player.boughtDash = true;
                                    buyDash.setString("KUPIONE");
                                    buyDash.setFillColor(sf::Color::Green);
                                }

                            } else if (event.key.code == sf::Keyboard::Num4 ||
                                       event.key.code == sf::Keyboard::Numpad4) {
                                if (player.coins > 3 and !player.canShoot) {
                                    player.coins = player.coins - 4;
                                    player.canShoot = true;
                                    buyGun.setString("KUPIONE");
                                    buyGun.setFillColor(sf::Color::Green);
                                }

                            } else if (event.key.code == sf::Keyboard::Num5 ||
                                       event.key.code == sf::Keyboard::Numpad5) {
                                if (player.coins > 3 and !player.canReverseGravitiy) {
                                    player.coins = player.coins - 4;
                                    player.canReverseGravitiy = true;
                                    buyGravity.setString("KUPIONE");
                                    buyGravity.setFillColor(sf::Color::Green);
                                }

                            } else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6 || event.key.code == sf::Keyboard::Escape) {
                                //window.close();
                                shopSelected = false;
                            }
                        }


                        window.clear();

                        window.draw(title);
                        // window.draw(shop);
                        window.draw(buySpeed);
                        // window.draw(exitOption);
                        window.draw(coinCounter);
                        window.draw(lifeCounter);
                        window.draw(buyLives);
                        window.draw(buyDash);
                        window.draw(buyGun);
                        window.draw(buyGravity);
                        window.setView(
                                camera.GetView(window.getSize(),
                                               sf::Vector2f(title.getPosition().x, title.getPosition().y + 150)));
                        window.display();
                    }

                }
            }
        } else if (playselected) {
            while (playselected) {
                if (player.lifes < 1) {
                    playselected = false;


                }
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                            event.key.code == sf::Keyboard::Space) {
                            player.jump();
                        } else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                            player.moveLeft();

                        } else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                            player.moveRight();
                        } else if (event.key.code == sf::Keyboard::LShift) {
                            if (player.boughtDash) {
                                player.dash();
                            }
                        } else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                            //player.reverseGravity();
                            player.crouch();
                        } else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6 || event.key.code == sf::Keyboard::Escape) {
                            playselected = false;

                        }
                    } else if (event.type == sf::Event::KeyReleased) {
                        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right ||
                            event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                            player.stop();
                        } else if (event.key.code = sf::Keyboard::Down) {
                            player.uncrouch();
                        }
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (player.canShoot) {
                            sf::Vector2f target = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            player.fire(target, currentLevel.playerProjectiles);
                        }
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        if (player.canReverseGravitiy) {
                            player.Startfly();
                        }
                    } else if (sf::Event::MouseButtonReleased) {
                        player.Stopfly();
                        player.fired = false;
                    }
                }
                if (!playselected) {
                    window.setView(
                            camera.GetView(window.getSize(),
                                           sf::Vector2f(title.getPosition().x, title.getPosition().y + 150)));
                    break;
                }
                player.handleCollision(currentLevel.tileSprites, currentLevel.enemies,
                                       currentLevel.Projectiles, currentLevel.MovingTiles,
                                       currentLevel.playerProjectiles);
                player.update(1.0f / 60.0f); // Update player logic with a fixed timestep
                currentLevel.update(1.f / 60.f, player.position);

                window.clear(sf::Color::White);
                currentLevel.draw(window);
                window.setView(camera.GetView(window.getSize(), player.position));
                window.draw(player.getSprite());

                window.display();
            }
        }
        if (player.restartWhenLost()) {
            currentLevel.generate(Level::level1);
            player.currentLevel = 0;
            player.position = currentLevel.playerStart;
            player.defaultPosition = currentLevel.playerStart;
            camera.position = player.position;
            buyDash.setString("3. Aby odblokowac Dash'e. \n               cena: 3 coin'y");
            buyDash.setFillColor(sf::Color::White);
            buyGun.setString("4. Aby odblowowac strzelanie. \n                cena: 4 coin'y");
           buyGun.setFillColor(sf::Color::White);
            buyGravity.setString("5. Aby odblowowac Latanie. \n                cena: 4 coin'y");
           buyGravity.setFillColor(sf::Color::White);
        }

    }

}

