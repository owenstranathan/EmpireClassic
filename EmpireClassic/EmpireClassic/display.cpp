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
#include <iomanip>



bool loadTextures()
{
    fogTexture.setSmooth(true);
    city.setSmooth(true);
    water.setSmooth(true);
    land.setSmooth(true);
    transport.setSmooth(true);
    army.setSmooth(true);
    return (fogTexture.loadFromFile(resourcePath() +"fog.png")
            && city.loadFromFile(resourcePath() + "city.png")
            && water.loadFromFile(resourcePath() + "water.png")
            && land.loadFromFile(resourcePath() + "land.png")
            && transport.loadFromFile(resourcePath() + "transport.png"));
    //      && army.loadFromFile(resourcePath() + "army.png") !!not working right now for some reason!!
}

//load the textures of the map
void loadMapTextures()
{
    for(int i = 0; i < MAP_W; i++)
    {
        for(int j = 0; j < MAP_H; j++)
        {
            //real_map[i][j].sprite.setPosition(i*32, j*32);
            if(real_map[i][j].terrain == LAND)
            {
                real_map[i][j].sprite.setTexture(land);
                //real_map[i][j]->sprite.setColor(sf::Color((i+1)*9,(j+1)*9,0));
                
                //If the pieceList is not empty
                if(!real_map[i][j].pieceList.empty())
                {
                    for( Piece * piece : real_map[i][j].pieceList)
                    {
                        //Set the textures based on the type of the city
                        switch(getType(piece))
                        {
                            case CITY:
                                piece->sprite.setTexture(city);
                                //piece->sprite.setPosition(real_map[i][j].x*32,real_map[i][j].y*32);
                                break;
                        
                            case ARMY:
                                //NOTHING
                                break;
                            default:
                                break;
                            //Stuff for other types
                        }
                    }
                }
            }
            else if(real_map[i][j].terrain == WATER)
            {
                real_map[i][j].sprite.setTexture(water);
                //real_map[i][j]->sprite.setColor(sf::Color((i+1)*9,(j+1)*9,0));
                if(!real_map[i][j].pieceList.empty())
                {
                    for(Piece * piece : real_map[i][j].pieceList)
                    {
                        //Set the textures based on the type of the city
                        switch(getType(piece))
                        {
                            case TRANSPORT:
                                piece->sprite.setTexture(transport);
                                //piece->sprite.setPosition(real_map[i][j].x*32,real_map[i][j].y*32);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
}


//DRAWS THE REAL MAP AND THE FOG OF WAR WHERE APPROPRIATE
void drawMap(sf::RenderWindow & window)
{
    for(int i = 0; i < MAP_W; i++ )
    {
        for(int j = 0; j < MAP_H; j ++ )
        {
            // Draw the sprite
            real_map[i][j].draw(window);
            //if the tile's piece list is not emty
            if(!real_map[i][j].pieceList.empty())
            {
                //draw the last piece in the list
                real_map[i][j].pieceList.back()->draw(window);
            }
            //Draw the players vision
            if(!player_map[i][j])
            {
                //cover anything the player can't see with fog
                //fog.setPosition(i*32,j*32);
                //window.draw(fog);
            }
        }
    }
}


