#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "empire.hpp"


//global HEIGHT and WIDTH variables
const int MAP_W = 30;
const int MAP_H = 20;


//The real map that hold all the in game objects
extern Tile real_map[MAP_W][MAP_H];
//the players view map that simply dictates what is and is not visible by the player.
extern bool player_map[MAP_W][MAP_H];

//function to read predefined maps from text files
void readMap(std::string);

//function to update the player_map based on player location
void updateVision(int , int, int v = 1);

//function to check if a location is part of the map
bool isOnMap(int, int);

//for clearing the vision of the map
void clearVision();

#endif /* defined(MAP_HPP) */


