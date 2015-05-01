//
//  interface.h
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/30/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "empire.hpp"

Tile * getMouseTile(sf::Mouse &, sf::Window &);

#endif /* defined(INTERFACE_HPP) */
