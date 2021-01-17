/**
 * @file count_nodes.c
 * @author Abdullah Saad | 1043850 | asaad02@uoguelph.ca
 * @date november 23th 2020
 * @brief File c compiled to create a program called count_nodes.
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
    int nodes = 0;
    for (int i = 0; i < HSIZE; i++)
    {
        if (htable[i].init == 1)
        {
            nodes++;
        }
        
    }
    printf(" The number of entries in the htable %d\n",nodes );
    
    return 0;
}
