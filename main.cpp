#include <iostream>
#include <utility>
#include <string>
#include <stdio.h>
#include "ttc.h"
#include "agent_v1.h"

using namespace std;

int main() {
    ttc tic{};
    auto* player_1 = new agent_v1;
    auto* player_2 = new agent_v1;

    player_1->init('o');
    player_2->init('x');
    //tic.main_loop();
    bool winner = tic.train_loop(player_1, player_2);
    cout << "Playing against the winner!" << endl;
    if(winner)
        tic.play_against_bot(player_1);
    else
        tic.play_against_bot(player_2);


    return 0;
}



