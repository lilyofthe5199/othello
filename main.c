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

int othello()		// ���� �ʱ�ȭ 
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




void print_othello()	// ��ġ ���� �� �� 
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
                printf(" "); // ������� 
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

	//�ʿ��� ������ ����;
	othello();			// ���� �ʱ�ȭ
	
	while (isGameEnd() == 0) {	// Game ���� ���� Ȯ��
		print_othello();			// ��ġ ���� ��� ��
		if (��ġ�� ������ ĭ�� �ִ��� Ȯ��)
				continue;			// �� playter ��� ��ġ�� �Ұ����ϸ� �ݺ����� ���������� ��
			��ġ�� ��ǥ �Է� �ޱ�;
		
		if (�Է� ��ǥ�� �������� üũ)
			if (������ �õ�) {
				� ���������� ���;
				�� �ٲ�;
			}
			else
				�������� �Է����� ���;
			}
		check_result();			// ��� ���
		
}

