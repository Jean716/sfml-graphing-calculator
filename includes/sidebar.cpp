#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar() : _left(1120), _width(280)
    {
    _rect.setSize(sf::Vector2f(_width, 800));
    _rect.setFillColor(sf::Color(100, 100, 100));
    _rect.setPosition(_left, 0);
    if (!_font.loadFromFile("arial.ttf"))
        {
        // Handle error
        }
    _sb_text.setFont(_font);
    _sb_text.setFillColor(sf::Color::White);
    }


Sidebar::Sidebar(float left, float width) :_left(left), _width(width)
    {
    cout << "Sidebar CTOR: TOP" << endl;
    _items.reserve(50); //reserve space for 50 strings

    //set up the sidebar rectangle:
    _rect.setFillColor(sf::Color(131, 175, 155)); //green
    _rect.setPosition(sf::Vector2f(left, 0));
    _rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    //setBackgroundColor(sf::Color(131, 175, 155));

    cout << "Sidebar CTOR:  load font." << endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the font file must be in the "working directory"
    // check projects->run->working directory
    //      [Make sure it's not pointing to the app file]

    if (!_font.loadFromFile("Roboto-Thin.ttf"))
        {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
        }

    cout << "Sidebar CTOR: Set the text of the sidebar" << endl;
    _sb_text.setFont(_font);
    _sb_text.setCharacterSize(20);
    _sb_text.setStyle(sf::Text::Bold);
    _sb_text.setColor(sf::Color::Black);

    // position text on screen:
    //_sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - _sb_text.getLocalBounds().height - 5));

    // add some text to the sidebar:
    _items.push_back("Please Enter a Function.");
    //_items.push_back("add some text here");

    // set up the input box:
    _inputBox.setSize(sf::Vector2f(_width - 20, 30));
    _inputBox.setFillColor(sf::Color::White);
    _inputBox.setPosition(_left + 10, 50);

    _inputText.setFont(_font);
    _inputText.setFillColor(sf::Color::Black);
    _inputText.setCharacterSize(20);
    _inputText.setPosition(_left + 15, 55);



    //Fill the items vector with empty strings so that we can use [] to read them:
    for (int i = 0; i < 30; i++)
        {
        _items.push_back("");
        }
    cout << "Sidebar: CTOR: Exit." << endl;
    }

void Sidebar::draw(sf::RenderWindow& window)
    {
    const float VERTICAL_LINE_SPACING = 5.0;//  5 pixels between lines
    const float LEFT_MARGIN = 10.0;  //  10 pixels from left edge

    window.draw(_rect); //draw the rectangle of the sidebar
    float height = 10; //start 10 pixels from the top

    for (const auto& item : _items)
        {
        if (item.empty())
            {
            continue; // skip empty strings
            }
        _sb_text.setString(item); // set the text
        _sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height)); // set the position
        height += _sb_text.getLocalBounds().height + VERTICAL_LINE_SPACING; // update the height
        window.draw(_sb_text); // draw the text

        // drwa the input box and text
        window.draw(_inputBox);
        window.draw(_inputText);
        }
    }

string& Sidebar::operator [](int index)
    {
    return _items[index];
    }


void Sidebar::handleEvent(const sf::Event& event)
    {
    if (event.type == sf::Event::TextEntered)
        {
        if (event.text.unicode == '\b')
            { // handle backspace
            if (!_inputString.empty())
                {
                _inputString.pop_back();
                }
            }
        else if (event.text.unicode < 128)
            { // handle ASCII characters only
            _inputString += static_cast<char>(event.text.unicode);
            }
        _inputText.setString(_inputString);
        }
    }


string Sidebar::getInput() const
    {
    return _inputString;
    }