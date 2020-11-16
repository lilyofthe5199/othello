#define N 6
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define W 0
#define B 1

int gameboard[N][N];

int othello()		// 게임 초기화 
{
	//memset( gameboard, Empty, sizeof( gameboard ) );
	gameboard[(N/2)-1][(N/2)-1] = B; // BLACK
	gameboard[(N/2)+1][(N/2)+1] = B; // BLACK
	gameboard[(N/2)-1][(N/2)+1] = W; // WHITE
	gameboard[(N/2)+1][(N/2)-1] = W; // WHITE
}

int print_othello()	// 배치 상태 출 력 
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
        	printf("  ------------- \n");
		}
	printf("  ------------- \n");
}

void main()
{
	othello();
	print_othello();
}

/*
void main() {
	//필요한 변수들 정의;
	othello();			// 게임 초기화

	//while (isGameEnd() == 0) {	// Game 종료 조건 확인
		print_othello();			// 배치 상태 출력 등
		if (배치가 가능한 칸이 있는지 확인)
				continue;			// 두 playter 모두 배치가 불가능하면 반복문을 빠져나가야 함
			배치할 좌표 입력 받기;
		
		if (입력 좌표가 적절한지 체크)
			if (뒤집기 시도) {
				몇개 뒤집었는지 출력;
				턴 바꿈;
			}
			else
				부적절한 입력임을 출력;
			}
		check_result();			// 결과 출력
}*/
