//
//  interface.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/30/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//


#include "interface.hpp"




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

void Selection::command(sf::Keyboard::Key code, Map & map)
{
    if(tile && tile->piece)
    {
        Piece * piece = tile->piece;
        switch(code)
        {
            case sf::Keyboard::W:   //NORTH
                piece->move(NORTH, map);
                break;
            case sf::Keyboard::Q:   //NORTHWEST
                piece->move(NORTHWEST, map);
                break;
            case sf::Keyboard::A:   //WEST
                piece->move(WEST, map);
                break;
            case sf::Keyboard::Z:   //SOUTHWEST
                piece->move(SOUTHWEST, map);
                break;
            case sf::Keyboard::X:   //SOUTH
                piece->move(SOUTH, map);
                break;
            case sf::Keyboard::C:   //SOUTHEAST
                piece->move(SOUTHEAST, map);
                break;
            case sf::Keyboard::D:   //EAST
                piece->move(EAST, map);
                break;
            case sf::Keyboard::E:   //NORTHEAST
                piece->move(NORTHEAST, map);
                break;
            case sf::Keyboard::U:   //Transport unload
                if(Transport * t = dynamic_cast<Transport*>(piece))
                {
                    t->unload(map);
                }
                break;
            case sf::Keyboard::L:
                if(Transport * t = dynamic_cast<Transport*>(piece))
                {
                    t->load(map);
                }
                break;
            case sf::Keyboard::K:
                if(Army * a = dynamic_cast<Army*>(piece))
                {
                    a->capture(map);
                }
            default:
                break;
        }
        tile = &map.map[piece->x][piece->y];
    }
}


////////////////////////////////////////////////////////////////////////////////////////
//TEXT//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Text::Text(std::string textContent, const char* fontName )
{
    font.loadFromFile(resourcePath() + fontName);
    setFont(font);

}

/////////////////////////////////////////////////////////////////////////////////////////
//MISC///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


Tile * getTileFromCursorPos(const Window & window, Map & map)
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
    if(map.vision[i][j])
    {
        return &map.map[i][j];
    }
    return NULL;
    
}

