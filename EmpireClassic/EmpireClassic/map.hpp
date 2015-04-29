#ifdef MAP_HPP
#define MAP_HPP

#include <iostream>

const int MAP_W = 4;
const int MAP_H = 4;


//The real map that holds all the in game objects
extern int real_map[MAP_W][MAP_H] = {{1,1,1,1}, 
			    				      {0,0,0,0},
							  {1,1,1,1},
							  {1,1,1,1}};

//The players view of the map that simply dictates what is and is not visible by the player.
extern int player_map[MAP_W][MAP_H] = {
									   {0,0,0,0},
									   {0,0,0,0},
									   {0,0,0,0},
									   {0,0,0,0}
									  };


void updateMap(int c, int r, int a = 1);

#endif /* defined(MAP_HPP) */


