#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset �Լ� ����� ���� �߰��� 

#define N 6
	
#define WHITE 0
#define BLACK 1
#define EMPTY 2
	
extern char gameboard[N][N];
extern int score[2];

	int over_position(int row, int column){	// �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
		if ((row < 0) || (row >= N) || (column < 0) || (column >= N)){
			return 0;
		}
		return 1;
	}

	int position_able(int i, int j){	// ��ġ������ ĭ�� �ִ��� Ȯ��
	// WHITE�� ������ 0 �̰ų� BLACK�� ������ 0 �̰ų� ����ִ� ĭ�� ���� ���(WHITE�� BLACK�� ������ ���� N*N�� �� ���)  ��ġ �Ұ���
		if ((score[WHITE] == 0) || (score[BLACK] == 0)|| (score[WHITE] + score[BLACK] == N * N))
		{
			return 0; // 0�� ��ȯ
		}
		// �� �� 
		return 1; // 1�� ��ȯ
	}
