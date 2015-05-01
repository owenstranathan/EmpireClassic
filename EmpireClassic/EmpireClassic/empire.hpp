//
//  empire.hpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/27/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "ResourcePath.hpp"



//Number of turns that have elapsed
extern int turn;

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
//TILE//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
enum Terrain
{
    WATER,
    LAND
};

struct Tile
{
    //Sprite of the tile
    sf::Sprite sprite;
    
    //The type of terrain the tile is
    Terrain terrain;
    
    //The piece located on the terrain
    Piece * piece;
    
    //position of the tile
    int x, y;
    
    //draws the piece at it's location
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
    Piece(int arg_x, int arg_y): x(arg_x), y(arg_y) {}
    
    //draws the piece at its location
    void draw(sf::RenderWindow &);
    
    //for type related actions
    virtual void accept(Visitor & v) = 0;
    
    virtual void move() {}
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
    Transport(int, int);
    
    //for type specific actions
    void accept(Visitor & v) { v.visit(this); }
    
    //moving functionality
    void move(Direction dir);
    
};


////////////////////////////////////////////////////////////////////////////////////////
//CITY//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

//for giving cities ID numbers
extern int cityCount;

struct City : Piece
{
    //rate of production per turn
    int rate;
    //last turn Generated
    int lastGenerationTurn;
    //type of unit to produce
    std::string typeToMake;
    
    //City ID
    int id;
    
    //constructor that takes a position
    City(int, int, int);
    
    //for type specific actions
    void accept(Visitor & v) { v.visit(this); }
    
    //to generate a new Piece
    Piece * generate();
    
    //give ownership of a city to another player
    void submitTo(Owner & newOwner);

    //moving functionality
    void move(Direction dir);

    
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
    
    Army(int, int);
    
    void accept(Visitor & v ){ v.visit(this);}
        
    //movement functionally
    
    void move(Direction dir);
    
};

////////////////////////////////////////////////////////////////////////////////////////
//MISC//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

//determines whether a tile has a piece or not
bool canRecieve(int, int);




#endif /* defined(EMPIRE_HPP) */

