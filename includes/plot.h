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
#include "polar.h"
using namespace std;

// by using the graphinfo, coord_translation, and rpn classes
// evaluate the value of the postfix expression
// convert the value to screen coordinates
// store the screen coordinates in a vector
//then  plot the graph

class Plot
    {
    public:
        Plot(GraphInfo* info);
        void set_info(GraphInfo* info);
        vector<vector<sf::Vector2f>> operator()(float xMin, float xMax, float increment);
        Queue<Token*> tokenize(const string& equation) const;

    private:
        GraphInfo* _info;
        ShuntingYard _shuntingYard;
        CoordTranslation _coordTranslation;

    };

#endif 