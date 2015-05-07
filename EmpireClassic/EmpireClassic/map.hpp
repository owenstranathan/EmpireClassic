#ifndef MAP_HPP
#define MAP_HPP


#include "empire.hpp"
#include "display.hpp"
#include "interface.hpp"



//global HEIGHT and WIDTH variables
const int MAP_W = 50;
const int MAP_H = 40;

struct Piece;
struct Map;


////////////////////////////////////////////////////////////////////////////////////////
//TILE//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
enum Terrain
{
    WATER,
    LAND
};

struct Tile
{
    //Sprite of the tile
    sf::Sprite sprite;

    //The type of terrain the tile is
    Terrain terrain;

    //The piece located on the terrain
    Piece * piece;

    //position of the tile
    int x, y;

    Tile() : piece(NULL)
    {}

    //draws the piece at it's location
    void draw(sf::RenderTexture &);
};




//determines whether a tile has a piece or not
bool canRecieve(int, int, Map &map);


////////////////////////////////////////////////////////////////////////////////////////
//MAP///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

struct Map
{
    Tile map[MAP_W][MAP_H];
    bool vision[MAP_W][MAP_H];

    int cityCount;


    //read predefined maps from text files and set the map member accordingly
    Map(std::string);

    //function to update the player_map based on player location
    void updateVision(int , int, int v = 1);


    //for clearing the vision of the map
    void clearVision();

    void draw(sf::RenderTexture&);
};

//function to check if a location is part of the map
bool isOnMap(int, int);


#endif /* defined(MAP_HPP) */
