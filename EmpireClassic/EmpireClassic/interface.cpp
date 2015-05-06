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


/////////////////////////////////////////////////////////////////////////////////////////
//SELECTION//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


Selection::Selection() : tile(NULL)
{
    sprite.setTexture(selection);
}


void Selection::draw(sf::RenderTexture & world)
{
    if(tile != NULL)
    {
        sprite.setPosition(tile->x * 32, tile->y *32);
        world.draw(sprite);
    }
}

void Selection::command(sf::Keyboard::Key code)
{
    if(tile && tile->piece)
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

/////////////////////////////////////////////////////////////////////////////////////////
//MISC///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


Tile * getTileFromCursorPos(const Window & window)
{
    
    //center position of the viewport in pixels
    sf::Vector2f viewPos = window.view.getCenter();
    //size of the viewport in pixels
    sf::Vector2f viewSize = window.view.getSize();
    //find the size of half the viewport
    viewSize.x = viewSize.x/2;
    viewSize.y = viewSize.y/2;
    //use that to determine the offset from the absolute position on the world map to the view port
    sf::Vector2f offset(viewPos.x - viewSize.x, viewPos.y - viewSize.y);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //get tile of mouse click by adding the offset to the mouse position in the view
    int i = (offset.x+mousePos.x) / 32;
    int j = (offset.y+mousePos.y) / 32;
    if(player_map[i][j])
    {
        return &real_map[i][j];
    }
    return NULL;
    
}

