
//
//
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

#include "ResourcePath.hpp"

//The actual map
Tile real_map[MAP_W][MAP_H];
//The players view map
bool player_map[MAP_W][MAP_H];

int turn = 0;

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

World world(MAP_W * 32, MAP_H * 32);

int main(int, char const**)
{
    //load the textures from files and exit
    if(!loadTextures()) { return EXIT_FAILURE; }
    clearVision();
    readMap(resourcePath() + "map1.txt");
    loadMapTextures();
    fog.setTexture(fogTexture);
    
    // Create the main window
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "EmpireClassic");
    
    window.init("icon.png","concerningHobbits.ogg");
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "sansation.ttf");
    
    sf::Text test("This is sample text", font, 30);
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
                window.scroll(event.key.code);
                select.command(event.key.code);
                
            }
            
        }
        drawMap(world);
        select.draw(world);
        world.draw(window);
        window.draw(test);
        



        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
