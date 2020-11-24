#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset 함수 사용을 위해 추가함 

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2 

// gameboard[i][j]
extern char gameboard[N][N];

// direction[i][j][8] 
extern int direction[N][N][8]; // i, j 위치에서 방향 8개: N, W, E, S, NW, NE, SW, SE

extern int score[2];	// WHITE와 BLACK의 score
extern int player;
extern int flip[8];
extern int over_position(int row, int column);


	int distance(int i, int j, int i_flip, int j_flip){
		int i_distance;
		int j_distance;

		i_distance = abs(i - i_flip);
		j_distance = abs(j - j_flip);
		
		if (i_distance > 0) {	// i_distance가 1, 2, 3...이면
			return i_distance;	// i_distance 반환 
		}						// i_distance가 0이면 
		return j_distance;		// j_distance 반환
	}


	int able_flip(int i, int j) {	// 뒤집기 가능한 칸이 있는지 확인
		// direction[i][j]를 0으로 초기화 direction의 사이즈 만큼 
		memset(direction, 0, sizeof(direction));

		int opposing_player = (player + 1) % 2;
		int i_flip;
		int j_flip;

		// 방향 4개: N, W, E, S
		// N 위쪽
		i_flip = i - 1;	// 위쪽 
		j_flip = j;
		while ((over_position(i_flip, j_flip)==1) && gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1; // 1 한번 더 감소 
		}
		// 플립 하고자 하는 방향으로가면 현재 player의 알이 있어야함 && 현재 player의 알과 새로운 알 사이의 거리가 2보다 크거나 같아야함(연달아 있으면 안되기 때문에 1보다 커야함)
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][0] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		// W 왼쪽
		i_flip = i;
		j_flip = j - 1;	 // 왼쪽  
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip -= 1; // 1 한번 더 감소
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][1] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		// E 오른쪽
		i_flip = i;
		j_flip = j + 1;	// 오른쪽 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip += 1;// 1 한번 더 증가  
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][2] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		// S 아래쪽
		i_flip = i + 1;	// 아래쪽 
		j_flip = j;
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;// 1 한번 더 증가
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][3] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		// 대각선 방향 4개: NW, NE, SW, SE 
		// NW
		i_flip = i - 1; // 위쪽 
		j_flip = j - 1;	// 왼쪽 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;// 1 한번 더 감소
			j_flip -= 1;// 1 한번 더 감소
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][4] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		// NE
		i_flip = i - 1; // 위쪽 
		j_flip = j + 1; // 오른쪽 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;// 1 한번 더 감소
			j_flip += 1;// 1 한번 더 증가
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][5] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		// SW
		i_flip = i + 1;	// 아래쪽  
		j_flip = j - 1; // 왼쪽 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;// 1 한번 더 증가
			j_flip -= 1;// 1 한번 더 감소
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][6] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		// SE 
		i_flip = i + 1; // 아래쪽  
		j_flip = j + 1; // 오른쪽 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;// 1 한번 더 증가
			j_flip += 1;// 1 한번 더 증가
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][7] = 1;
			return 1; // 뒤집기 가능하면 1 반환
		}

		return 0; // 뒤집기 불가능하면 0 반환
	
	}

	int prompt_flip(int i, int j){	// 뒤집기 시도
		// flip을 0으로 초기화 flip의 사이즈 만큼 
		memset(flip, 0, sizeof(flip));
		
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
				
				i_flip -= 1;	// 1 한번 더 감소
				
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
				
				j_flip -= 1;	// 1 한번 더 감소
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
				
				j_flip += 1;	// 1 한번 더 증가 
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
				
				i_flip += 1;	// 1 한번 더 증가 
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
				
				i_flip -= 1;	// 1 한번 더 감소
				j_flip -= 1;	// 1 한번 더 감소
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
				
				i_flip -= 1;	// 1 한번 더 감소
				j_flip += 1;	// 1 한번 더 증가 
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
				
				i_flip += 1;	// 1 한번 더 증가 
				j_flip -= 1;	// 1 한번 더 감소
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
				
				i_flip += 1;	// 1 한번 더 증가 
				j_flip += 1;	// 1 한번 더 증가 
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
