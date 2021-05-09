//
// Created by Ryan on 5/4/2021.
//

#include <vector>
#include "Mat.h"

#ifndef TICTACTOE_AGENT_V2_H
#define TICTACTOE_AGENT_V2_H

/*
 * Q-learning approach
 */
using namespace std;

class agent_v2{
private:
    // Instance variables, mat for matrix operations, piece for which side you are on
    Mat matrix;
    char piece;
    // weights and biases of each node in the value network
    vector<vector<double>> val_net_weight_1;
    vector<double> val_net_bias_1;
    vector<vector<double>> val_net_weight_2;
    vector<double> val_net_bias_2;
    // last_most keeps track of the neurons of the last calc_value
    double last_most[2][5];


    // turns the board from a 3x3 matrix to a 1x9 matrix for value net
    vector<double> flatten(char board[3][3]) const;

    // gets the predicted probability of a win in the current position with the given move
    double find_value(char board[3][3], pair<int,int> move);

    // does the weight and bias calculations at a given layer
    vector<double>
    calc_nodes(int layer, const vector<double> &board, vector<vector<double>> weights, vector<double> bias);

public:
    // initializes the agent
    void init(char piece);

    // chooses and makes "best" move
    pair<int,int> make_move(char board[3][3]);

    // if needed to change the agent's current piece (do not adjust during games)
    void set_piece(char p);

    // adjusts weights based on true outcome, uses RMSE as loss function
    void adjust_weights(double outcome);


};

#endif //TICTACTOE_AGENT_V2_H
