# an-unbeatable-tic-tac-toe-noughts-and-crosses-player.
working with both a hash-table and a graph data structure.



# typedef char Board[HSIZE];
This typedef is used to represent a printable tic-tac-toe board. The initial board will be printed
as:
0|1|2
-+-+-
3|4|5
-+-+-
6|7|8
This board is represented by the string:
# Board START_BOARD = "0|1|2\n-+-+-\n3|4|5\n-+-+-\n6|7|8\n";
Once the game begins players select one of the places on the board (indicated by numbers) and
place their markers (capital Xs and capital Os) over top of the numbers. The length of the board
string always stays the same (HSIZE including the null terminator character). E.g. if the player,
X, decides to play a piece at position 4, then the new board string would look like:
"0|1|2\n-+-+-\n3|X|5\n-+-+-\n6|7|8\n";
In order to quickly figure out where in the string to draw the letter, I have provided an array of
integers (pos2idx) which can be used to map a board position to an index in the board string. So,
to play an X at position 4 you could write:
# board_string[ pos2idx[4] ] = ‘X’;
The objective of the game of tic-tac-toe is to place three markers in one row, column or diagonal.
An array called WINS contains 8 rows corresponding to the possible winning configurations, with
3 position values in each row.

# A structure called BoardNode represents a node in the graph of all possible tic-tac-toe games.
Each node represents one board, some properties for that board, and the moves that can be
applied to that board and the subsequent boards, based on those nodes.
struct BoardNode
{
char init; // 0=not initialized, or 1=initialized
char turn; // 'X', 'O', '-'=board is full (game over)
int depth; // depth of the node in the graph = moves played
Board board; // printable board file
char winner; // 'X', 'O', '-' (tie), '?' (game in progress)
int move[9]; // board hashes for all move positions; -1=illegal
int score; // winner of the game if both players play smartly
// 1=X -1=O 0=tie
};

# A global variable called htable is designed to describe all the possible boards in the game of tic-
tac-toe (and a bunch of impossible boards as well).

struct BoardNode htable[HSIZE];


# void init_boards();
This is a function which you will create in the file ttt2.c. The function should go through the
entire htable and set the init variable in each structure to 0, to indicate that that element of the
hash table is empty (hasn’t been initialized).
# int depth( Board board );
This is a function which you will create in the file ttt2.c. The function should return the
number of markers (Xs and Os) on the board.
# char winner( Board board );
This is a function which you will create in the file ttt2.c. The function should return either:
• ‘X’, if X has won the game,
• ‘O’, if O has won the game,
• ‘-‘, if the game is over and a draw (the board is filled and no-one has won), or
• ‘?’, if the game is incomplete and no-one has won.
You can use the pos2idx and WINS arrays to help to detect wins, and the depth function to
determine whether the game is over.
# char turn( Board board );
This is a function which you will create in the file ttt2.c. The function should return either:
• ‘X’, if it is X’s turn,
• ‘O’, if it is O’s turn,
• ‘-‘, if the game is over a (the board is filled).
You can use the depth function and modular division to determine whose turn it is.

# void init_board( Board board );
This is a function which you will create in the file ttt2.c. The function should compute the
hash index of the provided board using the board_hash function in ttt1.c. It should set the
variables of the structure at that index as follows:
• init should be set to 1,
• turn should be set to the return value of the turn function for the given board,
• depth should be set to the return value of the depth function for the given board,
• board should be set to the argument board (by calling the strcpy function), and
• winner should be set to the return value of the winner function for the given board.
# void join_graph( Board board );
This is a function which you will create in the file ttt2.c. This function should create and join
all the nodes of all possible tic-tac-toe games. This can be done recursively by looping over all
the possible move positions (1-8). For each position, if there is already a piece in that position
(check the pos2idx index in the string for the board), then store a value of -1 in the
corresponding position in the move array in the appropriate structure of the htable (computed by
calling the board_hash function). If the index in the string contains a number instead (the spot
is empty), then you must make a copy of the board, place the appropriate marker (turn(...)) in
the appropriate spot (pos2idx) in the string. Then, you will need to check if the hash table
already contains an entry (init!=0) for the new board string. If it does, you can loop to the next
move position. If there is no entry, you will need to create one by calling init_board and
recursively calling join_graph.
show_node
This is a program that accepts 0 or more integer command line arguments. It will display the
value of the board node corresponding to the hash values supplied on the command line. It will
call init_board(), init_board(START_BOARD), join_graph(START_BOARD), and, if you have
implemented it, compute_score(). Then, for each command line argument it will call
print_node on the location in the htable corresponding to the argument (e.g. if you pass a
single command line argument of 0, it should print the opening board).
# count_nodes
This program will call init_board(), init_board(START_BOARD), and
join_graph(START_BOARD), and then count the number of entries in the htable that have
init==1. This is nodes that can actually occur in real tic-tac-toe games.

# void compute_score();
This is a function which you will create in the file ttt2.c. This function should assign a score
to each entry in the htable that has an init value of 1. The score to be assigned is defined by
the following rules:
1) if the board results in a win for X, then the score is 1, otherwise
2) if the board results in a win for O, then the score is -1, otherwise
3) if the board is a complete game that ends in a tie, then the score is 0, otherwise
4) if it is X’s turn, then the score is equal to the maximum of all the valid child nodes in the
move array, otherwise

5) if it is O’s turn, then the score is equal to the minimum of all the valid child nodes in the
move array.
Hints: You must evaluate the nodes in order of decreasing depth. You can do this in a loop that
counts down from 9 to 0, or using a recursive function that assigns values “coming out of” the
recursion.
# int best_move( int board );
This is a function which you will create in the file ttt2.c. This function should return the best
possible move position. Note that the best possible move position is the move leading to the
child node with the highest score for X, and the lowest score for O. You can test this code by
using the alphatoe program.
