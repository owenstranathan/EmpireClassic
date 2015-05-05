//
//  interface.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/30/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "display.hpp"
#include "interface.hpp"
#include "empire.hpp"
#include "map.hpp"

Tile * getTileFromCursorPos(const sf::RenderWindow & window) {
	sf::Vector2i vec = sf::Mouse::getPosition(window);
	int i = vec.x / 32;
	int j = vec.y / 32;
	return &real_map[i][j];
}


Selection::Selection() : tile(NULL)
{
    sprite.setTexture(selection);
}


void Selection::draw(sf::RenderWindow & window)
{
    if(tile != NULL)
    {
        sprite.setPosition(tile->x * 32, tile->y *32);
        window.draw(sprite);
    }
}

void Selection::command(sf::Keyboard::Key code)
{
    if(tile->piece)
    {
        Piece * piece = tile->piece;
        switch(code)
        {
            case sf::Keyboard::W:   //NORTH
                piece->move(NORTH);
                break;
            case sf::Keyboard::Q:   //NORTHWEST
                piece->move(NORTHWEST);
                break;
            case sf::Keyboard::A:   //WEST
                piece->move(WEST);
                break;
            case sf::Keyboard::Z:   //SOUTHWEST
                piece->move(SOUTHWEST);
                break;
            case sf::Keyboard::X:   //SOUTH
                piece->move(SOUTH);
                break;
            case sf::Keyboard::C:   //SOUTHEAST
                piece->move(SOUTHEAST);
                break;
            case sf::Keyboard::D:   //EAST
                piece->move(EAST);
                break;
            case sf::Keyboard::E:   //NORTHEAST
                piece->move(NORTHEAST);
                break;
            default:
                break;
        }
        tile = &real_map[piece->x][piece->y];
    }
}
