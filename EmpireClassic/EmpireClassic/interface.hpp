//
//  interface.h
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/30/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "empire.hpp"
#include "display.hpp"
#include "map.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct Map;
struct Window;
struct Tile;
struct Text;


///////////////////////////////////////////////////////////////////////////////
//TEXT/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct Text : sf::Text
{
    sf::Font font;
    std::string text;
    
    Text(std::string textContent, const char* fontName);
    
    //draw for text, so you can draw regarless of view
    void draw(Window & window);
    
    
};

///////////////////////////////////////////////////////////////////////////////
//SELECTION////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct Selection
{

    Tile * tile;
    sf::Sprite sprite;
    Text message;
    //constructor
    Selection();

    //draw the selection onto the window
    void draw(sf::RenderTexture &);

    //do action based on the key
    void command(sf::Keyboard::Key, Map & map);

    //update the message based on the tile selected
    void updateMessage();
};


///////////////////////////////////////////////////////////////////////////////
//MISC/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


Tile * getTileFromCursorPos(const Window & window, Map & map);



#endif /* defined(INTERFACE_HPP) */
