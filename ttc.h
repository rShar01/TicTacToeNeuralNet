//
// Created by Ryan on 4/30/2021.
//
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
#include <vector>
#include "agent_v2.h"
#include "agent_v1.h"


#ifndef TICTACTOE_TTC_H
#define TICTACTOE_TTC_H

class ttc{
private:
    vector<vector<char>> board;
    bool turn;
    int curr_moves;

public:
    void init();
    void boardDisplay();
    void get_user();
    std::pair<int, int> get_coord();
    std::vector<std::pair<int,int>> get_valid_moves(char curr[3][3]);
    bool check_diag();
    bool check_hor();
    bool check_vert();
    bool play_game(agent_v1* p1, agent_v1* p2);
    void main_loop();
    bool train_loop(agent_v1* player_1, agent_v1* player_2);
    void play_against_bot(agent_v1* agent);
    bool play_game(agent_v2* p1, agent_v2* p2);
    bool train_loop(agent_v2* player_1, agent_v2* player_2);
    void play_against_bot(agent_v2* agent);
};

#endif //TICTACTOE_TTC_H
