#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset �Լ� ����� ���� �߰��� 

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2 

// gameboard[i][j]
extern char gameboard[N][N];

// direction[i][j][8] 
extern int direction[N][N][8]; // i, j ��ġ���� ���� 8��: N, W, E, S, NW, NE, SW, SE

extern int score[2];	// WHITE�� BLACK�� score
extern int player;
extern int flip[8];
extern int over_position(int row, int column);


	int distance(int i, int j, int i_flip, int j_flip){
		int i_distance;
		int j_distance;

		i_distance = abs(i - i_flip);
		j_distance = abs(j - j_flip);
		
		if (i_distance > 0) {	// i_distance�� 1, 2, 3...�̸�
			return i_distance;	// i_distance ��ȯ 
		}						// i_distance�� 0�̸� 
		return j_distance;		// j_distance ��ȯ
	}


	int able_flip(int i, int j) {	// ������ ������ ĭ�� �ִ��� Ȯ��
		// direction[i][j]�� 0���� �ʱ�ȭ direction�� ������ ��ŭ 
		memset(direction, 0, sizeof(direction));

		int opposing_player = (player + 1) % 2;
		int i_flip;
		int j_flip;

		// ���� 4��: N, W, E, S
		// N ����
		i_flip = i - 1;	// ���� 
		j_flip = j;
		while ((over_position(i_flip, j_flip)==1) && gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1; // 1 �ѹ� �� ���� 
		}
		// �ø� �ϰ��� �ϴ� �������ΰ��� ���� player�� ���� �־���� && ���� player�� �˰� ���ο� �� ������ �Ÿ��� 2���� ũ�ų� ���ƾ���(���޾� ������ �ȵǱ� ������ 1���� Ŀ����)
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][0] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		// W ����
		i_flip = i;
		j_flip = j - 1;	 // ����  
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip -= 1; // 1 �ѹ� �� ����
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][1] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		// E ������
		i_flip = i;
		j_flip = j + 1;	// ������ 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip += 1;// 1 �ѹ� �� ����  
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][2] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		// S �Ʒ���
		i_flip = i + 1;	// �Ʒ��� 
		j_flip = j;
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;// 1 �ѹ� �� ����
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][3] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		// �밢�� ���� 4��: NW, NE, SW, SE 
		// NW
		i_flip = i - 1; // ���� 
		j_flip = j - 1;	// ���� 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;// 1 �ѹ� �� ����
			j_flip -= 1;// 1 �ѹ� �� ����
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][4] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		// NE
		i_flip = i - 1; // ���� 
		j_flip = j + 1; // ������ 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;// 1 �ѹ� �� ����
			j_flip += 1;// 1 �ѹ� �� ����
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][5] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		// SW
		i_flip = i + 1;	// �Ʒ���  
		j_flip = j - 1; // ���� 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;// 1 �ѹ� �� ����
			j_flip -= 1;// 1 �ѹ� �� ����
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][6] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		// SE 
		i_flip = i + 1; // �Ʒ���  
		j_flip = j + 1; // ������ 
		while ((over_position(i_flip, j_flip) == 1) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;// 1 �ѹ� �� ����
			j_flip += 1;// 1 �ѹ� �� ����
		}
		if ((over_position(i_flip, j_flip) == 1) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][7] = 1;
			return 1; // ������ �����ϸ� 1 ��ȯ
		}

		return 0; // ������ �Ұ����ϸ� 0 ��ȯ
	
	}

	int prompt_flip(int i, int j){	// ������ �õ�
		// flip�� 0���� �ʱ�ȭ flip�� ������ ��ŭ 
		memset(flip, 0, sizeof(flip));
		
		// player �� 0 �̸� ������� 1, player�� 1 �̸� ������� 0
		int opposing_player = (player + 1) % 2;
		int i_flip;
		int j_flip;
		
		// ���� 4��: N, W, E, S
		// N ����
		if (direction[i][j][0]) {
			i_flip = i - 1;	// ���� 
			j_flip = j;
			while (gameboard[i_flip][j_flip] == opposing_player){
				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// N ���� flip[0] ���� 
				flip[0]++;
				
				i_flip -= 1;	// 1 �ѹ� �� ����
				
			}
		}

		// W ����
		if (direction[i][j][1]) {
			i_flip = i;
			j_flip = j - 1;	 // ����  
			while (gameboard[i_flip][j_flip] == opposing_player) {
				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// W ���� flip[1] ���� 
				flip[1]++;
				
				j_flip -= 1;	// 1 �ѹ� �� ����
			}
		}

		// E ������
		if (direction[i][j][2]) {
			i_flip = i;
			j_flip = j + 1;	// ������ 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// E ���� flip[2] ����
				flip[2]++;
				
				j_flip += 1;	// 1 �ѹ� �� ���� 
			}
		}

		// S �Ʒ���
		if (direction[i][j][3]) {
			i_flip = i + 1;	// �Ʒ��� 
			j_flip = j;
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// S ���� flip[3] ����
				flip[3]++;
				
				i_flip += 1;	// 1 �ѹ� �� ���� 
			}
		}

		// �밢�� ���� 4��: NW, NE, SW, SE 
		// NW
		if (direction[i][j][4]) {
			i_flip = i - 1; // ���� 
			j_flip = j - 1;	// ���� 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// NW ���� flip[4] ����
				flip[4]++;
				
				i_flip -= 1;	// 1 �ѹ� �� ����
				j_flip -= 1;	// 1 �ѹ� �� ����
			}
		}

		// NE
		if (direction[i][j][5]) {
			i_flip = i - 1; // ���� 
			j_flip = j + 1; // ������ 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// NE ���� flip[5] ����
				flip[5]++;
				
				i_flip -= 1;	// 1 �ѹ� �� ����
				j_flip += 1;	// 1 �ѹ� �� ���� 
			}
		}

		// SW
		if (direction[i][j][6]) {
			i_flip = i + 1;	// �Ʒ���  
			j_flip = j - 1; // ���� 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// SW ���� flip[6] ����
				flip[6]++;
				
				i_flip += 1;	// 1 �ѹ� �� ���� 
				j_flip -= 1;	// 1 �ѹ� �� ����
			}
		}

		// SE 
		if (direction[i][j][7]) {
			i_flip = i + 1; // �Ʒ���  
			j_flip = j + 1; // ������ 
			while (gameboard[i_flip][j_flip] == opposing_player) {

				// player�� �˷� �ٲ�
				gameboard[i_flip][j_flip] = player;
				// player ���� ���� 
				score[player]++;
				// ��� player ���� ���� 
				score[opposing_player]--;
				// SE ���� flip[7] ����
				flip[7]++;
				
				i_flip += 1;	// 1 �ѹ� �� ���� 
				j_flip += 1;	// 1 �ѹ� �� ���� 
			}
		}
	}
	
	void print_flip(){	
		printf("\n\n < flip result >\n");
		// �� ������ flip[] ��� 
		printf(" N:%i W:%i E:%i S:%i NW:%i NE:%i SW:%i SE:%i\n", flip[0], flip[1], flip[2], flip[3], flip[4], flip[5], flip[6], flip[7]);
		if(player == WHITE){	// player�� WHITE�� ���
			printf(" White has flipped %i othellos!\n\n", flip[0]+flip[1]+flip[2]+flip[3]+flip[4]+flip[5]+flip[6]+flip[7]);	// �� ������ flip[] ��� ���� ��ŭ othello�� flipped��
		} else{					// player�� BLACK�� ��� 
			printf(" Black has flipped %i othellos!\n\n", flip[0]+flip[1]+flip[2]+flip[3]+flip[4]+flip[5]+flip[6]+flip[7]);
		}
		
	}
