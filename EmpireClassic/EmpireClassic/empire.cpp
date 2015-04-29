//
//  map.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/27/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "empire.hpp"
#include "ResourcePath.hpp"


///////////////
//TILE/////////
///////////////
void Tile::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

///////////////
//PIECE////////
///////////////
void Piece::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

////////////////
//VISITOR///////
////////////////
struct TypeVisitor : public Visitor
{
    std::string type;
    void visit(Transport * t){ type = "Transport"; }
    void visit(City * c){ type = "City"; }
    //add stuff for other types
    
};

std::string getType(Piece * piece)
{
    TypeVisitor v;
    piece->accept(v);
    return v.type;
}

