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

	int othello(){	// 게임 초기화
	
		// gameboard를 EMPTY로 초기화 gameboard의 size 만큼 
		memset(gameboard, EMPTY, sizeof(gameboard));
		// WHITE의 초기 배치 
		gameboard[(N / 2) - 1][(N / 2) - 1] = WHITE;
		gameboard[(N / 2)][(N / 2)] = WHITE;
		// BLACK의 초기 배치 
		gameboard[(N / 2) - 1][(N / 2)] = BLACK;
		gameboard[(N / 2)][(N / 2) - 1] = BLACK;
		// WHITE와 BLACK의 점수
		score[WHITE] = 2;
		score[BLACK] = 2;
		// 초기 player는 WHITE 
		player = WHITE;
	}
	
	int print_othello(){	// 배치 상태, WHITE와 BLACK의 점수 출력
	
		// 배치 상태
		int i;
		int j;
		 
		printf( "\n  0 1 2 3 4 5\n");	// row 번호
	    printf( " -------------\n" );	// row 구분
	    for ( i=0; i<N; ++i )
	    {
	        printf( "%i|", i );	// column 번호 
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
	                printf(" "); // 비어있음 
	            }
	             
	            printf("|");	// column 구분
	        }
	        printf( "\n" );
	        printf( " -------------\n" );	// row 구분
	    }
	    printf( "\n" );
	   	printf(" STATUS - WHITE: %d, BLACK: %d\n\n", score[WHITE], score[BLACK]);	// WHITE와 BLACK의 점수 출력
	}

	int change_turn(){	// player를 바꾼다.
		// player 값을 0 1 0 1 바꿈
		player = (player + 1) % 2;  
	}


	int input_othello(int *othello_row, int *othello_column){	// othello를 입력 받음 
		if(player == WHITE){	// player가 WHITE인 경우
			printf(" put a new White othello : ");
			scanf("%i %i", othello_row, othello_column);
		} else{					// player가 BLACK인 경우
			printf(" put a new Black othello : ");
			scanf("%i %i", othello_row, othello_column);
		}
	}

	int place_othello(int othello_row, int othello_column){
		 
		gameboard[othello_row][othello_column] = player;	// 해당위치에 player의 알을 둠 
		score[player]++;
		prompt_flip(othello_row, othello_column);			// flip 시도
	}
	 
	void check_result(){	
		
		if (score[WHITE] > score[BLACK]){ 			// WHITE 점수가 더 많음
			printf("White wins.\n");
		} else if (score[WHITE] < score[BLACK]){ 	// BLACK 점수가 더 많음
			printf("Black wins.\n");
		} else										// WHITE와 BLACK의 점수 동일 
			printf("Draw game.\n"); 
	}
