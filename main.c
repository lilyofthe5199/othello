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
        {/*
        	if(gameboard[i][j] == WHITE )	// WHITE
        	{
        		printf("O");
			} else if ( gameboard[i][j] == BLACK )	// BLACK
            {
                printf("X");
            } else
            {
                printf(" "); // ������� 
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
	player = (player +1)%2; // player ���� 0 1 0 1 �ٲ� 
}


void input_othello(int *othello_row, int *othello_column)
{
	printf("put a new white othello : ");
	scanf( "%d %d", othello_row, othello_column );
}

int over_position(int row, int column) // �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
{
	if( (row <0 )||(row>=N)||(column<0)||(column>=N))
	{
		return 0;
	}
	return 1;
}

void prompt_flip() // ������ �õ�
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

	//�ʿ��� ������ ����;
	othello();			// ���� �ʱ�ȭ
	
	while (isGameEnd() == 0) {	// Game ���� ���� Ȯ��
		print_othello();			// ��ġ ���� ��� ��
		if (position_able() == 1) // ��ġ������ ĭ�� �ִ��� Ȯ��
		// ����ִ� ĭ ����
		// WHITE�� ����
		// BLACK�� ����
		// �����Ⱑ ������ ĭ�� ���� 
				continue;			// �� playter ��� ��ġ�� �Ұ����ϸ� �ݺ����� ���������� ��
			input_othello(int *othello_row, int *othello_column); //��ġ�� ��ǥ �Է� �ޱ�
		
		if (over_position(&othello_row, &othello_column) == 1) // �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
			if (prompt_flip())// ������ �õ� 
			{
				� ���������� ���;
				change_turn() //�� �ٲ�
			}
			else
				print_wrong_input();//�������� �Է����� ���
			}
		check_result();			// ��� ���
		
}
*/
void main(){
	othello();
	print_othello();
}
