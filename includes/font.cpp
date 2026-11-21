#include "font.h"
#include <iostream>

#ifndef FONT_PATH
#define FONT_PATH "assets/fonts/DejaVuSans.ttf"
#endif

const sf::Font& app_font()
    {
    static sf::Font font;
    static bool loaded = false;
    if (!loaded)
        {
        loaded = font.loadFromFile(FONT_PATH) ||
                 font.loadFromFile("assets/fonts/DejaVuSans.ttf");
        if (!loaded)
            {
            std::cerr << "Error: could not load font from " << FONT_PATH << std::endl;
            loaded = true;  // report once, then draw without text
            }
        }
    return font;
    }
