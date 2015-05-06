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
    selection.setSmooth(true);
    return (fogTexture.loadFromFile(resourcePath() +"fog.png")
            && city.loadFromFile(resourcePath() + "city.png")
            && water.loadFromFile(resourcePath() + "water.png")
            && land.loadFromFile(resourcePath() + "land.png")
            && transport.loadFromFile(resourcePath() + "transport.png")
            && army.loadFromFile(resourcePath() + "army.png")
            && selection.loadFromFile(resourcePath() + "selection.png"));
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
                if(real_map[i][j].piece != NULL)
                {
                 
                    //Set the textures based on the type of the city
                    switch(getType(real_map[i][j].piece))
                    {
                        case CITY:
                            real_map[i][j].piece->sprite.setTexture(city);
                            //piece->sprite.setPosition(real_map[i][j].x*32,real_map[i][j].y*32);
                            break;
                        
                        case ARMY:
                            real_map[i][j].piece->sprite.setTexture(army);
                            break;
                        default:
                            break;
                        //Stuff for other types
                    }

                }
            }
            else if(real_map[i][j].terrain == WATER)
            {
                real_map[i][j].sprite.setTexture(water);
                //real_map[i][j]->sprite.setColor(sf::Color((i+1)*9,(j+1)*9,0));
                if(real_map[i][j].piece != NULL)
                {

                    //Set the textures based on the type of the city
                    switch(getType(real_map[i][j].piece))
                    {
                        case TRANSPORT:
                            real_map[i][j].piece->sprite.setTexture(transport);
                            //piece->sprite.setPosition(real_map[i][j].x*32,real_map[i][j].y*32);
                            break;
                        case ARMY:
                            real_map[i][j].piece->sprite.setTexture(army);
                            break;
                        default:
                            break;
                        
                    }
                }
            }
        }
    }
}


//DRAWS THE REAL MAP AND THE FOG OF WAR WHERE APPROPRIATE
void drawMap(sf::RenderTexture & world)
{
    for(int i = 0; i < MAP_W; i++ )
    {
        for(int j = 0; j < MAP_H; j ++ )
        {
            // Draw the sprite
            real_map[i][j].draw(world);
            //if the tile's piece list is not emty
            if(real_map[i][j].piece != NULL)
            {
                //draw the last piece in the list
                real_map[i][j].piece->draw(world);
            }
            //Draw the players vision
            if(!player_map[i][j])
            {
                //cover anything the player can't see with fog
                fog.setPosition(i*32,j*32);
                world.draw(fog);
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////
//WINDOW////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Window::Window(int width, int height, const char * title)
:
sf::RenderWindow(sf::VideoMode(960, 640), title), view(sf::FloatRect(0,0, 960, 640))
{
}

void Window::init(const char * iconFile, char const * musicFile)
{
    

    icon.loadFromFile(resourcePath() + iconFile);
    //Set the windows icon to the loaded Icon image
    setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //open and play the music
    music.openFromFile(resourcePath() + musicFile);
    music.play();
    
    //cap the frame rate limit
    setFramerateLimit(60);
    
    //Set the view port
    view.setCenter((MAP_W/2)*32, (MAP_H/2)*32);
    
    setView(view);
}

//Because views are positioned by their center, I have to do funky math
void Window::scroll(sf::Keyboard::Key code)
{
    //get the current position of the view
    sf::Vector2f viewPos = view.getCenter();
    //get the size of the viewport
    sf::Vector2f viewSize = view.getSize();
    
    switch(code)
    {
        //Move the view around
        case sf::Keyboard::Up:  //Move up
            //consider x's at the top of the screen,
            //we want to keep from pushing any part of the view off the world
            //subtract half the screen to the x and y positions in the center of the screen
            //we subtract because screen coords start with 0-y at the top
            viewPos.y -= viewSize.y/2;
            if(isOnMap((viewPos.x)/32, (viewPos.y-32)/32))
            {
                view.move(0, -32);
                setView(view);
            }
            break;
        case sf::Keyboard::Right:   //Move right
            viewPos.x += viewSize.x/2;
            if(isOnMap((viewPos.x+32)/32, (viewPos.y)/32))
            {
                view.move(32, 0);
                setView(view);
            }
            break;
        case sf::Keyboard::Down:    //Move down
            viewPos.y += viewSize.y/2;
            if(isOnMap((viewPos.x)/32, (viewPos.y+32)/32))
            {
                view.move(0, 32);
                setView(view);
            }
            break;
        case sf::Keyboard::Left:    //move left
            viewPos.x -= viewSize.x/2;
            if(isOnMap((viewPos.x-32)/32, (viewPos.y)/32))
            {
                view.move(-32, 0);
                setView(view);
            }
            break;
        default:
            break;

    }
}


