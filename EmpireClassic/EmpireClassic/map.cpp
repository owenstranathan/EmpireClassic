
#include "map.hpp"
#include "empire.hpp"
#include <iostream>
#include <fstream>


//Read the saved map and bring it into memory from file
void readMap(std::string file)
{
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
                            real_map[column][row].pieceList.push_back(new City); 
                            break;
                        case 4:
                            //push army onto tile vector
                            //real_map[column][row].pieceList.push_back
                            break;
                    }
                }
                else
                {
                    //set the terrain type
                    real_map[column][row].terrain = WATER;
                    switch(type)
                    {
                        case 3:
                            real_map[column][row].pieceList.push_back(new Transport);
                            break;
                    }
                }
                //set the position of the tile
                real_map[column][row].x = row;
                real_map[column][row].y = column;
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
