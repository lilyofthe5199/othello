#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2	// 비어있음 

// gameboard
char gameboard[N][N];

// direction 
int direction[N][N][8]; // i, j 위치에서 방향 8개: N, W, E, S, NW, NE, SW, SE

int score[2];		// WHITE와 BLACK의 score
int player;			// player
int flip[8];		// 방향 8개: N, W, E, S, NW, NE, SW, SE
int isGameEnd = 0;	// 초기에 isGameEnd는 0 


// flip.c
int distance(int i, int j, int i_flip, int j_flip);
int able_flip(int i, int j);
int prompt_flip(int i, int j);
void print_flip();

// print_wrong_input.c
int print_wrong_input_range();
int print_wrong_input_occupied();
int print_wrong_input_flip();

// othello.c
int othello();
int print_othello();
int change_turn();
int input_othello(int *othello_row, int *othello_column);
int place_othello(int othello_row, int othello_column);
void check_result();

// position.c
int over_position(int row, int column);
int position_able(int i, int j);
int occupied_position(int othello_row, int othello_column);
