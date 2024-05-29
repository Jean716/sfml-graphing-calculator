#include "animate.h"
#include "constants.h"
#include "system.h"

// User interaction

animate::animate()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graph Plotter"),
    system([] (float x) { return x; }),
    sidebar(WORK_PANEL, SIDE_BAR),
    mousePoint(5), // Set radius for the little red dot
    mouseIn(false)
    {

    // Initialize mousePoint (red dot)
    mousePoint.setFillColor(sf::Color::Red);

    // Load font
    if (!font.loadFromFile("Roboto-Thin.ttf"))
        {
        std::cout << "animate() CTOR: Font failed to load" << std::endl;
        std::cin.get();
        }

    // Initialize text label
    myTextLabel.setFont(font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::White);
    myTextLabel.setPosition(10, 10);
    myTextLabel.setString("Welcome to Graph Plotter!");

    cout << "animate instantiated successfully." << endl;

    }


void animate::processEvents()
    {
    sf::Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event))//or waitEvent
        {
        // check the type of the event...
        switch (event.type)
            {
            // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                    // key pressed
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                        {
                            case sf::Keyboard::Left:
                                sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                                command = 4;
                                break;
                            case sf::Keyboard::Right:
                                sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                                command = 6;
                                break;
                            case sf::Keyboard::Escape:
                                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                                window.close();
                                break;
                        }

                    break;
                case sf::Event::MouseEntered:
                    mouseIn = true;
                    break;

                case sf::Event::MouseLeft:
                    mouseIn = false;
                    break;

                case sf::Event::MouseMoved:
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;

                    //Do something with it if you need to...
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Right)
                        {
                        sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                            mouse_pos_string(window);

                        }
                    else
                        {
                        sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                            mouse_pos_string(window);
                        }
                    break;

                default:
                    break;
            }
        }
    }

void animate::update()
    {
    system.update();
    }

void animate::render()
    {
    window.clear(sf::Color::Black); // set background to black
    system.draw(window);
    if (mouseIn)
        {
        window.draw(mousePoint); // draw the little red dot
        }
    window.draw(myTextLabel); // draw the text label
    sidebar.draw(window); // draw the sidebar
    window.display();
    }

void animate::Draw()
    {
    // This function can be used to draw additional elements if needed
    }


void animate::run()
    {
    while (window.isOpen())
        {
        processEvents();
        update();
        render(); //clear/draw/display
        }
    }


string mouse_pos_string(sf::RenderWindow& window)
    {
    return "(" +
        to_string(sf::Mouse::getPosition(window).x) +
        ", " +
        to_string(sf::Mouse::getPosition(window).y) +
        ")";
    }
