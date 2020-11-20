#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2	


extern char gameboard[N][N];
extern int direction[N][N][8];
extern int score[2];
extern int player;
extern int flip[8];

	int othello(){	// ���� �ʱ�ȭ
	
		// gameboard�� EMPTY�� �ʱ�ȭ gameboard�� size ��ŭ 
		memset(gameboard, EMPTY, sizeof(gameboard));
		// WHITE�� �ʱ� ��ġ 
		gameboard[(N / 2) - 1][(N / 2) - 1] = WHITE;
		gameboard[(N / 2)][(N / 2)] = WHITE;
		// BLACK�� �ʱ� ��ġ 
		gameboard[(N / 2) - 1][(N / 2)] = BLACK;
		gameboard[(N / 2)][(N / 2) - 1] = BLACK;
		// WHITE�� BLACK�� ����
		score[WHITE] = 2;
		score[BLACK] = 2;
		// �ʱ� player�� WHITE 
		player = WHITE;
	}
	
	int print_othello(){	// ��ġ ����, WHITE�� BLACK�� ���� ���
	
		// ��ġ ����
		int i;
		int j;
		 
		printf( "\n  0 1 2 3 4 5\n");	// row ��ȣ
	    printf( " -------------\n" );	// row ����
	    for ( i=0; i<N; ++i )
	    {
	        printf( "%i|", i );	// column ��ȣ 
	        for ( j=0; j<N; ++j )
	        {
	            if ( gameboard[i][j] == WHITE )			// WHITE
	            {
	                printf("O");
	            } else if ( gameboard[i][j] == BLACK )	// BLACK
	            {
	                printf("X");
	            } else
	            {
	                printf(" "); // ������� 
	            }
	             
	            printf("|");	// column ����
	        }
	        printf( "\n" );
	        printf( " -------------\n" );	// row ����
	    }
	    printf( "\n" );
	   	printf(" STATUS - WHITE: %d, BLACK: %d\n\n", score[WHITE], score[BLACK]);	// WHITE�� BLACK�� ���� ���
	}

	int change_turn(){	// player�� �ٲ۴�.
		// player ���� 0 1 0 1 �ٲ�
		player = (player + 1) % 2;  
	}


	int input_othello(int *othello_row, int *othello_column){	// othello�� �Է� ���� 
		if(player == WHITE){	// player�� WHITE�� ���
			printf(" put a new White othello : ");
			scanf("%i %i", othello_row, othello_column);
		} else{					// player�� BLACK�� ���
			printf(" put a new Black othello : ");
			scanf("%i %i", othello_row, othello_column);
		}
	}

	int place_othello(int othello_row, int othello_column){
		 
		gameboard[othello_row][othello_column] = player;	// �ش���ġ�� player�� ���� �� 
		score[player]++;
		prompt_flip(othello_row, othello_column);			// flip �õ�
	}
	 
	void check_result(){	
		
		if (score[WHITE] > score[BLACK]){ 			// WHITE ������ �� ����
			printf("White wins.\n");
		} else if (score[WHITE] < score[BLACK]){ 	// BLACK ������ �� ����
			printf("Black wins.\n");
		} else										// WHITE�� BLACK�� ���� ���� 
			printf("Draw game.\n"); 
	}
