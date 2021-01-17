/**
 * @file ttt2.c
 * @author Abdullah Saad | 1043850 | asaad02@uoguelph.ca
 * @date november 23th 2020
 * @brief File c compiled to create an object file called ttt2.o.
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ttt.h"
#define imax(a,b) (((a)<(b))?(b):(a))
#define imin(a,b) (((a)>(b))?(b):(a))

/* This function will set init variabale to zero in entair htable */
void init_boards(){
    // loop through the entire htable array
    for (int i = 0; i < HSIZE; i++)
    {
        // set the init to zero 
        htable[i].init = 0; // indicate the elements of hash table is empty
    }
    
}
/* function return the number of markers x amd o */
int depth( Board board ){
    // variable hold how many markers
    int markers = 0 ;
    // loop through the entair board string
    for (int i = 0; i < BSIZE; i++)
    {
        // if board has 'x' or 'o' 
        if (board[i] == 'X' || board[i] == 'O')
        {
            markers++;
        }  
    }
    // return the number of markers
    return markers ;
    
}
/* this function should return who won the game */
char winner( Board board ){
    // for loop for entire win string 
    for (int i = 0; i < 8; i++)
    {
        // check array of row, column and diagonal positions of win and pos2idx
        if (board[pos2idx[WINS[i][0]]] == 'X' && board[pos2idx[WINS[i][1]]] == 'X' && board[pos2idx[WINS[i][2]]] == 'X'  )
        {
            int index = board_hash(board);
            // looping through the possible moves 
            for (int  i = 0; i < 9; i++){
                // store a value of -1 in the move array 
                htable[index].move[i]= -1;
            }
            return 'X'; //  if X has won the game,
        }
        if (board[pos2idx[WINS[i][0]]] == 'O' && board[pos2idx[WINS[i][1]]] == 'O' && board[pos2idx[WINS[i][2]]] == 'O'  )
        {
            int index = board_hash(board);
            // looping through the possible moves 
            for (int  i = 0; i < 9; i++){
                // store a value of -1 in the move array 
                htable[index].move[i]= -1;
            }
            return 'O'; // if O has won the game
        }
        
    }
    if (depth(board ) < 9)
    {
        return '?'; // if the game is incomplete and no-one has won.
    }
    return  '-'; //if the game is over and a draw
    
}
/* This function return which player turn */
char turn( Board board ){
    // counter for x
    int x = 0;
    // counter for O 
    int o = 0;
    // if depth equal to 9 
    if (depth(board ) == 9)
    {
        return '-'; // game over
    }
    // if X or O won the game 
    if (winner(board ) == 'X' || winner(board ) == 'O' )
    {
        // return game over
        return '-'; 
    }
    
    // Count X in board String 
    for (int i = 0; i < BSIZE; i++)
    {
        if (board[i] == 'X')
        {
            x++;
        }
        
    }
    // Count O in board String 
    for (int i = 0; i < BSIZE; i++)
    {
        if (board[i] == 'O')
        {
            o++;
        }
        
    }
    if (x == 0)
    {
        return 'X';
    }
    // if X bigger than O then O turn else X turn 
    if (x>o)
    {
        return 'O';
    }
    else
    {
        return 'X';
    }
}
/* The function should compute the hash index and set the variables of the structure */
void init_board( Board board ){
    // compute the hash index 
    int index = board_hash(board);
    //init should be set to 1
    htable[index].init = 1;
    //turn should be turn function for the given board
    htable[index].turn = turn(board);
    //depth should be depth function for the given board
    htable[index].depth= depth(board);
    //board should be by calling the strcpy function
    strcpy(htable[index].board,board);
    //winner should be winner function for the given board
    htable[index].winner= winner(board);
}
/* This function should create and join all the nodes of all possible tic-tac-toe games */
void join_graph( Board board ){
    // compute the hash index 
    int index = board_hash(board);
    // looping through the possible moves 
    for (int  i = 0; i < 9; i++)
    {
        // check the pos2idx index in the string for the board
        if (board[pos2idx[i]] == 'X'||board[pos2idx[i]] == 'O' )
        { 
            // store a value of -1 in the move array 
            htable[index].move[i]= -1;
        }
        // If the index in the string contains a number
        if (board[pos2idx[i]] == '0' || board[pos2idx[i]] == '1' || board[pos2idx[i]] == '2' || board[pos2idx[i]] == '3' || board[pos2idx[i]] == '4' || board[pos2idx[i]] == '5' || board[pos2idx[i]] == '6' || board[pos2idx[i]] == '7' || board[pos2idx[i]] == '8' )
        {
            // make a copy of the board
            Board copy;
            strcpy(copy , board);
            // whose turn is it 
            char player_turn = turn(board);
            // place the appropriate marker in pos2idx
            copy[pos2idx[i]]=player_turn;
            //compute the hash value of the new board
            int copyhash = board_hash(copy);
            // store hash value in the move array
            if (winner(board ) != 'X' && winner(board ) != 'O' )
            {
            htable[index].move[i]= copyhash;
            }
            // if the hash table already contains an entry (init!=0)
            if (htable[copyhash].init == 0 )
            {
                //calling init_board
                init_board(copy);
                //recursively calling join_graph.
                join_graph(copy);
            }   
        }   
    }
}
/* This function should assign a score to each entry in the htable */
void compute_score(){
    // for loop going through the htable
    for (int i = HSIZE - 1; i >= 0; i--)
    {
        // htable has an init of 1 
        if (htable[i].init == 1)
        {
            char result = htable[i].winner;
            switch (result)
            {
            //if the board results in a win for X, then the score is 1
            case 'X':
                htable[i].score = 1;
                break;
            //if the board results in a win for O, then the score is -1
            case 'O':
                htable[i].score = -1;
                break;
            //if the board is a complete game that ends in a tie, then the score is 0
            case '-':
                htable[i].score = 0;
                break;
            default:
                break;
            }
            
            // if it is X’s turn
            if (htable[i].turn == 'X')
            {
                htable[i].score = -1;
                // n the score is equal to the maximum of all the valid child nodes in the move array
                for (int b = 8; b >= 0; b--)
                {
                    if (htable[i].move[b] != -1)
                    {
                        htable[i].score =imax(htable[i].score, htable[htable[i].move[b]].score);
                    }
                    
                }
                
            }
            // if it is O’s turn
            else if (htable[i].turn == 'O')
            {
                htable[i].score = 1;
                //the score is equal to the minimum of all the valid child nodes in themove array.
                for (int b = 8; b >= 0; b--)
                {
                    if (htable[i].move[b] != -1)
                    {
                        htable[i].score =imin(htable[i].score, htable[htable[i].move[b]].score);
                    }
                    
                }
                
            }
            
        }
        
    }
    
}
/* This function should return the best possible move position. */
int best_move( int board ){
    int move = 0; 
    if (htable[board].turn == 'X')
    {
        for (int  i = 0; i < 9; i++)
        {
            if (htable[board].move[i] != -1 && htable[htable[board].move[i]].score > -1  )
            {
                move = i ; 
            }
            
        }
        
    }
    else if (htable[board].turn == 'O')
    {
        for (int  i = 0; i < 9; i++)
        {
            if (htable[board].move[i] != -1 && htable[htable[board].move[i]].score < -1  )
            {
                move = i ; 
            }
            
        }
        
    }
    return move ; 
}
