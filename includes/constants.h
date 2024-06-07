#ifndef CONSTANTS_H
#define CONSTANTS_H

const float SCREEN_WIDTH = 1400;
const float SCREEN_HEIGHT = 800;
const float WORK_PANEL = SCREEN_WIDTH * 4 / 5; // work panel is 1120 pixels wide
const float SIDE_BAR_WIDTH = SCREEN_WIDTH * 1 / 5;  // sidebar is 280 pixels wide


const int SB_MOUSE_POSITION = 0; //  sidebar mouse position
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1; //  sidebar mouse clicked
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1; //  sidebar key pressed
const float _minScale = 0.1f; // minimum scale
const float _maxScale = 10.0f; // maximum scale

// Default domain values
const sf::Vector2f DEFAULT_DOMAIN(-10.0f, 10.0f);
const float DEFAULT_SCALE = 60.0f; // default scale
const int DEFAULT_POINTS = 1000; // default number of points
const float DEFAULT_OFFSET_X = 0.0f; // default X-axis offset for panning
const float DEFAULT_OFFSET_Y = 0.0f; // default Y-axis offset for panning

// Sidebar default values
const float SIDE_BAR_LEFT = 1120.0f;

// Zoom and pan steps
const float ZOOM_STEP = 1.1f; // zoom factor
const float PAN_STEP = 2.0f; // pan step in pixels
#endif 
