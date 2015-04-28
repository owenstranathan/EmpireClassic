//
//  display.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/28/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "display.hpp"
#include "ResourcePath.hpp"



bool loadTextures()
{
    fog.setSmooth(true);
    city.setSmooth(true);
    water.setSmooth(true);
    land.setSmooth(true);
    return (fog.loadFromFile(resourcePath() +"fog.png")
            && city.loadFromFile(resourcePath() + "city.png")
            && water.loadFromFile(resourcePath() + "water.png")
            && land.loadFromFile(resourcePath() + "land.png"));
}
