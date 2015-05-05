
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
sf::Texture selection;

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
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "EmpireClassic");
    
    window.init("icon.png","concerningHobbits.ogg");

    Selection select;
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
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
            {
                select.tile = getTileFromCursorPos(window);
            }
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::P:
                        window.music.pause();
                        break;
                        
                    case sf::Keyboard::O:
                        window.music.play();

                    default:
                        break;
                        
                }
                select.command(event.key.code);
                
            }
            
        }
        drawMap(window);
        select.draw(window);


        // Draw the string
        //window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
