//
// Created by Ryan on 5/4/2021.
//

#include <vector>

#ifndef TICTACTOE_AGENT_V2_H
#define TICTACTOE_AGENT_V2_H
#include "Mat.h"
#include "ttc.h"
/*
 * Q-learning approach
 */
using namespace std;

class agent_v2 {
private:
    Mat matrix;
    ttc board_ops;
    char piece;
    vector<vector<double>> val_net_weight_1;
    vector<double> val_net_bias_1;
    vector<vector<double>> val_net_weight_2;
    vector<double> val_net_bias_2;
    vector<double> flatten(char board[3][3]) const;
    double find_value(char board[3][3], pair<int,int> move);

public:
    void init(char piece);
    pair<int,int> make_move(char board[3][3]);
    void set_piece(char p);
};

#endif //TICTACTOE_AGENT_V2_H
