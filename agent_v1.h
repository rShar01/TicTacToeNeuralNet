//
// Created by Ryan on 4/30/2021.
//
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>

#ifndef TICTACTOE_AGENT_H
#define TICTACTOE_AGENT_H
/*
 * A naive approach to reinforcement learning.
 * Flaws:
 *  - adjustment function could not produce meaningful change (perhaps pre-processing was the wrong idea)
 *  - swapping of weights occurred too often (volatile)
 *
 * Fix:
 *  - Less supervision
 *  - Less nodes
 *  - Q-learning ?
 *
 */
class agent_v1 {
private:
    double layer_1[3][3];
    char piece;     // true = x, false = o
    double layer_2[4];

public:
    double weight_1[3][3];
    double const_1[3][3];
    double weight_2[3][3];
    double const_2[3][3];
    double weight_out[4];
    double const_out[4];

    std::pair<int,int> make_move(char board[3][3]);
    void init(char start);
    void calc_weights(char curr[3][3]);
    void adjust_weights(agent_v1* winner, int moves);
    void set_piece(char piece);
};


#endif //TICTACTOE_AGENT_H
