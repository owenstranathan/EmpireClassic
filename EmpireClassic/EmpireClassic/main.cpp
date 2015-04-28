
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "empire.hpp"
#include "display.hpp"


// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

//The actual map
piece* real_map[MAP_W][MAP_H];
//The players view map
piece * player_map[MAP_W][MAP_H];

//declaring extenal global textures
sf::Texture fog;
sf::Texture city;
sf::Texture water;
sf::Texture land;

void makeMap()
{
    for (int i = 0; i < MAP_W; i++)
    {
        for (int j = 0; j < MAP_H; j++)
        {
            real_map[i][j] = new piece;
        }
    }
}

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
                real_map[row][column]->isLand = line[j] - '0';
                column++;
            }
            std::cout << std::endl;
            row++;
        }
    }
}


void loadMapTextures()
{
    for(int i = 0; i < MAP_W; i++)
    {
        for(int j = 0; j < MAP_H; j++)
        {
            real_map[i][j]->sprite.setPosition(i*32, j*32);
            if(real_map[i][j]->isLand)
            {
                real_map[i][j]->sprite.setTexture(land);
                //real_map[i][j]->sprite.setColor(sf::Color((i+1)*9,(j+1)*9,0));
            }
            else
            {
                real_map[i][j]->sprite.setTexture(water);
                //real_map[i][j]->sprite.setColor(sf::Color((i+1)*9,(j+1)*9,0));
            }
        }
    }
}

int main(int, char const**)
{
    //load the textures from files and exit
    if(!loadTextures()) { return EXIT_FAILURE; }
    makeMap();
    readMap(resourcePath() + "map.txt");
    loadMapTextures();
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "EmpireClassic");

    
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    


    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }



        for(int i = 0; i < MAP_W; i++ )
        {
            for(int j = 0; j < MAP_H; j ++ )
            {
                // Draw the sprite
                real_map[i][j]->draw(window);
                
            }
        }


        // Draw the string
        //window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
