//
//  map.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/27/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "map.hpp"
#include "empire.hpp"
#include "ResourcePath.hpp"




////////////////////////////////////////////////////////////////////////////////////////
//TILE//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
void Tile::draw(sf::RenderWindow & window)
{
    sprite.setPosition(x*32, y*32);
    window.draw(sprite);
}

////////////////////////////////////////////////////////////////////////////////////////
//PIECE/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
void Piece::draw(sf::RenderWindow & window)
{
    sprite.setPosition(x*32, y*32);
    window.draw(sprite);
}

////////////////////////////////////////////////////////////////////////////////////////
//VISITOR///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

struct TypeVisitor : public Visitor
{
    Type type;
    void visit(Transport * t){ type = TRANSPORT; }
    void visit(City * c){ type = CITY; }
    void visit(Army * a){ type = ARMY; }
    //add stuff for other types
    
};

Type getType(Piece * piece)
{
    TypeVisitor v;
    piece->accept(v);
    return v.type;
}


////////////////////////////////////////////////////////////////////////////////////////
//TRANSPORT/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Transport::Transport(int arg_x, int arg_y) : Piece(arg_x, arg_y), hp(5)
{
}


void Transport::move(Direction dir)
{
    //switch on which direction. diagionals included.
    switch (dir)
    {
        case NORTH:
            if(canRecieve(x,y-1))
            {
                if(real_map[x][y-1].terrain == WATER)
                {
                    //moves piece to new tile in the eyes of the map.
                    real_map[x][y-1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    //updates the piece's internal position
                    y -=1;
                }
            }
            break;
            
        case EAST:
            if(canRecieve(x+1,y))
            {
                if(real_map[x+1][y].terrain == WATER)
                {
                    
                    real_map[x+1][y].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x+=1;
                }
                
            }
            break;
            
        case SOUTH:
            if(canRecieve(x,y+1))
            {
                if(real_map[x][y+1].terrain == WATER)
                {
                    real_map[x][y+1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    y+=1;
                }
                
            }
            break;
            
        case WEST:
            if(canRecieve(x-1,y))
            {
                if(real_map[x-1][y].terrain == WATER)
                {
                    real_map[x-1][y].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x-=1;
                }
                
            }
            break;
            
        case NORTHEAST:
            if(canRecieve(x+1,y-1))
            {
                if(real_map[x+1][y-1].terrain == WATER)
                {
                    
                    real_map[x+1][y-1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x+=1;
                    y-=1;
                }
                
            }
            break;
            
        case NORTHWEST:
            if(canRecieve(x-1,y-1))
            {
                if(real_map[x-1][y-1].terrain == WATER)
                {
                    real_map[x-1][y-1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x-=1;
                    y-=1;
                }
            }
            break;
            
            
        case SOUTHEAST:
            if(canRecieve(x+1,y+1))
            {
                if(real_map[x+1][y+1].terrain == WATER)
                {
                    real_map[x+1][y+1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x+=1;
                    y+=1;
                }
                
            }
            break;
            
        case SOUTHWEST:
            if(canRecieve(x-1,y+1))
            {
                if(real_map[x-1][y+1].terrain == WATER)
                {
                    real_map[x-1][y+1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x-=1;
                    y+=1;
                }
                
            }
            break;
    }//end switch
    updateVision(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////
//CITY//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
City::City(int arg_x, int arg_y, int arg_id) : Piece(arg_x, arg_y), id(arg_id)
{ }

void City::move(Direction dir) { }

////////////////////////////////////////////////////////////////////////////////////////
//ARMY//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
Army::Army(int arg_x, int arg_y) : Piece(arg_x, arg_y)
{ }

void Army::move(Direction dir)
{
    //switch on which direction. diagionals included.
    switch (dir)
    {
        case NORTH:
            if(canRecieve(x,y-1))
            {
                if(real_map[x][y-1].terrain == LAND)
                {
                    //moves piece to new tile in the eyes of the map.
                    real_map[x][y-1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    //updates the piece's internal position
                    y -=1;
                }
            }
            break;
            
        case EAST:
            if(canRecieve(x+1,y))
            {
                if(real_map[x+1][y].terrain == LAND)
                {
                    
                    real_map[x+1][y].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x+=1;
                }
                
            }
            break;
            
        case SOUTH:
            if(canRecieve(x,y+1))
            {
                if(real_map[x][y+1].terrain == LAND)
                {
                    real_map[x][y+1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    y+=1;
                }
                
            }
            break;
            
        case WEST:
            if(canRecieve(x-1,y))
            {
                if(real_map[x-1][y].terrain == LAND)
                {
                    real_map[x-1][y].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x-=1;
                }
                
            }
            break;
            
        case NORTHEAST:
            if(canRecieve(x+1,y-1))
            {
                if(real_map[x+1][y-1].terrain == LAND)
                {
                    
                    real_map[x+1][y-1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x+=1;
                    y-=1;
                }
                
            }
            break;
            
        case NORTHWEST:
            if(canRecieve(x-1,y-1))
            {
                if(real_map[x-1][y-1].terrain == LAND)
                {
                    real_map[x-1][y-1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x-=1;
                    y-=1;
                }
            }
            break;
            
            
        case SOUTHEAST:
            if(canRecieve(x+1,y+1))
            {
                if(real_map[x+1][y+1].terrain == LAND)
                {
                    real_map[x+1][y+1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x+=1;
                    y+=1;
                }
                
            }
            break;
            
        case SOUTHWEST:
            if(canRecieve(x-1,y+1))
            {
                if(real_map[x-1][y+1].terrain == LAND)
                {
                    real_map[x-1][y+1].piece = real_map[x][y].piece;
                    real_map[x][y].piece = NULL;
                    x-=1;
                    y+=1;
                }
                
            }
            break;
    }//end switch
    
    updateVision(x, y);

}


////////////////////////////////////////////////////////////////////////////////////////
//WINDOW////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Window::Window(int width, int height, const char * title) : sf::RenderWindow(sf::VideoMode(width, height), title)
{
}

void Window::init(const char * iconFile, char const * musicFile)
{
    if (!icon.loadFromFile(resourcePath() + iconFile)) {
        return EXIT_FAILURE;
    }
    //Set the windows icon to the loaded Icon image
    setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //open and play the music
    if (!music.openFromFile(resourcePath() + musicFile)) {
        return EXIT_FAILURE;
    }
    music.play();
    
    //cap the frame rate limit
    setFramerateLimit(60);
    
    
}


////////////////////////////////////////////////////////////////////////////////////////
//MISC//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

bool canRecieve(int x, int y)
{
    if(isOnMap(x,y))
    {
        if(real_map[x][y].piece == NULL)
        {
            return true;
        }
    }
    return false;
}




