#ifndef HELP_FUNCTIONS_HH
#define HELP_FUNCTIONS_HH

#include <iostream>
#include <vector>

using namespace std;

void print_board(vector<vector<char>>& board);
void enlarge_board_zero(vector<vector<char>>& board);
void enlarge_board_end(vector<vector<char>>& board);
bool hit(char symbol, unsigned int x, unsigned int y, vector<vector<char>>& board);
bool parse_commands(string cmd1, string cmd2, char player, vector<vector<char>>& board);
bool if_won(vector<vector<char>>& board, char player);
bool ifempty(vector<vector<char>>& board);


#endif // HELP_FUNCTIONS_HH
