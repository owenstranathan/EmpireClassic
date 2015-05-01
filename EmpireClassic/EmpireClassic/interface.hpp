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

<<<<<<< HEAD
#include "empire.hpp"

Tile * getMouseTile(sf::Mouse &, sf::Window &);
=======
Tile * getTileFromCursorPos(const sf::RenderWindow & window);
>>>>>>> bdb286d93059501a6a7d41dc81a69fcb7a79b071

#endif /* defined(INTERFACE_HPP) */
