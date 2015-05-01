//
//  interface.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/30/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "interface.hpp"
#include "empire.hpp"
#include "map.hpp"

Tile * getTileFromCursorPos(const sf::RenderWindow & window) {
	sf::Vector2i vec = sf::Mouse::getPosition(window);
	int i = vec.x / 32;
	int j = vec.y / 32;
	return &real_map[i][j];
}
