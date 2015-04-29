#include "map.hpp"
#include <iostream>
using namespace std;






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
}
