#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../includes/shunting_yard/shunting_yard.h"
#include "../includes/token/tk_string.h"

#include "../includes/rpn/rpn.h"
#include "graphInfo.h"
#include "coord_translation.h"

using namespace std;

// by using the graphinfo, coord_translation, shuntingYard and rpn classes
// evaluate the value of the postfix expression
// convert the value to screen coordinates
// store the screen coordinates in a vector
//then  plot the graph

class Plot
    {
    public:
        Plot(GraphInfo* info); // constructor
        void set_info(GraphInfo* info); // set the information of the graph
        vector<vector<sf::Vector2f>> operator()(float xMin, float xMax, float increment); // operator overloading
        Queue<Token*> tokenize(const string& equation) const; // tokenize the equation
        vector<vector<sf::Vector2f>> calculateC(float xMin, float xMax, float increment); // calculate the cartesian coordinates
        vector<vector<sf::Vector2f>> calculateP(float thetaMin, float thetaMax, float increment); // calculate the polar coordinates


    private:
        GraphInfo* _info; // graph information
        ShuntingYard _shuntingYard; // shunting yard object
        CoordTranslation _coordTranslation; // coordinate translation object

    };

#endif 