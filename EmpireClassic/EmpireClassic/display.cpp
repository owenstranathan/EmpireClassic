//
//  display.cpp
//  EmpireClassic
//
//  Created by Owen Stranathan on 4/28/15.
//  Copyright (c) 2015 Owen Stranathan. All rights reserved.
//

#include "display.hpp"
#include "map.hpp"
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

//load the textures of the map
void loadMapTextures()
{
    for(int i = 0; i < MAP_W; i++)
    {
        for(int j = 0; j < MAP_H; j++)
        {
            real_map[i][j].sprite.setPosition(i*32, j*32);
            if(real_map[i][j].terrain == LAND)
            {
                real_map[i][j].sprite.setTexture(land);
                //real_map[i][j]->sprite.setColor(sf::Color((i+1)*9,(j+1)*9,0));
            }
            else if(real_map[i][j].terrain == WATER)
            {
                real_map[i][j].sprite.setTexture(water);
                //real_map[i][j]->sprite.setColor(sf::Color((i+1)*9,(j+1)*9,0));
            }
        }
    }
}
