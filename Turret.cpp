//
// Created by Kuba on 04/01/2024.
//

#include "Turret.h"

#include "iostream"

Turret::Turret(sf::Vector2f position, float range) : position(position), range(range), projectileSpeed(1.5f) {
    if (!turretTexture.loadFromFile("resources/turret.png")) {
        // handle error
        std::cout<<"ERRRor"<<'\n';
    }

    sprite.setTexture(turretTexture);
    sprite.setColor(sf::Color::Blue);
    sprite.setPosition(position);
    //sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().top);
    clock = 0;
}

auto Turret::calcRange(sf::Vector2f targetPosition) {
    return std::sqrt((Turret::position.x - targetPosition.x) * (Turret::position.x - targetPosition.x))
           + ((Turret::position.y - targetPosition.y) * (Turret::position.y - targetPosition.y));
}


void Turret::shoot(sf::Vector2f targetPosition, std::vector<Projectile> &projectileList) {
//idea: https://en.sfml-dev.org/forums/index.php?topic=27150.0
    float destinationY, destinationX = 0;
    //wyliczamy i normalizujemy wektor kierunku pocisku
    sf::Vector2f direction = sf::Vector2f(targetPosition.x - Turret::position.x, targetPosition.y - Turret::position.y);
    auto length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (length != 0) {
        direction = sf::Vector2f(direction.x / length, direction.y / length);
    } else direction = sf::Vector2f(0, 0);
    direction = sf::Vector2f(direction.x * Turret::projectileSpeed, direction.y * Turret::projectileSpeed);
    //tworzymy pocisk
    Projectile projectile(Turret::position, direction, calcRange(targetPosition), this->position);
    projectileList.push_back(projectile);
}

void Turret::update(float deltaTime, sf::Vector2f player, std::vector<Projectile> &projectileList) {
    if (clock == 120) {
        if(calcRange(player) <= range){
        Turret::shoot(player, projectileList);
        clock = 0;}
    } else {
        clock += 1;
    }

    }