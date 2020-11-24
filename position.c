#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset 함수 사용을 위해 추가함 

#define N 6
	
#define WHITE 0
#define BLACK 1
#define EMPTY 2
	
extern char gameboard[N][N];
extern int score[2];

	int over_position(int row, int column){	// 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
		if ((row < 0) || (row >= N) || (column < 0) || (column >= N)){
			return 0;
		}
		return 1;
	}

	int position_able(int i, int j){	// 배치가능한 칸이 있는지 확인
	// WHITE의 점수가 0 이거나 BLACK의 점수가 0 이거나 비어있는 칸이 없는 경우(WHITE와 BLACK의 점수의 합이 N*N이 된 경우)  배치 불가능
		if ((score[WHITE] == 0) || (score[BLACK] == 0)|| (score[WHITE] + score[BLACK] == N * N))
		{
			return 0; // 0을 반환
		}
		// 그 외 
		return 1; // 1을 반환
	}
