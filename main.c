#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2	// ������� 

#define FALSE 0
#define TRUE 1

// gameboard[i][j]
char gameboard[N][N];

// direction[i][j][8] 
int direction[N][N][8]; // i, j ��ġ���� ���� 8��: N, W, E, S, NW, NE, SW, SE

int score[2];
int player;
int flip[8];
int isGameEnd = 0;

int othello()		// ���� �ʱ�ȭ 
{
	memset(gameboard, EMPTY, sizeof(gameboard));
	// WHITE
	gameboard[(N / 2) - 1][(N / 2) - 1] = WHITE;
	gameboard[(N / 2)][(N / 2)] = WHITE;
	// BLACK
	gameboard[(N / 2) - 1][(N / 2)] = BLACK;
	gameboard[(N / 2)][(N / 2) - 1] = BLACK;
	// SCORE
	score[WHITE] = 2;
	score[BLACK] = 2;
	player = WHITE;
}

int print_othello()	// ��ġ ���� ��� 
{
	int i;
	int j;
	printf( "\n  0 1 2 3 4 5\n");
    printf( " -------------\n" );
    for ( i=0; i<N; ++i )
    {
        printf( "%i|", i );
        for ( j=0; j<N; ++j )
        {
            if ( gameboard[i][j] == WHITE )	// WHITE
            {
                printf("O");
            } else if ( gameboard[i][j] == BLACK )	// BLACK
            {
                printf("X");
            } else
            {
                printf(" "); // ������� 
            }
            printf("|");
        }
        printf( "\n" );
        printf( " -------------\n" );
    }
    printf( "\n" );
   	printf(" STATUS - WHITE: %d, BLACK: %d\n\n", score[WHITE], score[BLACK]);
}

	int change_turn() // player�� �ٲ۴�.
	{
		player = (player + 1) % 2; // player ���� 0 1 0 1 �ٲ� 
	}


	int input_othello(int *othello_row, int *othello_column)
	{
		if(player == WHITE)
		{
			printf("put a new White othello : ");
			scanf("%i %i", othello_row, othello_column);
		} else
		{
			printf("put a new Black othello : ");
			scanf("%i %i", othello_row, othello_column);
		}
		
	}

	int over_position(int row, int column) // �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
	{
		if ((row < 0) || (row >= N) || (column < 0) || (column >= N))
		{
			return 0;
		}
		return 1;
	}

	int prompt_flip(int i, int j) // ������ �õ�
	{
		int opposing_player = (player + 1) % 2; // player �� 0 �̸� ������� 1, player�� 1 �̸� ������� 0 
		int i_flip;
		int j_flip;
		
		// ���� 4��: N, W, E, S
		// N ����
		i_flip = i - 1;
		j_flip = j;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;	// player�� �˷� �ٲ�
			score[player]++;
			score[opposing_player]--;
			//i_flip -= 1;
			flip[0]++;
		}

		// W ����
		i_flip = i;
		j_flip = j - 1;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;
			score[player]++;
			score[opposing_player]--;
			//j_flip -= 1;
			flip[1]++;
		}

		// E ������
		i_flip = i;
		j_flip = j + 1;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;
			score[player]++;
			score[opposing_player]--;
			//j_flip += 1;
			flip[2]++;
		}

		// S �Ʒ���
		i_flip = i + 1;
		j_flip = j;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;
			score[player]++;
			score[opposing_player]--;
			//i_flip += 1;
			flip[3]++;
		}

		// �밢�� ���� 4��: NW, NE, SW, SE 
		// NW
		i_flip = i - 1;
		j_flip = j - 1;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;
			score[player]++;
			score[opposing_player]--;
			//i_flip -= 1;
			//j_flip -= 1;
			flip[4]++;
		}

		// NE
		i_flip = i - 1;
		j_flip = j + 1;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;
			score[player]++;
			score[opposing_player]--;
			//i_flip -= 1;
			//j_flip += 1;
			flip[5]++;
		}

		// SW
		i_flip = i + 1;
		j_flip = j - 1;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;
			score[player]++;
			score[opposing_player]--;
			//i_flip += 1;
			//j_flip -= 1;
			flip[6]++;
		}

		// SE
		i_flip = i + 1;
		j_flip = j + 1;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{
			
			gameboard[i_flip][j_flip] = player;
			score[player]++;
			score[opposing_player]--;
			//i_flip += 1;
			//j_flip += 1;
			flip[7]++;
		}

	
	}

	void print_flip()
	{
		printf("N:%i W:%i E:%i S:%i NW:%i NE:%i SW:%i SE:%i\n\n", flip[0], flip[1], flip[2], flip[3], flip[4], flip[5], flip[6], flip[7]);
	}

	int position_able(int i, int j)
	{

		if ((gameboard[i][j] != EMPTY) || (score[WHITE] == 0) || (score[BLACK] == 0))
		{
			return 0;
		}
		if (over_position(i, j) == 0)
		{
			return 0;
		}
		return 1;
	}

	int place_othello(int othello_row, int othello_column)
	{
	
		//input_othello(&othello_row, &othello_column);
	
		gameboard[othello_row][othello_column] = player;
	
		prompt_flip(othello_row, othello_column);
	
	}
	 
	void check_result()
	{
		
		if (score[WHITE] > score[BLACK])	// WHITE ������ �� ����
			printf("White wins.\n");
		else if (score[WHITE] < score[BLACK])	// BLACK ������ �� ����
			printf("Black wins.\n");
		else
			printf("Draw game.\n");
	}

	int print_wrong_input_flip()
	{
		printf("invalid input!\n");
	}

	int print_wrong_input_range()
	{
		printf("invalid input!");
		printf("(should be less than 6)\n");
	}
	
	int main()
	{
		//�ʿ��� ������ ����
		int row;
		int column;
		int othello_row;
		int othello_column;
		
		othello();			// ���� �ʱ�ȭ

		while (isGameEnd == 0) // Game ���� ���� Ȯ��
		{	
			print_othello();			// ��ġ ���� ��� ��
			
			// ��ġ������ ĭ�� �ִ��� Ȯ��
			if (position_able(row, column) == 0)	
			{
										// ����ִ� ĭ ����
										// WHITE�� ����
										// BLACK�� ����

										// ������ ������ ĭ�� ����??
				isGameEnd = 1;
				// �� playter ��� ��ġ�� �Ұ����ϸ� �ݺ����� ���������� ��
				continue;  
			}
		
			//��ġ�� ��ǥ �Է� �ޱ�
			input_othello(&othello_row, &othello_column); 
			
			// �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
			if (over_position(othello_row, othello_column) == 1)
			{	
				// ������ �õ�
				if (place_othello(othello_row, othello_column))
				{
					print_flip(); // � ���������� ���
					change_turn(); // �� �ٲ�
				}
				else
					// flip ����
					print_wrong_input_flip();	// �������� �Է����� ���		 
			}
			else
				// �������� ����
				print_wrong_input_range();
					
		}
		
		check_result();			// ��� ��� 

	}

	

