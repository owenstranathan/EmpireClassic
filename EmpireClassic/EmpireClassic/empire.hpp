//
//  empire.hpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/27/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#ifndef EMPIRE_HPP
#define EMPIRE_HPP


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

#include "interface.hpp"
#include "map.hpp"
#include "display.hpp"


//Struct 
struct Tile;
struct Visitor;
struct Piece;
struct Transport;
struct City;
struct Army;



//vactir to hold all the pieces the player owns
extern std::vector<Piece *> player_pieces;

////////////////////////////////////////////////////////////////////////////////////////
//DIRECTIONS////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
enum Direction
{
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST
};


////////////////////////////////////////////////////////////////////////////////////////
//VISITOR///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

struct Visitor
{
    virtual void visit(Transport *) {}
    virtual void visit(City *) {}
    virtual void visit(Army *) {}
};
//for getting the type of a piece
//using the visitor pattern
enum Type
{
    CITY,
    TRANSPORT,
    ARMY
};

//Returns an enum of the type of piece
Type getType(Piece * piece);

////////////////////////////////////////////////////////////////////////////////////////
//WORLD////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
struct World : sf::RenderTexture
{
    sf::Sprite sprite;
    
    World(int, int);
    
    void draw(sf::RenderWindow &);
};



////////////////////////////////////////////////////////////////////////////////////////
//PIECE/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

enum Owner
{
    PLAYER,
    COMPUTER,
    NEUTRAL
};

struct Piece
{
    //The owner of the piece
    Owner owner;
    
    //The sprite of the piece
    sf::Sprite sprite;
    
    //the position of the piece
    int x, y;
    
    //inheader definition of the Piece constructor only needed
    //to initialize the position variables
    Piece(int arg_x, int arg_y, Owner arg_owner): x(arg_x), y(arg_y), owner(arg_owner)  {}
    
    //draws the piece at its location
    void draw(sf::RenderTexture &);
    
    //for type related actions
    virtual void accept(Visitor & v) = 0;
    
    virtual void move(Direction dir, Map & map) {}
};


////////////////////////////////////////////////////////////////////////////////////////
//TRANSPORT/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
struct Transport : Piece
{
    //linked list for contents
    std::vector<Piece *> contents;
    const int vision = 1;
    int hp;
    int moves;
    
    //constructor that takes a position
    Transport(int, int, Owner);
    
    //for type specific actions
    void accept(Visitor & v) { v.visit(this); }
    
    //moving functionality
    void move(Direction dir, Map & map);
    
    //for unloading armies
    void unload(Map & map);
    
    //for loading armies
    void load(Map & map);
    
};


////////////////////////////////////////////////////////////////////////////////////////
//CITY//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

//for giving cities ID numbers
extern int cityCount;

struct City : Piece
{
    
    //stuff inside the city
    std::vector<Piece *> contents;
    //rate of production per turn
    int rate;
    //last turn Generated
    int lastGenerationTurn;
    //type of unit to produce
    std::string typeToMake;
    
    //City ID
    int id;
    
    //constructor that takes a position
    City(int, int, int, Owner);
    
    //for type specific actions
    void accept(Visitor & v) { v.visit(this); }
    
    //to generate a new Piece
    Piece * generate();
    
    //give ownership of a city to another player
    void submitTo(Owner & newOwner);

    //moving functionality
    void move(Direction dir, Map & map);

    
};

////////////////////////////////////////////////////////////////////////////////////////
//ARMY//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
struct Army : Piece
{
    //for how far it can see
    int vision;
    int strength;
    int hp;
    int moves;
    
    Army(int, int, Owner);
    
    void accept(Visitor & v ){ v.visit(this);}
        
    //movement functionality
    void move(Direction dir, Map& map);
    
    //capture cities and docked transports
    void capture(Map & map);
    
};




////////////////////////////////////////////////////////////////////////////////////////
//MISC//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



#endif /* defined(EMPIRE_HPP) */

