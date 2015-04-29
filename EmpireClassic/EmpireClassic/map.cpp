
#include "map.hpp"
#include "empire.hpp"
#include <iostream>
#include <fstream>



void readMap(std::string file)
{
    std::ifstream infile (file.c_str());
    std::string line;
    int row = 0;
    if(infile.is_open())
    {
        
        while(std::getline(infile,line))
        {
            int column = 0;
            for(int j = 0; j < line.length(); j ++)
            {
                std::cout << line[j];
                if(line[j]-'0')
                {
                    //set the terrain type
                    real_map[column][row].terrain = LAND;
                                    }
                else
                {
                    //set the terrain type
                    real_map[row][column].terrain = WATER;
                }
                //set the position of the tile
                real_map[column][row].x = row;
                real_map[column][row].y = column;
                column++;
            }
            std::cout << std::endl;
            row++;
        }
    }
}


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
}
