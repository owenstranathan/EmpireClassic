//
//  interface.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/30/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "interface.hpp"
#include "map.hpp"
#include "empire.hpp"

Tile * getTileFromCursorPos(const sf::RenderWindow & window) {
	int width = 32;
	int height = 32;
	sf::Vector2i vec = sf::Mouse::getPosition(window);
	int ptX = vec.x;
	int ptY = vec.y;
	for (int i = 0; i < MAP_W; i++) {
		for (int j = 0; j < MAP_H; j++) {
			int sqX = real_map[i][j].x * 32;
			int sqXWidth = sqX + width;
			int sqY = real_map[i][j].y * 32;
			int sqYHeight = sqY + height;
			if ((ptX > sqX && ptX < sqXWidth) && (ptY > sqY && ptY < sqYHeight)) {
				return &real_map[i][j];
			}
		}
	}
	return NULL;
}
