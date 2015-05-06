//
//  actions.h
//  EmpireClassic
//
//  Created by Owen Stranathan on 5/6/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "map.hpp"
#include "interface.hpp"
#include "display.hpp"
#include "empire.hpp"


struct Player
{
    Selection selection;
    std::vector<Piece *> pieces;
    Player();
};

void checkForAction(Player &);

#endif /* defined(ACTIONS_HPP) */
