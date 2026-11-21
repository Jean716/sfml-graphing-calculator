#ifndef FONT_H
#define FONT_H
#include <SFML/Graphics.hpp>

// Shared UI font, loaded once on first use.
// The path is set by CMake (FONT_PATH); if that file is missing, the
// font is looked up at assets/fonts/DejaVuSans.ttf relative to the
// working directory.
const sf::Font& app_font();

#endif
