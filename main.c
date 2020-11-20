#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset 함수 사용을 위해 추가함 

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2	// 비어있음 

// gameboard[i][j]
char gameboard[N][N];

// direction[i][j][8] 
int direction[N][N][8]; // i, j 위치에서 방향 8개: N, W, E, S, NW, NE, SW, SE

int score[2];
int player;
int flip[8];
int isGameEnd = 0;

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

	int over_position(int row, int column){	// 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
		if ((row < 0) || (row >= N) || (column < 0) || (column >= N)){
			return 0;
		}
		return 1;
	}

	int distance(int i, int j, int i_flip, int j_flip){
		int i_distance;
		int j_distance;

		i_distance = abs(i - i_flip);
		j_distance = abs(j - j_flip);
		
		if (i_distance > 0) {
			return i_distance;
		}
		return j_distance;
	}

	int able_flip(int i, int j) {	// 뒤집기 가능한 칸이 있는지 확인
		// direction[i][j]를 0으로 초기화 8(방향의 수)만큼 
		memset(direction[i][j], 0, N);

		int opposing_player = (player + 1) % 2;
		int i_flip;
		int j_flip;

		// 방향 4개: N, W, E, S
		// N 위쪽
		i_flip = i - 1;	// 위쪽 
		j_flip = j;
		while (over_position(i_flip, j_flip) && gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1; // 1 한번 더 감소 
		}
		// 플립 하고자 하는 방향으로가면 현재 player의 알이 있어야함 && 현재 player의 알과 새로운 알 사이의 거리가 2보다 크거나 같아야함(1보다 커야함)(맞다아 있으면 안되기 때문에)
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player)&&(distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][0] = 1;
			return 1; // 뒤집기 가능하다
		}

		// W 왼쪽
		i_flip = i;
		j_flip = j - 1;	 // 왼쪽  
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip -= 1; // 1 한번 더 감소
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][1] = 1;
			return 1; // 뒤집기 가능하다
		}

		// E 오른쪽
		i_flip = i;
		j_flip = j + 1;	// 오른쪽 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip +=1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][2] = 1;
			return 1; // 뒤집기 가능하다
		}

		// S 아래쪽
		i_flip = i + 1;	// 아래쪽 
		j_flip = j;
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][3] = 1;
			return 1; // 뒤집기 가능하다
		}

		// 대각선 방향 4개: NW, NE, SW, SE 
		// NW
		i_flip = i - 1; // 위쪽 
		j_flip = j - 1;	// 왼쪽 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;
			j_flip -= 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][4] = 1;
			return 1; // 뒤집기 가능하다
		}

		// NE
		i_flip = i - 1; // 위쪽 
		j_flip = j + 1; // 오른쪽 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;
			j_flip += 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][5] = 1;
			return 1; // 뒤집기 가능하다
		}

		// SW
		i_flip = i + 1;	// 아래쪽  
		j_flip = j - 1; // 왼쪽 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1; 
			j_flip -= 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][6] = 1;
			return 1; // 뒤집기 가능하다
		}

		// SE 
		i_flip = i + 1; // 아래쪽  
		j_flip = j + 1; // 오른쪽 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {

			i_flip += 1;
			j_flip += 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][7] = 1;
			return 1; // 뒤집기 가능하다
		}

		return 0; // 뒤집기 불가능하면 0 반환
	
	}

	int prompt_flip(int i, int j){	// 뒤집기 시도
		memset(flip, 0, N);
		// player 가 0 이면 상대편은 1, player가 1 이면 상대편은 0
		int opposing_player = (player + 1) % 2;
		int i_flip;
		int j_flip;
		
		// 방향 4개: N, W, E, S
		// N 위쪽
		if (direction[i][j][0]) {
			i_flip = i - 1;	// 위쪽 
			j_flip = j;
			while (gameboard[i_flip][j_flip] == opposing_player){
				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// N 방항 flip[0] 증가 
				flip[0]++;
				
				i_flip -= 1;
				
			}
		}

		// W 왼쪽
		if (direction[i][j][1]) {
			i_flip = i;
			j_flip = j - 1;	 // 왼쪽  
			while (gameboard[i_flip][j_flip] == opposing_player) {
				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// W 방항 flip[1] 증가 
				flip[1]++;
				
				j_flip -= 1;
			}
		}

		// E 오른쪽
		if (direction[i][j][2]) {
			i_flip = i;
			j_flip = j + 1;	// 오른쪽 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// E 방항 flip[2] 증가
				flip[2]++;
				
				j_flip += 1;
			}
		}

		// S 아래쪽
		if (direction[i][j][3]) {
			i_flip = i + 1;	// 아래쪽 
			j_flip = j;
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// S 방항 flip[3] 증가
				flip[3]++;
				
				i_flip += 1;
			}
		}

		// 대각선 방향 4개: NW, NE, SW, SE 
		// NW
		if (direction[i][j][4]) {
			i_flip = i - 1; // 위쪽 
			j_flip = j - 1;	// 왼쪽 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// NW 방항 flip[4] 증가
				flip[4]++;
				
				i_flip -= 1;
				j_flip -= 1;
			}
		}

		// NE
		if (direction[i][j][5]) {
			i_flip = i - 1; // 위쪽 
			j_flip = j + 1; // 오른쪽 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// NE 방항 flip[5] 증가
				flip[5]++;
				
				i_flip -= 1;
				j_flip += 1;
			}
		}

		// SW
		if (direction[i][j][6]) {
			i_flip = i + 1;	// 아래쪽  
			j_flip = j - 1; // 왼쪽 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// SW 방항 flip[6] 증가
				flip[6]++;
				
				i_flip += 1;
				j_flip -= 1;
			}
		}

		// SE 
		if (direction[i][j][7]) {
			i_flip = i + 1; // 아래쪽  
			j_flip = j + 1; // 오른쪽 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player의 알로 바뀜
				gameboard[i_flip][j_flip] = player;
				// player 점수 증가 
				score[player]++;
				// 상대 player 점수 감소 
				score[opposing_player]--;
				// SE 방항 flip[7] 증가
				flip[7]++;
				
				i_flip += 1;
				j_flip += 1;
			}
		}

	
	}

	void print_flip(){	
		printf("\n\n < flip result >\n");
		// 각 방향의 flip[] 출력 
		printf(" N:%i W:%i E:%i S:%i NW:%i NE:%i SW:%i SE:%i\n", flip[0], flip[1], flip[2], flip[3], flip[4], flip[5], flip[6], flip[7]);
		if(player == WHITE){	// player가 WHITE인 경우
			printf(" White has flipped %i othellos!\n\n", flip[0]+flip[1]+flip[2]+flip[3]+flip[4]+flip[5]+flip[6]+flip[7]);	// 각 방향의 flip[] 모두 더한 만큼 othello는 flipped됨
		} else{					// player가 BLACK인 경우 
			printf(" Black has flipped %i othellos!\n\n", flip[0]+flip[1]+flip[2]+flip[3]+flip[4]+flip[5]+flip[6]+flip[7]);
		}
		
	}

	int position_able(int i, int j){	// 배치가능한 칸이 있는지 확인
	
		// gameboard가 비어있지 않거나 WHITE의 점수가 0 이거나 BLACK의 점수가 0인 경우 배치 불가능 
		if ((gameboard[i][j] != EMPTY) || (score[WHITE] == 0) || (score[BLACK] == 0))
		{
			
			return 0; // 0을 반환
		}
		// 0-5의 범위를 벗어난 경우 배치 불가능 
		if (over_position(i, j) == 0)
		{
			return 0; // 0을 반환
		}
		// 뒤집기가 가능한 칸이 없을 경우 배치 불가능
		/*
		if (able_flip(i, j) == 0)
		{
			return 0; // 0을 반환
		}
		*/
		// 그 외 
		return 1; // 1을 반환
	}

	int place_othello(int othello_row, int othello_column){
		 
		gameboard[othello_row][othello_column] = player;	// 해당위치에 player의 알을 둠 
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

	int print_wrong_input_flip(){	// flip이 불가능한 입력임을 출력 
		printf("invalid input!\n");
		printf("(no flip happens)\n");
	}

	int print_wrong_input_range(){	// 0-5범위를 벗어나는 입력임을 출력 
		printf("invalid input!");
		printf("(should be less than 6)\n");
	}
	
	int main(){
		
		//필요한 변수들 정의
		int row;
		int column;
		int othello_row;
		int othello_column;
		
		othello(); 		// 게임 초기화
				
		while (isGameEnd == 0){ // Game 종료 조건 확인
			print_othello(); 	// 배치 상태, WHITE와 BLACK의 점수  출력
			
			if (position_able(row, column) == 0){ // 배치가능한 칸이 있는지 확인	
										// 비어있는 칸 없음
										// WHITE가 없음
										// BLACK이 없음

										// 뒤집기 가능한 칸이 없음??
										
				isGameEnd = 1; 	// 게임 종료
				continue;	 	// 두 playter 모두 배치가 불가능하면 반복문을 빠져나가야 함
			}
			
			input_othello(&othello_row, &othello_column); 			//배치할 좌표 입력 받기
		
			if (over_position(othello_row, othello_column) == 1){ 	// 입력 좌표가 0-5, 0-5 범위 내에 있어야 함
				
				if (able_flip(othello_row, othello_column)){ 	// 뒤집기 시도
					place_othello(othello_row, othello_column);
					print_flip(); 	// 몇개 뒤집었는지 출력
					change_turn(); 	// 턴 바꿈
				}
				else
					print_wrong_input_flip(); 	// flip이 불가능한 입력임을 출력 
			}
			else
				print_wrong_input_range(); 		// 0-5범위를 벗어나는 입력임을 출력 
					
		}
		
		check_result();		// 결과 출력 

	}

	

