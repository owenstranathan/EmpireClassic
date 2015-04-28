//
//  map.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/27/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "empire.hpp"
#include "ResourcePath.hpp"






///////////////////////
//PIECE////////////////
///////////////////////
void piece::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

piece::piece():owner(NONE)
{
}
