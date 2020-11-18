#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2	// 비어있음 

#define FALSE 0
#define TRUE 1

// gameboard[i][j]
char gameboard[N][N];

// direction[i][j][8] 
int direction[N][N][8]; // i, j 위치에서 방향 8개: N, W, E, S, NW, NE, SW, SE

int score[2];
int player;
int flip[8];
int isGameEnd = 0;

int othello()		// 게임 초기화 
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

int print_othello()	// 배치 상태 출력 
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
                printf(" "); // 비어있음 
            }
            printf("|");
        }
        printf( "\n" );
        printf( " -------------\n" );
    }
    printf( "\n" );
   	printf(" STATUS - WHITE: %d, BLACK: %d\n\n", score[WHITE], score[BLACK]);
}

	int change_turn() // player를 바꾼다.
	{
		player = (player + 1) % 2; // player 값을 0 1 0 1 바꿈 
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

	int over_position(int row, int column) // 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
	{
		if ((row < 0) || (row >= N) || (column < 0) || (column >= N))
		{
			return 0;
		}
		return 1;
	}

	int prompt_flip(int i, int j) // 뒤집기 시도
	{
		int opposing_player = (player + 1) % 2; // player 가 0 이면 상대편은 1, player가 1 이면 상대편은 0 
		int i_flip;
		int j_flip;
		
		// 방향 4개: N, W, E, S
		// N 위쪽
		i_flip = i - 1;
		j_flip = j;
		while (gameboard[i_flip][j_flip] == opposing_player)
		{

			gameboard[i_flip][j_flip] = player;	// player의 알로 바뀜
			score[player]++;
			score[opposing_player]--;
			//i_flip -= 1;
			flip[0]++;
		}

		// W 왼쪽
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

		// E 오른쪽
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

		// S 아래쪽
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

		// 대각선 방향 4개: NW, NE, SW, SE 
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
		
		if (score[WHITE] > score[BLACK])	// WHITE 점수가 더 많음
			printf("White wins.\n");
		else if (score[WHITE] < score[BLACK])	// BLACK 점수가 더 많음
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
		//필요한 변수들 정의
		int row;
		int column;
		int othello_row;
		int othello_column;
		
		othello();			// 게임 초기화

		while (isGameEnd == 0) // Game 종료 조건 확인
		{	
			print_othello();			// 배치 상태 출력 등
			
			// 배치가능한 칸이 있는지 확인
			if (position_able(row, column) == 0)	
			{
										// 비어있는 칸 없음
										// WHITE가 없음
										// BLACK이 없음

										// 뒤집기 가능한 칸이 없음??
				isGameEnd = 1;
				// 두 playter 모두 배치가 불가능하면 반복문을 빠져나가야 함
				continue;  
			}
		
			//배치할 좌표 입력 받기
			input_othello(&othello_row, &othello_column); 
			
			// 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
			if (over_position(othello_row, othello_column) == 1)
			{	
				// 뒤집기 시도
				if (place_othello(othello_row, othello_column))
				{
					print_flip(); // 몇개 뒤집었는지 출력
					change_turn(); // 턴 바꿈
				}
				else
					// flip 못함
					print_wrong_input_flip();	// 부적절한 입력임을 출력		 
			}
			else
				// 범위내에 없음
				print_wrong_input_range();
					
		}
		
		check_result();			// 결과 출력 

	}

	

