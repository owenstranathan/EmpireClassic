//
//  display.hpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/28/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

//SCREEN SIZE VALUES
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

//external textures
extern sf::Texture fog;
extern sf::Texture city;
extern sf::Texture water;
extern sf::Texture land;

//to load the textures from files
//file paths are hardcoded
//returns false on load failure
//true on load success
bool loadTextures();

//set's map sprite textures
void loadMapTextures();

//Draw the real map
void drawRealMap(sf::RenderWindow & window);

//Draw the player map
void drawPlayerMap(sf::RenderWindow & window);


#endif /* defined(__EmpireClassic__display__) */
