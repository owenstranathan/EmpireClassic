//
//  map.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/27/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//



#include "empire.hpp"
#include "ResourcePath.hpp"
#include <iostream>






///////////////////////////////////////////////////////////////////////////////
//PIECE////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Piece::draw(sf::RenderTexture & world)
{
    sprite.setPosition(x*32, y*32);
    if(owner == PLAYER)
    {
        sprite.setColor(sf::Color(250,128,114));
    }
    world.draw(sprite);
}

///////////////////////////////////////////////////////////////////////////////
//VISITOR//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////////////////////
//TRANSPORT////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Transport::Transport(int arg_x, int arg_y, Owner arg_owner)
: Piece(arg_x, arg_y, arg_owner)
{
    sprite.setTexture(transport);
    contents.push_back(new Army(arg_x, arg_y, PLAYER));
}


void Transport::move(Direction dir, Map & map)
{
    //switch on which direction. diagionals included.
    switch (dir)
    {
        case NORTH:
            if(canRecieve(x,y-1,map))
            {
                if(map.map[x][y-1].terrain == WATER)
                {
                    //moves piece to new tile in the eyes of the map.
                    map.map[x][y-1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    //updates the piece's internal position
                    y -=1;
                }
            }
            break;

        case EAST:
            if(canRecieve(x+1,y,map))
            {
                if(map.map[x+1][y].terrain == WATER)
                {

                    map.map[x+1][y].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x+=1;
                }

            }
            break;

        case SOUTH:
            if(canRecieve(x,y+1,map))
            {
                if(map.map[x][y+1].terrain == WATER)
                {
                    map.map[x][y+1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    y+=1;
                }

            }
            break;

        case WEST:
            if(canRecieve(x-1,y,map))
            {
                if(map.map[x-1][y].terrain == WATER)
                {
                    map.map[x-1][y].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x-=1;
                }

            }
            break;

        case NORTHEAST:
            if(canRecieve(x+1,y-1,map))
            {
                if(map.map[x+1][y-1].terrain == WATER)
                {

                    map.map[x+1][y-1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x+=1;
                    y-=1;
                }

            }
            break;

        case NORTHWEST:
            if(canRecieve(x-1,y-1,map))
            {
                if(map.map[x-1][y-1].terrain == WATER)
                {
                    map.map[x-1][y-1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x-=1;
                    y-=1;
                }
            }
            break;


        case SOUTHEAST:
            if(canRecieve(x+1,y+1,map))
            {
                if(map.map[x+1][y+1].terrain == WATER)
                {
                    map.map[x+1][y+1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x+=1;
                    y+=1;
                }

            }
            break;

        case SOUTHWEST:
            if(canRecieve(x-1,y+1,map))
            {
                if(map.map[x-1][y+1].terrain == WATER)
                {
                    map.map[x-1][y+1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x-=1;
                    y+=1;
                }

            }
            break;
    }//end switch
    map.updateVision(x, y);
}


void Transport::unload(Map & map)
{
    //UNLOAD NORTH
    if(canRecieve(x,y-1,map)
        && map.map[x][y-1].terrain == LAND
        && !contents.empty())
    {

        map.map[x][y-1].piece = contents.front();
        contents.erase(contents.begin(), contents.begin()+1);
        map.map[x][y-1].piece->x = x;
        map.map[x][y-1].piece->y = y-1;

    }
    //UNLOAD EAST
    else if(canRecieve(x+1,y,map)
        && map.map[x+1][y].terrain == LAND
        && !contents.empty())
    {

        map.map[x+1][y].piece = contents.front();
        contents.erase(contents.begin(), contents.begin()+1);
        map.map[x+1][y].piece->x = x+1;
        map.map[x+1][y].piece->y = y;

    }
    //UNLOAD SOUTH
    else if(canRecieve(x,y+1,map)
        && map.map[x][y+1].terrain == LAND
        && !contents.empty())
    {

        map.map[x][y+1].piece = contents.front();
        contents.erase(contents.begin(), contents.begin()+1);
        map.map[x][y+1].piece->x = x;
        map.map[x][y+1].piece->y = y+1;
    }
    //UNLOAD WEST
    else if(canRecieve(x-1,y,map)
        && map.map[x-1][y].terrain == LAND
        && !contents.empty())
    {

        map.map[x-1][y].piece = contents.front();
        contents.erase(contents.begin(), contents.begin()+1);
        map.map[x-1][y].piece->x = x-1;
        map.map[x-1][y].piece->y = y;

    }


}

void Transport::load(Map & map)
{
    //LOAD NORTH
    if(map.map[x][y-1].piece && getType(map.map[x][y-1].piece) == ARMY)
    {
        contents.push_back(map.map[x][y-1].piece);
        map.map[x][y-1].piece = NULL;
    }
    //LOAD EAST
    else if(map.map[x+1][y].piece && getType(map.map[x+1][y].piece) == ARMY)
    {
        contents.push_back(map.map[x+1][y].piece);
        map.map[x+1][y].piece = NULL;
    }
    //LOAD SOUTH
    else if(map.map[x][y+1].piece && getType(map.map[x][y+1].piece) == ARMY)
    {
        contents.push_back(map.map[x][y+1].piece);
        map.map[x][y+1].piece = NULL;
    }
    //LOAD WEST
    else if(map.map[x-1][y].piece && getType(map.map[x-1][y].piece) == ARMY)
    {
        contents.push_back(map.map[x-1][y].piece);
        map.map[x-1][y].piece = NULL;
    }


}

///////////////////////////////////////////////////////////////////////////////
//CITY/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

City::City(int arg_x, int arg_y, int arg_id, Owner arg_owner)
: Piece(arg_x, arg_y, arg_owner), id(arg_id)
{
    sprite.setTexture(city);
}

void City::move(Direction dir, Map  & map) { }

///////////////////////////////////////////////////////////////////////////////
//ARMY/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Army::Army(int arg_x, int arg_y, Owner arg_owner)
: Piece(arg_x, arg_y, arg_owner)
{
    sprite.setTexture(army);
}

void Army::move(Direction dir, Map &map)
{
    //switch on which direction. diagionals included.
    switch (dir)
    {
        case NORTH:
            if(canRecieve(x,y-1, map))
            {
                if(map.map[x][y-1].terrain == LAND)
                {
                    //moves piece to new tile in the eyes of the map.
                    map.map[x][y-1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    //updates the piece's internal position
                    y -=1;
                }
            }
            break;

        case EAST:
            if(canRecieve(x+1,y, map))
            {
                if(map.map[x+1][y].terrain == LAND)
                {

                    map.map[x+1][y].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x+=1;
                }

            }
            break;

        case SOUTH:
            if(canRecieve(x,y+1, map))
            {
                if(map.map[x][y+1].terrain == LAND)
                {
                    map.map[x][y+1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    y+=1;
                }

            }
            break;

        case WEST:
            if(canRecieve(x-1,y, map))
            {
                if(map.map[x-1][y].terrain == LAND)
                {
                    map.map[x-1][y].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x-=1;
                }

            }
            break;

        case NORTHEAST:
            if(canRecieve(x+1,y-1,map))
            {
                if(map.map[x+1][y-1].terrain == LAND)
                {

                    map.map[x+1][y-1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x+=1;
                    y-=1;
                }

            }
            break;

        case NORTHWEST:
            if(canRecieve(x-1,y-1,map))
            {
                if(map.map[x-1][y-1].terrain == LAND)
                {
                    map.map[x-1][y-1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x-=1;
                    y-=1;
                }
            }
            break;


        case SOUTHEAST:
            if(canRecieve(x+1,y+1,map))
            {
                if(map.map[x+1][y+1].terrain == LAND)
                {
                    map.map[x+1][y+1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x+=1;
                    y+=1;
                }

            }
            break;

        case SOUTHWEST:
            if(canRecieve(x-1,y+1,map))
            {
                if(map.map[x-1][y+1].terrain == LAND)
                {
                    map.map[x-1][y+1].piece = map.map[x][y].piece;
                    map.map[x][y].piece = NULL;
                    x-=1;
                    y+=1;
                }

            }
            break;
    }//end switch

    map.updateVision(x, y);

}

void Army::capture(Map & map)
{
    //CAPTURE NORTH
    if(map.map[x][y-1].piece
        && getType(map.map[x][y-1].piece) != ARMY
        && map.map[x][y-1].piece->owner != owner)
    {
        map.map[x][y-1].piece->owner = owner;
    }
    //CAPTURE EAST
    else if(map.map[x+1][y].piece
        && getType(map.map[x+1][y].piece) != ARMY
        && map.map[x+1][y].piece->owner != owner)
    {
        map.map[x+1][y].piece->owner = owner;
    }
    //CAPTURE SOUTH
    else if(map.map[x][y+1].piece
        && getType(map.map[x][y+1].piece) != ARMY
        && map.map[x][y+1].piece->owner != owner)
    {
        map.map[x][y+1].piece->owner = owner;
    }
    //CAPTURE WEST
    else if(map.map[x-1][y].piece
        && getType(map.map[x-1][y].piece) != ARMY
        && map.map[x-1][y].piece->owner != owner)
    {
        map.map[x-1][y].piece->owner = owner;
    }
}
