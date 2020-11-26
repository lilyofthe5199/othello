#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset 함수 사용을 위해 추가함 

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
extern int distance(int i, int j, int i_flip, int j_flip);
extern int able_flip(int i, int j);
extern int prompt_flip(int i, int j);
extern void print_flip();

// print_wrong_input.c
extern int print_wrong_input_range();
extern int print_wrong_input_occupied();
extern int print_wrong_input_flip();

// othello.c
extern int othello();
extern int print_othello();
extern int change_turn();
extern int input_othello(int *othello_row, int *othello_column);
extern int place_othello(int othello_row, int othello_column);
extern void check_result();

// position.c
extern int over_position(int row, int column);
extern int position_able(int i, int j);
extern int occupied_position(othello_row, othello_column);

	int main()
	{
		//필요한 변수들 정의
		int row;
		int column;
		int othello_row;
		int othello_column;
		
		othello(); 				// 게임 초기화
				
		while (isGameEnd == 0) 	// Game 종료 조건 확인
		{ 
			print_othello(); 	// 배치 상태, WHITE와 BLACK의 점수  출력
			if (position_able(row, column) == 0) // 배치가능한 칸이 있는지 확인
			{ 	
				isGameEnd = 1; 	// 게임 종료
				continue;	 	// 두 player 모두 배치가 불가능하면 반복문을 빠져나가야 함							
			}
			
			input_othello(&othello_row, &othello_column);			//배치할 좌표 입력 받기
		
			if (over_position(othello_row, othello_column) == 1)	// 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
			{ 	
				if (occupied_position(othello_row, othello_column) == 1)
				{
					if (able_flip(othello_row, othello_column))			// 뒤집기가 가능하다면  
					{
						place_othello(othello_row, othello_column);		// 입력받은 othello 배치 
						
						while(able_flip(othello_row, othello_column))	// 뒤집기가 가능한 동안 
						{
							prompt_flip(othello_row, othello_column); 	// 뒤집기 시도 
						}
						print_flip(); 	// 몇개 뒤집었는지 출력
						change_turn(); 	// 턴 바꿈
					}
					else
						print_wrong_input_flip(); 	// flip이 불가능한 입력임을 출력
				}
				else
					print_wrong_input_occupied();	// 빈 공간이 아님을 출력 
			}
			else
				print_wrong_input_range(); 			// 0-5범위를 벗어나는 입력임을 출력 			
		}
		check_result();		// 결과 출력 
	}
