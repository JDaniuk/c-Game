//
// Created by Kuba on 29/11/2023.
//

#include "Camera.h"

//zoomlevel is how much we zoom...
//higher numbers means LESS zoom
Camera::Camera(float zoomLevel) :zoomLevel(zoomLevel) {

}

sf::View Camera::GetView(sf::Vector2u windowsize, sf::Vector2f position) {

    float aspect = (float)windowsize.x / (float)windowsize.y; //returns witdh to height ratio
    sf::Vector2f size{};
    if(aspect<1.0f){ //if window is taller than its width
        size = sf::Vector2f (zoomLevel, zoomLevel/aspect);
    } else
        size = sf::Vector2f (zoomLevel * aspect, zoomLevel);
    prevpos = position;

    return sf::View(position, size);
}