//
// Created by Ryan on 5/5/2021.
//

#include <vector>

#ifndef TICTACTOE_MAT_H
#define TICTACTOE_MAT_H

using namespace std;

class Mat{
public:
    vector<double> multiply(vector<double> mat_1, vector<double> mat_2);
    vector<double> add(vector<double> mat_1, vector<double> mat_2);
    double sum(vector<double> mat);
};

#endif //TICTACTOE_MAT_H
