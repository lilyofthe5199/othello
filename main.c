#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2

#define FALSE 0
#define TRUE 1

char gameboard[N][N];
int direction[8][8][8];
int scores[2];
int player;


int othello()		// 게임 초기화 
{
 	memset( gameboard, EMPTY, sizeof( gameboard ) );
	// BLACK
	gameboard[(N/2)-1][(N/2)-1] = BLACK;
	gameboard[(N/2)][(N/2)] = BLACK;
	// WHITE
	gameboard[(N/2)-1][(N/2)] = WHITE;
	gameboard[(N/2)][(N/2)-1] = WHITE;
	// SCORE
	scores[WHITE] = 2;
    scores[BLACK] = 2;
}

void print_othello()	// 배치 상태 출 력 
{
	int i;
	int j;
	printf("   0 1 2 3 4 5 \n");
	printf("  ------------- \n");
	for (i=0; i<N; ++i)
	{
		printf("%i |", i);
		for (j=0; j<N; ++j )
        {/*
        	if(gameboard[i][j] == WHITE )	// WHITE
        	{
        		printf("O");
			} else if ( gameboard[i][j] == BLACK )	// BLACK
            {
                printf("X");
            } else
            {
                printf(" "); // 비어있음 
            }*/
        	printf("  ------------- \n");
		}
	printf("  ------------- \n");
}

/*
int over_position( int i, int j )
{
    if ( i < 0 || i >= N || j < 0 || j >= N )
    {
    	return FALSE;
	}
    return TRUE;
}

void change_turn()
{
	player = (player +1)%2; // player 값을 0 1 0 1 바꿈 
}


void input_othello(int *othello_row, int *othello_column)
{
	printf("put a new white othello : ");
	scanf( "%d %d", othello_row, othello_column );
}

int over_position(int row, int column) // 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
{
	if( (row <0 )||(row>=N)||(column<0)||(column>=N))
	{
		return 0;
	}
	return 1;
}

void prompt_flip() // 뒤집기 시도
{
}

void position_able()
{
	if((score[EMPTY] == 0)||(score[WHITE] == 0)||(score[BLACK] == 0))
	{
		return = 0;
	}
	return = 1;
}

void check_result( )
{
    printf("<Final score>\n");
	printf("WHITE: %d, BLACK: %d\n", scores[WHITE], scores[BLACK] );
    if ( scores[WHITE] > scores[BLACK] )
        printf( "White wins.\n");
    else if ( scores[WHITE] < scores[BLACK] )
        printf( "Black wins.\n");
    else
        printf( "Draw game.\n" );
}

int print_wrong_input()
{
	printf("invalid input!");
}

void main() {

	//필요한 변수들 정의;
	othello();			// 게임 초기화
	
	while (isGameEnd() == 0) {	// Game 종료 조건 확인
		print_othello();			// 배치 상태 출력 등
		if (position_able() == 1) // 배치가능한 칸이 있는지 확인
		// 비어있는 칸 없음
		// WHITE가 없음
		// BLACK이 없음
		// 뒤집기가 가능한 칸이 없음 
				continue;			// 두 playter 모두 배치가 불가능하면 반복문을 빠져나가야 함
			input_othello(int *othello_row, int *othello_column); //배치할 좌표 입력 받기
		
		if (over_position(&othello_row, &othello_column) == 1) // 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
			if (prompt_flip())// 뒤집기 시도 
			{
				몇개 뒤집었는지 출력;
				change_turn() //턴 바꿈
			}
			else
				print_wrong_input();//부적절한 입력임을 출력
			}
		check_result();			// 결과 출력
		
}
*/
void main(){
	othello();
	print_othello();
}
