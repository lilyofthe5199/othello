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

int over_position( int i, int j )
{
    if ( i < 0 || i >= N || j < 0 || j >= N )
    {
    	return FALSE;
	}
    return TRUE;
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
        {
        	if(gameboard[i][j] == WHITE )	// WHITE
        	{
        		printf("O");
			} else if ( gameboard[i][j] == BLACK )	// BLACK
            {
                printf("X");
            } else
            {
                printf(" "); // 비어있음 
            }
        	printf("  ------------- \n");
		}
	printf("  ------------- \n");
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


void main() {

	//필요한 변수들 정의;
	othello();			// 게임 초기화
	
	while (isGameEnd() == 0) {	// Game 종료 조건 확인
		print_othello();			// 배치 상태 출력 등
		if (배치가 가능한 칸이 있는지 확인)
				continue;			// 두 playter 모두 배치가 불가능하면 반복문을 빠져나가야 함
			배치할 좌표 입력 받기;
		
		if (입력 좌표가 적절한지 체크)
			if (뒤집기 시도) {
				몇개 뒤집었는지 출력;
				턴 바꿈;
			}
			else
				부적절한 입력임을 출력;
			}
		check_result();			// 결과 출력
		
}

