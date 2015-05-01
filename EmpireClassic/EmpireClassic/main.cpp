
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
#include "map.hpp"
#include "interface.hpp"


// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

//The actual map
Tile real_map[MAP_W][MAP_H];
//The players view map
bool player_map[MAP_W][MAP_H];

//declaring extenal global textures
sf::Texture fogTexture;
sf::Texture city;
sf::Texture water;
sf::Texture land;
sf::Texture transport;
sf::Texture army;

//Fog of War sprite
sf::Sprite fog;


int main(int, char const**)
{
    //load the textures from files and exit
    if(!loadTextures()) { return EXIT_FAILURE; }
    clearVision();
    readMap(resourcePath() + "map.txt");
    loadMapTextures();
    fog.setTexture(fogTexture);
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "EmpireClassic");

    //The mouse object
    sf::Mouse mouse;
    
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

            //WASD for piece movement
            //UP DOWN RIGHT LEFT for cursur
            //enter is to select piece when in cursur

            // Handle mouse click events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
            	Tile * t = getTileFromCursorPos(window);
            	if (t != NULL) {
            		std::string type = "";
            		switch(t->terrain) {
						case Terrain::LAND:
							type = "land";
							break;
						case Terrain::WATER:
							type = "water";
							break;
            		}
            		std::cout << "You clicked on a " << type << " tile." << std::endl;
            	}
            }
        }
        drawMap(window);



        // Draw the string
        //window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
