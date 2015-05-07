//
//  display.hpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/28/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//
//  The display functions are responsible for
//  nearly all graphical aspects of the game
//  all images in the game are drawing to an sfml
//  RenderTexture which is
//  then drawn to a render window
//  of sfml View


#ifndef DISPLAY_H
#define DISPLAY_H


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "empire.hpp"
#include "interface.hpp"
#include "map.hpp"


//SCREEN SIZE VALUES
//const int SCREEN_WIDTH = MAP_W * 32;
//const int SCREEN_HEIGHT = MAP_H * 32;

//external textures
extern sf::Texture fogTexture;
extern sf::Texture city;
extern sf::Texture water;
extern sf::Texture land;
extern sf::Texture transport;
extern sf::Texture army;
extern sf::Texture selection;

//constant fog sprite to draw fog of war
extern sf::Sprite fog;

//to load the textures from files
//file paths are hardcoded
//returns false on load failure
//true on load success
bool loadTextures();

//set's map sprite textures
void loadMapTextures();

//Draw the real map
void drawMap(sf::RenderTexture & world);



///////////////////////////////////////////////////////////////////////////////
//WINDOW///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
struct Window : sf::RenderWindow
{
    sf::Music music;
    sf::Mouse mouse;
    sf::Image icon;
    sf::View view;

    //constructor sets up the render window
    Window(int, int, const char *);

    //initializes the icon, music and view port
    void init(char const *, char const *);

    //handles scrolling
    void scroll(sf::Keyboard::Key);

};


///////////////////////////////////////////////////////////////////////////////
//WORLD////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
struct World : sf::RenderTexture
{
    sf::Sprite sprite;
    
    World(int, int);
    
    void draw(sf::RenderWindow &);
};



#endif /* defined(__EmpireClassic__display__) */
