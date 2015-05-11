
#include "map.hpp"

#include <iostream>
#include <fstream>



///////////////////////////////////////////////////////////////////////////////
//TILE/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Tile::draw(sf::RenderTexture & world)
{
    sprite.setPosition(x*32, y*32);
    world.draw(sprite);
}


bool canRecieve(int x, int y, Map & map)
{
    if(isOnMap(x,y))
    {
        if(map.map[x][y].piece == NULL)
        {
            return true;
        }
    }
    return false;

}



///////////////////////////////////////////////////////////////////////////////
//MAP//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//Read the saved map and bring it into memory from file
Map::Map(std::string file)
{
    clearVision();
    //Set the city count to zero at the start of the game
    cityCount = 0;

    //Read the game dat in from a file
    std::ifstream infile (file.c_str());
    std::string line;
    int row = 0;
    if(infile.is_open())
    {
        while(std::getline(infile,line))
        {

            for(int column = 0; column < MAP_W; column++)
            {

                std::cout << line[column];
                int type = line[column]-'0';
                if(type)
                {
                    //set the terrain type
                    map[column][row].terrain = LAND;
                    map[column][row].sprite.setTexture(land);
                    switch(type)
                    {
                        case 2:
                            //push city onto tile vector
                            map[column][row].piece = new City(column, row, cityCount, NEUTRAL);
                            //increase the cityCount
                            ++cityCount;
                            break;
                        case 3:
                            map[column][row].terrain = WATER;
                            map[column][row].sprite.setTexture(water);
                            map[column][row].piece = new Transport(column, row, NEUTRAL);
                            break;
                        case 4:
                            map[column][row].piece = new Army(column, row, NEUTRAL);
                            //push army onto tile vector
                            break;
                        case 8:
                            map[column][row].piece = new Army(column, row, PLAYER);
                            updateVision(column, row);
                            break;
                        case 9:
                            map[column][row].piece = new City(column, row, cityCount, PLAYER);
                            updateVision(column, row);
                            break;
                    }
                }
                else
                {
                    //set the terrain type
                    map[column][row].terrain = WATER;
                    map[column][row].sprite.setTexture(water);
                }
                //set the position of the tile
                map[column][row].x = column;
                map[column][row].y = row;
            }
            std::cout << std::endl;
            row++;
        }
    }
    else
    {
        std::cout << "File failed to open" << std::endl;
    }

}


void Map::updateVision(int x, int y, int v )
{
    //for the total length of vision
    for( ; v >= 0; v--)
    {
        if(isOnMap(x, y-v)){ vision[x][y-v] = true; } // v blocks NORTH
        if(isOnMap(x+v,y-v)){ vision[x+v][y-v] = true; } // v blocks NORTHEAST
        if(isOnMap(x+v,y)){ vision[x+v][y] = true; } // v blocks BLOCKS EAST
        if(isOnMap(x+v,y+v)){ vision[x+v][y+v] = true; } // v blocks SOUTHEAST
        if(isOnMap(x,y+v)){ vision[x][y+v] = true; } // v blocks SOUTH
        if(isOnMap(x-v,y+v)){ vision[x-v][y+v] = true; } // v blocks SOUTHWEST
        if(isOnMap(x-v,y)){ vision[x-v][y] = true; } // v blocks WEST
        if(isOnMap(x-v,y-v)){ vision[x-v][y-v] = true; }// v blocks NORTHWEST
    }
}


void Map::clearVision()
{
    for(int i = 0; i < MAP_W; i++)
    {
        for(int j = 0 ; j<MAP_H; j++)
        {
            vision[i][j] = false;
        }
    }
}

//DRAWS THE REAL MAP AND THE FOG OF WAR WHERE APPROPRIATE
void Map::draw(sf::RenderTexture & world)
{
    for(int i = 0; i < MAP_W; i++ )
    {
        for(int j = 0; j < MAP_H; j ++ )
        {
            // Draw the sprite
            map[i][j].draw(world);
            //if the tile's piece list is not emty
            if(map[i][j].piece != NULL)
            {
                //draw the last piece in the list
                map[i][j].piece->draw(world);
            }
            //Draw the players vision
            if(!vision[i][j])
            {
                //cover anything the player can't see with fog
                fog.setPosition(i*32,j*32);
                world.draw(fog);
            }
        }
    }
}




bool isOnMap(int x, int y)
{
    if(x >= MAP_W || x < 0)
    {
        return false;
    }
    if(y >= MAP_H || y < 0)
    {
        return false;
    }
    return true;
}
