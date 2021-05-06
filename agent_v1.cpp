//
// Created by Ryan on 4/30/2021.
//
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
#include <random>
#include <math.h>
#include "agent_v1.h"

const double MAX = 1;
const double MIN = -1;

double random_num(float Min, float Max)
{
    return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}

void agent_v1::init(char start) {
    this->piece = start;
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
//            std::cout << random_num(-1,1) << std::endl;
//            agent_v1::weight_1[i][j] = (double) rand() / (double) (RAND_MAX / (MAX - MIN));
//            agent_v1::weight_2[i][j] = (double) rand() / (double) (RAND_MAX / (MAX - MIN));
//            agent_v1::const_1[i][j] = (double) rand() / (double) (RAND_MAX / (MAX - MIN));
//            agent_v1::const_2[i][j] = (double) rand() / (double) (RAND_MAX / (MAX - MIN));
            this->weight_1[i][j] = random_num(-1,1);
            this->weight_2[i][j] = random_num(-1,1);
            this->const_1[i][j] = random_num(-0.5,0.5);
            this->const_2[i][j] = random_num(-0.5, 0.5);
        }
    }
    for(int i = 0; i < 4; i++) {
//        std::cout << random_num(-0.5,0.5) << std::endl;
//        agent_v1::weight_out[i] = (double) rand() / (double) (RAND_MAX / (MAX - MIN));
//        agent_v1::const_out[i] = (double) rand() / (double) (RAND_MAX / (MAX - MIN));
        this->weight_out[i] = random_num(-1,1);
        this->const_out[i] = random_num(-0.5,0.5);
    }
}

std::pair<int,int> agent_v1::make_move(char board[3][3]) {
    this->calc_weights(board);
    std::vector<std::pair<int,int>> moves;

    int row_move = (int)(weight_out[0]*layer_2[0] + const_out[0] + weight_out[3]*layer_2[3] + const_out[3]);
    int col_move = (int)(weight_out[1]*layer_2[1] + const_out[1] + weight_out[2]*layer_2[2] + const_out[2]);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == '*')
                moves.emplace_back(i,j);
        }
    }

    int min_dist = 13000000;
    std::pair<int,int> move;

    for(auto curr : moves) {
        int distance = (int)sqrt(pow(curr.first - row_move,2) + pow(curr.second - col_move,2));
        if(distance < min_dist) {
            min_dist = distance;
            move = curr;
        }
    }
    return move;
}

