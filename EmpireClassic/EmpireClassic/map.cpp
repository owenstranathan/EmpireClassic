
#include "map.hpp"
#include "empire.hpp"
#include <iostream>
#include <fstream>

int cityCount;


//Read the saved map and bring it into memory from file
void readMap(std::string file)
{
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
            for(int column = 0; column < line.length(); column++)
            {
                std::cout << line[column];
                int type = line[column]-'0';
                if(type)
                {
                    //set the terrain type
                    real_map[column][row].terrain = LAND;
                    switch(type)
                    {
                        case 2:
                            //push city onto tile vector
                            real_map[column][row].piece = new City(column, row, cityCount);
                            //increase the cityCount
                            ++cityCount;
                            break;
                        case 3:
                            real_map[column][row].terrain = WATER;
                            real_map[column][row].piece = new Transport(column, row);
                            updateVision(column, row, 1);
                            break;
                        case 4:
                            real_map[column][row].piece = new Army(column, row);
                            //push army onto tile vector
                            updateVision(column, row, 1);
                            break;
                    }
                }
                else
                {
                    //set the terrain type
                    real_map[column][row].terrain = WATER;

                }
                //set the position of the tile
                real_map[column][row].x = column;
                real_map[column][row].y = row;
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





void updateVision(int x, int y, int v )
{
    //for the total length of vision
    for( ; v >= 0; v--)
    {
        if(isOnMap(x, y-v)){ player_map[x][y-v] = true; } // v blocks NORTH
        if(isOnMap(x+v,y-v)){ player_map[x+v][y-v] = true; } // v blocks NORTHEAST
        if(isOnMap(x+v,y)){ player_map[x+v][y] = true; } // v blocks BLOCKS EAST
        if(isOnMap(x+v,y+v)){ player_map[x+v][y+v] = true; } // v blocks SOUTHEAST
        if(isOnMap(x,y+v)){ player_map[x][y+v] = true; } // v blocks SOUTH
        if(isOnMap(x-v,y+v)){ player_map[x-v][y+v] = true; } // v blocks SOUTHWEST
        if(isOnMap(x-v,y)){ player_map[x-v][y] = true; } // v blocks WEST
        if(isOnMap(x-v,y-v)){ player_map[x-v][y-v] = true; }// v blocks NORTHWEST
    }
}

void clearVision()
{
    for(int i = 0; i < MAP_W; i++)
    {
        for(int j = 0 ; j<MAP_H; j++)
        {
            player_map[i][j] = false;
        }
    }
}

//OLD UPDTE MAP FUNCTION
//NO LONGER VALID
/*

void updateMap(int r, int c, int a)
{
    //for columns
    for(int i = 1; i <= a; i++) 
    //for rows
        for(int j = 1; j <= a; j++) 
        {
	    //check left
	    if((c - i) >= 0) 
	    {
	        player_map[c - i][r] = real_map[c-i][r];
		//check up
		if((r + j) >= 0) 
		{
		    for(int k = 1; k <= j; k++) 
		    {
                player_map[c-i][r+k] = real_map[c-i][r+k];
		    }
		}
		//check down
		if((r - j) < MAP_H) 
		{
		    for(int k = 1; k <= j; k++) 
		    {
			player_map[c-i][r-k] = real_map[c-i][r-k];
            }
		}
	    }
	    //check right
	    if((c + i) < MAP_W) 
	    {
	        player_map[c+i][r] = real_map[c+i][r];
	        //check up
		if((r+j) >= 0) 
		{
		    for(int k = 1; k <= j; k++) 
		    {
			player_map[c+i][r+k] = real_map[c+i][r+k];
		    }
		}
		//check down
		if((r-j) < MAP_H) 
		{
		    for(int k = 1; k <= j; k++) 
		    {
		        player_map[c+i][r+k] = real_map[c+i][r+k];
		    }
		}
	    }
	    //check directly up
	    if((r+j) >= 0) 
	    {
		player_map[c][r+j] = real_map[c][r+j];
	    }
	    //check directly down
	    if((r-j) < MAP_H) 
	    {
		player_map[c][r-j] = real_map[c][r-j];
	    }
	
    }
}*/
