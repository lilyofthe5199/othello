#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset �Լ� ����� ���� �߰��� 

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2	// ������� 

// gameboard
char gameboard[N][N];

// direction 
int direction[N][N][8]; // i, j ��ġ���� ���� 8��: N, W, E, S, NW, NE, SW, SE

int score[2];		// WHITE�� BLACK�� score
int player;			// player
int flip[8];		// ���� 8��: N, W, E, S, NW, NE, SW, SE
int isGameEnd = 0;	// �ʱ⿡ isGameEnd�� 0 


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
		//�ʿ��� ������ ����
		int row;
		int column;
		int othello_row;
		int othello_column;
		
		othello(); 				// ���� �ʱ�ȭ
				
		while (isGameEnd == 0) 	// Game ���� ���� Ȯ��
		{ 
			print_othello(); 	// ��ġ ����, WHITE�� BLACK�� ����  ���
			if (position_able(row, column) == 0) // ��ġ������ ĭ�� �ִ��� Ȯ��
			{ 	
				isGameEnd = 1; 	// ���� ����
				continue;	 	// �� player ��� ��ġ�� �Ұ����ϸ� �ݺ����� ���������� ��							
			}
			
			input_othello(&othello_row, &othello_column);			//��ġ�� ��ǥ �Է� �ޱ�
		
			if (over_position(othello_row, othello_column) == 1)	// �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
			{ 	
				if (occupied_position(othello_row, othello_column) == 1)
				{
					if (able_flip(othello_row, othello_column))			// �����Ⱑ �����ϴٸ�  
					{
						place_othello(othello_row, othello_column);		// �Է¹��� othello ��ġ 
						
						while(able_flip(othello_row, othello_column))	// �����Ⱑ ������ ���� 
						{
							prompt_flip(othello_row, othello_column); 	// ������ �õ� 
						}
						print_flip(); 	// � ���������� ���
						change_turn(); 	// �� �ٲ�
					}
					else
						print_wrong_input_flip(); 	// flip�� �Ұ����� �Է����� ���
				}
				else
					print_wrong_input_occupied();	// �� ������ �ƴ��� ��� 
			}
			else
				print_wrong_input_range(); 			// 0-5������ ����� �Է����� ��� 			
		}
		check_result();		// ��� ��� 
	}
