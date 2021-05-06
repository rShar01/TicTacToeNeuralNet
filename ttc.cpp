//
// Created by Ryan on 4/30/2021.
//
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
#include <stdio.h>

using namespace std;

#include "ttc.h"
void ttc::init() {
    turn = false;
    curr_moves = 0;
    //board = new char*[3];
    for(int i = 0; i < 3; i++) {
        //board[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            board[i][j] = '*';
        }
    }
}
void ttc::boardDisplay() {
    cout << "---current board---" << endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

std::pair<int,int> ttc::get_coord() {
    pair<int,int> ret;
    do {
        cout << "Enter the row number of your next move [0,2]: " << endl;
        cin >> ret.first;
    } while(ret.first > 2 || ret.first < 0);
    do {
        cout << "Enter the column number of your next move [0,2]: " << endl;
        cin >> ret.second;
    }while(ret.second > 2 || ret.second < 0);
    return ret;
}
void ttc::get_user() {
    if(turn)
        cout << "x's turn! ";
    else
        cout << "o's turn! ";

    pair<int,int> move = ttc::get_coord();
    while(board[move.first][move.second] != '*') {
        cout << "Invalid! Already occupied!" << endl;
        move = get_coord();
    }

    if(turn)
        board[move.first][move.second] = 'x';
    else
        board[move.first][move.second] = 'O';

    turn = !turn;
}

bool ttc::check_diag() {
    bool ret = false;
    if (board[0][0] != '*' && board[1][1] != '*' && board[2][2] != '*' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        ret = true;
    if(board[2][0] != '*' && board[1][1] != '*' && board[0][2] != '*' && board[2][0] == board[1][1] && board[1][1] == board[0][2])
        ret = true;

    return ret;
}

bool ttc::check_hor() {
    bool ret = false;
    if (board[0][0] != '*' && board[0][1] != '*' && board[0][2] != '*' && board[0][0] == board[0][1] && board[0][1] == board[0][2])
        ret = true;
    if (board[1][0] != '*' && board[1][1] != '*' && board[1][2] != '*' && board[1][0] == board[1][1] && board[1][1] == board[1][2])
        ret = true;
    if (board[2][0] != '*' && board[2][1] != '*' && board[2][2] != '*' && board[2][0] == board[2][1] && board[2][1] == board[2][2])
        ret = true;

    return ret;
}
bool ttc::check_vert() {
    bool ret = false;
    if (board[0][0] != '*' && board[1][0] != '*' && board[2][0] != '*' && board[0][0] == board[1][0] && board[1][0] == board[2][0])
        ret = true;
    if (board[0][1] != '*' && board[1][1] != '*' && board[2][1] != '*' && board[0][1] == board[1][1] && board[1][1] == board[2][1])
        ret = true;
    if (board[0][2] != '*' && board[1][2] != '*' && board[2][2] != '*' && board[0][2] == board[1][2] && board[1][2] == board[2][2])
        ret = true;

    return ret;
}


void ttc::main_loop() {
    cout << "Hello world" << endl;
    init();
    while(!check_diag() && !check_hor() && !check_vert()) {
        boardDisplay();
        get_user();
    }
    boardDisplay();
    if(!turn)
        cout<<"x won!" << endl;
    else
        cout << "o won!" << endl;

    cout << "Game over!" << endl;
}

bool ttc::play_game(agent_v1* p1, agent_v1* p2) {
    bool p1_win;
    while(!check_diag() && !check_hor() && !check_vert()) {
        std::pair<int,int> p1_move = p1->make_move(ttc::board);
        board[p1_move.first][p1_move.second] = 'o';
        curr_moves++;

        if(!(!check_diag() && !check_hor() && !check_vert()))
            return true;

        std::pair<int,int> p2_move = p2->make_move(ttc::board);
        board[p2_move.first][p2_move.second] = 'x';
        curr_moves++;
    }
    return false;
}

bool ttc::train_loop(agent_v1* player_1, agent_v1* player_2) {
    int one_win = 0;
    int two_win = 0;
    ttc::init();
    for(int i = 0; i < 100; i++) {
        //cout << "starting game: " << i << endl;
        if(ttc::play_game(player_1, player_2)) {
            player_2->adjust_weights(player_1, ttc::curr_moves);
            one_win++;
        }
        else {
            player_1->adjust_weights(player_2, ttc::curr_moves);
            two_win++;
        }
        //ttc::boardDisplay();
        ttc::init();
    }
    if(one_win > two_win) {
        cout << "player 1 was the winner with " << one_win << " wins!" << endl;
        return true;
    }
    else {
        cout << "player 2 was the winner with " << two_win << " wins!" << endl;
        return false;
    }
}

void ttc::play_against_bot(agent_v1 *agent) {
    init();
    agent->set_piece('x');
    while(!check_diag() && !check_hor() && !check_vert()) {
        boardDisplay();
        get_user();
        if(!(!check_diag() && !check_hor() && !check_vert()))
            break;

        std::pair<int,int> p2_move = agent->make_move(ttc::board);
        board[p2_move.first][p2_move.second] = 'x';
        turn = !turn;
    }
    boardDisplay();
    if(!turn)
        cout<<"x won!" << endl;
    else
        cout << "o won!" << endl;

    cout << "Game over!" << endl;
}

void ttc::play_game(agent_v2 *p1, agent_v2 *p2) {

}

bool ttc::train_loop(agent_v2 *player_1, agent_v2 *player_2) {
    return false;
}

void ttc::play_against_bot(agent_v2 *agent) {

}

std::vector<std::pair<int, int>> ttc::get_valid_moves(char curr[3][3]) {
    std::vector<std::pair<int, int>> ret;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(this->board[i][j] == '*')
                ret.emplace_back(i,j);

    return ret;
}




