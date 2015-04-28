//
//  empire.hpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/27/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "ResourcePath.hpp"


//global HEIGHT and WIDTH variables



const int MAP_W = 30;
const int MAP_H = 20;



enum Owner
{
    PLAYER,
    COMPUTER,
    NONE
};



//The piece struct
//will contain the majority of the behavior and information for all pieces
struct piece
{
    sf::Sprite sprite;
    Owner owner;
    bool isLand;
    
    //default constructor
    //sets Owner to NONE
    piece();
    
    
    //draws the piece at its location
    void draw(sf::RenderWindow &);
    
};


//The real map that hold all the in game objects
extern piece * real_map[MAP_W][MAP_H];
//the players view map that simply dictates what is and is not visible by the player.
extern piece * player_map[MAP_W][MAP_H];

#endif /* defined(EMPIRE_HPP) */

