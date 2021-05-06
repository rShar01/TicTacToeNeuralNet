//
// Created by Ryan on 5/4/2021.
//
#include <utility>
#include <random>
#include <math.h>
#include "agent_v2.h"
#include "Mat.h"


double random_num(float Min, float Max)
{
    return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}

double sigmoid(double x) {
    return 1/(1+exp(-x));
}

double ReLU(double x) {
    return (x > 0) ? x  : 0;
}

vector<double> calc_nodes(const vector<double>& board, vector<vector<double>> weights,  vector<double> bias) {
    vector<double> ret;
    Mat mat;
    for(int i = 0; i < weights.size(); i++) {
        vector<double> curr = mat.multiply(board, weights[i]);
        ret.push_back(sigmoid(mat.sum(curr) + bias[i]));
    }
}

double agent_v2::find_value(char board[3][3], pair<int,int> move) {
    char curr_board[3][3];
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            curr_board[i][j] = board[i][j];
        }
    }
    curr_board[move.first][move.second] = this->piece;
    vector<double> flat_board = this->flatten(curr_board);
    vector<double> layer_1 = calc_nodes(flat_board, this->val_net_weight_1, this->val_net_bias_1);
    vector<double> layer_2 = calc_nodes(layer_1, this->val_net_weight_2, this->val_net_bias_2);
    return matrix.sum(layer_2);
}

vector<double> agent_v2::flatten(char board[3][3]) const {
    vector<double> ret;
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == this->piece) {
                ret.push_back(1);
            } else if(board[i][j] == '*') {
                ret.push_back(0);
            } else {
                ret.push_back(-1);
            }
        }
    }
    return ret;
}

void agent_v2::init(char p) {
    this->piece = p;
    for(int i = 0; i < 5; i++) {
        vector<double> weights;
        for(int j = 0; j < 9; j++)
            weights.push_back(random_num(-1,1));

        this->val_net_weight_1.push_back(weights);
        this->val_net_bias_1.push_back(random_num(-5,5));
    }
    for(int i = 0; i < 2; i++) {
        vector<double> weights;

        for(int j = 0; j < 5; j++)
            weights.push_back(random_num(-1,1));

        this->val_net_weight_2.push_back(weights);
        this->val_net_bias_2.push_back(random_num(-5,5));
    }
}

pair<int, int> agent_v2::make_move(char board[3][3]) {
    pair<int,int> ret;
    vector<pair<int,int>> moves = board_ops.get_valid_moves(board);

    double max_val = 0;
    for(auto move:moves) {
        double curr = find_value(board, move);
        if(curr > max_val) {
            max_val = curr;
            ret = move;
        }
    }

    return ret;
}

void agent_v2::set_piece(char p) {
    this->piece = p;
}