void agent_v1::calc_weights(char curr[3][3]) {
    int board[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(curr[i][j] == '*') {
                board[i][j] = 0;
            } else if(curr[i][j] == piece) {
                board[i][j] = 1;
            }
            else {
                board[i][j] = -1;
            }
        }
    }
    layer_1[0][0] = (double)(weight_1[0][0] * board[0][0] + const_1[0][0] + weight_1[0][1] * board[0][1] + const_1[0][1] + weight_1[0][2] * board[0][2] + const_1[0][2] + weight_1[1][0] * board[1][0] + const_1[1][0] + weight_1[2][0] * board[2][0] + const_1[2][0]);
    layer_1[0][1] = (double)(weight_1[0][0] * board[0][0] + const_1[0][0] + weight_1[0][1] * board[0][1] + const_1[0][1] + weight_1[0][2] * board[0][2] + const_1[0][2] + weight_1[1][1] * board[1][1] + const_1[1][1] + weight_1[2][1] * board[2][1] + const_1[2][1]);
    layer_1[0][2] = (double)(weight_1[0][0] * board[0][0] + const_1[0][0] + weight_1[0][1] * board[0][1] + const_1[0][1] + weight_1[0][2] * board[0][2] + const_1[0][2] + weight_1[1][2] * board[1][2] + const_1[1][2] + weight_1[2][2] * board[2][2] + const_1[2][2]);
    layer_1[1][0] = (double)(weight_1[0][0] * board[0][0] + const_1[0][0] + weight_1[1][0] * board[1][0] + const_1[1][0] + weight_1[2][0] * board[2][0] + const_1[2][0] + weight_1[1][1] * board[1][1] + const_1[1][1] + weight_1[1][2] * board[1][2] + const_1[1][2]);
    layer_1[1][1] = (double)(weight_1[0][1] * board[0][1] + const_1[0][1] + weight_1[1][1] * board[1][1] + const_1[1][1] + weight_1[2][1] * board[2][1] + const_1[2][1] + weight_1[1][0] * board[1][0] + const_1[1][0] + weight_1[1][2] * board[1][2] + const_1[1][2]);
    layer_1[1][2] = (double)(weight_1[0][2] * board[0][2] + const_1[0][2] + weight_1[1][2] * board[1][2] + const_1[1][2] + weight_1[2][2] * board[2][2] + const_1[2][2] + weight_1[1][0] * board[1][0] + const_1[1][0] + weight_1[1][1] * board[1][1] + const_1[1][1]);
    layer_1[2][0] = (double)(weight_1[2][0] * board[2][0] + const_1[2][0] + weight_1[2][1] * board[2][1] + const_1[2][1] + weight_1[2][2] * board[2][2] + const_1[2][2] + weight_1[1][0] * board[1][0] + const_1[1][0] + weight_1[0][0] * board[0][0] + const_1[0][0]);
    layer_1[2][1] = (double)(weight_1[2][0] * board[2][0] + const_1[2][0] + weight_1[2][1] * board[2][1] + const_1[2][1] + weight_1[2][2] * board[2][2] + const_1[2][2] + weight_1[1][1] * board[1][1] + const_1[1][1] + weight_1[0][1] * board[0][1] + const_1[0][1]);
    layer_1[2][2] = (double)(weight_1[2][0] * board[2][0] + const_1[2][0] + weight_1[2][1] * board[2][1] + const_1[2][1] + weight_1[2][2] * board[2][2] + const_1[2][2] + weight_1[1][2] * board[1][2] + const_1[1][2] + weight_1[0][2] * board[0][2] + const_1[0][2]);

    layer_2[0] = (double)(weight_2[0][0]*layer_1[0][0] + const_2[0][0] + weight_2[0][1]*layer_1[0][1] + const_2[0][1] + weight_2[1][0]*layer_1[1][0] + const_2[1][0] + weight_2[1][1]*layer_1[1][1] + const_2[1][1]);
    layer_2[1] = (double)(weight_2[0][1]*layer_1[0][1] + const_2[0][1] + weight_2[0][2]*layer_1[0][2] + const_2[0][2] + weight_2[1][1]*layer_1[1][1] + const_2[1][1] + weight_2[1][2]*layer_1[1][2] + const_2[1][2]);
    layer_2[2] = (double)(weight_2[1][0]*layer_1[1][0] + const_2[1][0] + weight_2[1][1]*layer_1[1][1] + const_2[1][1] + weight_2[2][0]*layer_1[2][0] + const_2[2][0] + weight_2[2][1]*layer_1[2][1] + const_2[2][1]);
    layer_2[3] = (double)(weight_2[1][1]*layer_1[1][1] + const_2[1][1] + weight_2[1][2]*layer_1[1][2] + const_2[1][2] + weight_2[2][1]*layer_1[2][1] + const_2[2][1] + weight_2[2][2]*layer_1[2][2] + const_2[2][2]);

    std::cout << "Agent: " << piece << std::endl;
    std::cout << layer_1[0][0] << " " << layer_1[0][1] << " " << layer_1[0][2] << std::endl;
    std::cout << layer_1[1][0] << " " << layer_1[1][1] << " " << layer_1[1][2] << std::endl;
    std::cout << layer_1[2][0] << " " << layer_1[2][1] << " " << layer_1[2][2] << std::endl;
}

void agent_v1::adjust_weights(agent_v1 *winner, int moves) {
    double superiority = ((double)(9-moves)/9) + 1;
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; ++j) {
            double diff_w1 = winner->weight_1[i][j] - this->weight_1[i][j];
            this->weight_1[i][j] = this->weight_1[i][j] + diff_w1*superiority;
            double diff_c1 = winner->const_1[i][j] - this->const_1[i][j];
            this->const_1[i][j] = this->const_1[i][j] + diff_c1*superiority/2;
//            std::cout << diff_w1 << " + " << diff_c1 << std::endl;

            double diff_w2 = winner->weight_2[i][j] - this->weight_2[i][j];
            this->weight_2[i][j] = this->weight_2[i][j] + diff_w2*superiority;
            double diff_c2 = winner->const_2[i][j] - this->const_2[i][j];
            this->const_2[i][j] = this->const_2[i][j] + diff_c2*superiority/2;
//            std::cout << diff_w2 << " + " << diff_c2 << std::endl;
        }
    }

    for(int i = 0; i < 4; i++) {
        double diff_w = winner->weight_out[i] - this->weight_out[i];
        this->weight_out[i] += diff_w*superiority/4;
        double diff_c = winner->const_out[i] - this->const_out[i];
        this->const_out[i] += diff_c*superiority/4;
//        std::cout << diff_w << " + " << diff_c << std::endl;
    }
}

void agent_v1::set_piece(char piece) {
    this->piece = piece;
}



