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


/////////////
//VISITOR////
/////////////
struct Visitor
{
    virtual void visit(Transport *) {}
    virtual void visit(City *) {}
    virtual void visit(Army *) {}
};

//for getting the type of a piece
//using the visitor pattern
std::string getType(Piece * piece);



/////////////
//TILE///////
/////////////
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
    std::vector<Piece *> pieceList;
    
    //position of the tile
    int x, y;
    
    //draws the piece at it's location
    void draw(sf::RenderWindow &);
};


///////////////
//PIECE////////
///////////////

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
    
    //draws the piece at its location
    void draw(sf::RenderWindow &);
    
    //for type related actions
    virtual void accept(Visitor & v) = 0;
    
};



struct Transport : Piece
{
    //linked list for contents
    std::vector<Piece *> contents;
    int vision;
    int hp;
    int moves;
    
    //for type specific actions
    void accept(Visitor & v) { v.visit(this); }
    
    //moving functionality
    
};


//////////////
//CITY////////
//////////////
struct City : Piece
{
    //rate of production per turn
    int rate;
    //last turn Generated
    int lastGenerationTurn;
    std::string typeToMake;
    
    //for type specific actions
    void accept(Visitor & v) { v.visit(this); }
    
    //to generate a new Piece
    Piece * generate();
    
    //give ownership of a city to another player
    void submitTo(Owner & newOwner);
    
};

struct Army : Piece
{
    int vision;
    int strength;
    int hp;
    int moves;
    
    void accept(Visitor & v ){ v.visit(this);}
        
    //movement functionally
    
};






#endif /* defined(EMPIRE_HPP) */

