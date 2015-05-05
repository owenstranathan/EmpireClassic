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
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct Selection
{
    Piece * piece;
    
};

Tile * getTileFromCursorPos(const sf::RenderWindow & window);



#endif /* defined(INTERFACE_HPP) */

