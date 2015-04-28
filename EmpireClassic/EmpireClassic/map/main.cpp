#include <iostream>
#include "map.hpp"


using namespace std;
int real_map[MAP_W][MAP_H];
int player_map[MAp_W][MAP_H];


int main()
{
	cout << "The actual map" << endl;
	for(int i= 0 ; i < MAP_W; i++)
	{
	    for(int j = 0; j < MAP_H; j++)
		{
			cout << real_map[i][j];
		}
		cout << endl;
	}

	
    updateMap(2,2,1);	    


	cout << "The player map after the function updateMap(2,2,1) has been called" << endl;
	for(int i = 0; i < MAP_W; i++)
	{
		for(int j = 0; j < MAP_H; j++)
		{
			cout << player_map[i][j];
		}
		cout << endl;
	}
}
