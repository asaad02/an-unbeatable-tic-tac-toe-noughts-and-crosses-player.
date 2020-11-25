/**
 * @file show_node.c
 * @author Abdullah Saad | 1043850 | asaad02@uoguelph.ca
 * @date november 23th 2020
 * @brief File c compiled to create an executable file called show_node
 **/

#include <stdio.h>
#include <stdlib.h>
#include "ttt.h"

int main(int argc, char const *argv[])
{
    //call init_boards
    init_boards();
    // call  init_board(START_BOARD)
    init_board(START_BOARD);
    // call join_graph(START_BOARD) 
    join_graph(START_BOARD);
    // call compute_score()
    compute_score();

    for (int i = 1; i < argc; i++)
    {
        int command = atoi(argv[i]);
        // for each command line argument it will call print_node
        print_node( htable[command]);
    }
    


    return 0;
}
