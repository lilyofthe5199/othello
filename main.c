#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// memset �Լ� ����� ���� �߰��� 

#define N 6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define WHITE 0
#define BLACK 1
#define EMPTY 2	// ������� 

// gameboard[i][j]
char gameboard[N][N];

// direction[i][j][8] 
int direction[N][N][8]; // i, j ��ġ���� ���� 8��: N, W, E, S, NW, NE, SW, SE

int score[2];
int player;
int flip[8];
int isGameEnd = 0;

	int othello(){	// ���� �ʱ�ȭ
	
		// gameboard�� EMPTY�� �ʱ�ȭ gameboard�� size ��ŭ 
		memset(gameboard, EMPTY, sizeof(gameboard));
		// WHITE�� �ʱ� ��ġ 
		gameboard[(N / 2) - 1][(N / 2) - 1] = WHITE;
		gameboard[(N / 2)][(N / 2)] = WHITE;
		// BLACK�� �ʱ� ��ġ 
		gameboard[(N / 2) - 1][(N / 2)] = BLACK;
		gameboard[(N / 2)][(N / 2) - 1] = BLACK;
		// WHITE�� BLACK�� ����
		score[WHITE] = 2;
		score[BLACK] = 2;
		// �ʱ� player�� WHITE 
		player = WHITE;
	}
	
	int print_othello(){	// ��ġ ����, WHITE�� BLACK�� ���� ���
	
		// ��ġ ����
		int i;
		int j;
		 
		printf( "\n  0 1 2 3 4 5\n");	// row ��ȣ
	    printf( " -------------\n" );	// row ����
	    for ( i=0; i<N; ++i )
	    {
	        printf( "%i|", i );	// column ��ȣ 
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
	                printf(" "); // ������� 
	            }
	             
	            printf("|");	// column ����
	        }
	        printf( "\n" );
	        printf( " -------------\n" );	// row ����
	    }
	    printf( "\n" );
	   	printf(" STATUS - WHITE: %d, BLACK: %d\n\n", score[WHITE], score[BLACK]);	// WHITE�� BLACK�� ���� ���
	}

	int change_turn(){	// player�� �ٲ۴�.
		// player ���� 0 1 0 1 �ٲ�
		player = (player + 1) % 2;  
	}


	int input_othello(int *othello_row, int *othello_column){	// othello�� �Է� ���� 
		if(player == WHITE){	// player�� WHITE�� ���
			printf(" put a new White othello : ");
			scanf("%i %i", othello_row, othello_column);
		} else{					// player�� BLACK�� ���
			printf(" put a new Black othello : ");
			scanf("%i %i", othello_row, othello_column);
		}
	}

	int over_position(int row, int column){	// �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
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

	int able_flip(int i, int j) {	// ������ ������ ĭ�� �ִ��� Ȯ��
		// direction[i][j]�� 0���� �ʱ�ȭ 8(������ ��)��ŭ 
		memset(direction[i][j], 0, N);

		int opposing_player = (player + 1) % 2;
		int i_flip;
		int j_flip;

		// ���� 4��: N, W, E, S
		// N ����
		i_flip = i - 1;	// ���� 
		j_flip = j;
		while (over_position(i_flip, j_flip) && gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1; // 1 �ѹ� �� ���� 
		}
		// �ø� �ϰ��� �ϴ� �������ΰ��� ���� player�� ���� �־���� && ���� player�� �˰� ���ο� �� ������ �Ÿ��� 2���� ũ�ų� ���ƾ���(1���� Ŀ����)(�´پ� ������ �ȵǱ� ������)
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player)&&(distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][0] = 1;
			return 1; // ������ �����ϴ�
		}

		// W ����
		i_flip = i;
		j_flip = j - 1;	 // ����  
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip -= 1; // 1 �ѹ� �� ����
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][1] = 1;
			return 1; // ������ �����ϴ�
		}

		// E ������
		i_flip = i;
		j_flip = j + 1;	// ������ 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			j_flip +=1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][2] = 1;
			return 1; // ������ �����ϴ�
		}

		// S �Ʒ���
		i_flip = i + 1;	// �Ʒ��� 
		j_flip = j;
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][3] = 1;
			return 1; // ������ �����ϴ�
		}

		// �밢�� ���� 4��: NW, NE, SW, SE 
		// NW
		i_flip = i - 1; // ���� 
		j_flip = j - 1;	// ���� 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;
			j_flip -= 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][4] = 1;
			return 1; // ������ �����ϴ�
		}

		// NE
		i_flip = i - 1; // ���� 
		j_flip = j + 1; // ������ 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip -= 1;
			j_flip += 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][5] = 1;
			return 1; // ������ �����ϴ�
		}

		// SW
		i_flip = i + 1;	// �Ʒ���  
		j_flip = j - 1; // ���� 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {
			i_flip += 1; 
			j_flip -= 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][6] = 1;
			return 1; // ������ �����ϴ�
		}

		// SE 
		i_flip = i + 1; // �Ʒ���  
		j_flip = j + 1; // ������ 
		while (over_position(i_flip, j_flip) &&gameboard[i_flip][j_flip] == opposing_player) {

			i_flip += 1;
			j_flip += 1;
		}
		if (over_position(i_flip, j_flip) &&(gameboard[i_flip][j_flip] == player) && (distance(i, j, i_flip, j_flip) > 1)) {
			direction[i][j][7] = 1;
			return 1; // ������ �����ϴ�
		}

		return 0; // ������ �Ұ����ϸ� 0 ��ȯ
	
	}

	int prompt_flip(int i, int j){	// ������ �õ�
		memset(flip, 0, N);
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
				
				i_flip -= 1;
				
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
				
				j_flip -= 1;
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
				
				j_flip += 1;
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
				
				i_flip += 1;
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
				
				i_flip -= 1;
				j_flip -= 1;
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
				
				i_flip -= 1;
				j_flip += 1;
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
				
				i_flip += 1;
				j_flip -= 1;
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
				
				i_flip += 1;
				j_flip += 1;
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

	int position_able(int i, int j){	// ��ġ������ ĭ�� �ִ��� Ȯ��
	
		// gameboard�� ������� �ʰų� WHITE�� ������ 0 �̰ų� BLACK�� ������ 0�� ��� ��ġ �Ұ��� 
		if ((gameboard[i][j] != EMPTY) || (score[WHITE] == 0) || (score[BLACK] == 0))
		{
			
			return 0; // 0�� ��ȯ
		}
		// 0-5�� ������ ��� ��� ��ġ �Ұ��� 
		if (over_position(i, j) == 0)
		{
			return 0; // 0�� ��ȯ
		}
		// �����Ⱑ ������ ĭ�� ���� ��� ��ġ �Ұ���
		/*
		if (able_flip(i, j) == 0)
		{
			return 0; // 0�� ��ȯ
		}
		*/
		// �� �� 
		return 1; // 1�� ��ȯ
	}

	int place_othello(int othello_row, int othello_column){
		 
		gameboard[othello_row][othello_column] = player;	// �ش���ġ�� player�� ���� �� 
		prompt_flip(othello_row, othello_column);			// flip �õ�
	}
	 
	void check_result(){	
		
		if (score[WHITE] > score[BLACK]){ 			// WHITE ������ �� ����
			printf("White wins.\n");
		} else if (score[WHITE] < score[BLACK]){ 	// BLACK ������ �� ����
			printf("Black wins.\n");
		} else										// WHITE�� BLACK�� ���� ���� 
			printf("Draw game.\n"); 
	}

	int print_wrong_input_flip(){	// flip�� �Ұ����� �Է����� ��� 
		printf("invalid input!\n");
		printf("(no flip happens)\n");
	}

	int print_wrong_input_range(){	// 0-5������ ����� �Է����� ��� 
		printf("invalid input!");
		printf("(should be less than 6)\n");
	}
	
	int main(){
		
		//�ʿ��� ������ ����
		int row;
		int column;
		int othello_row;
		int othello_column;
		
		othello(); 		// ���� �ʱ�ȭ
				
		while (isGameEnd == 0){ // Game ���� ���� Ȯ��
			print_othello(); 	// ��ġ ����, WHITE�� BLACK�� ����  ���
			
			if (position_able(row, column) == 0){ // ��ġ������ ĭ�� �ִ��� Ȯ��	
										// ����ִ� ĭ ����
										// WHITE�� ����
										// BLACK�� ����

										// ������ ������ ĭ�� ����??
										
				isGameEnd = 1; 	// ���� ����
				continue;	 	// �� playter ��� ��ġ�� �Ұ����ϸ� �ݺ����� ���������� ��
			}
			
			input_othello(&othello_row, &othello_column); 			//��ġ�� ��ǥ �Է� �ޱ�
		
			if (over_position(othello_row, othello_column) == 1){ 	// �Է� ��ǥ�� 0-5, 0-5 ���� ���� �־�� ��
				
				if (able_flip(othello_row, othello_column)){ 	// ������ �õ�
					place_othello(othello_row, othello_column);
					print_flip(); 	// � ���������� ���
					change_turn(); 	// �� �ٲ�
				}
				else
					print_wrong_input_flip(); 	// flip�� �Ұ����� �Է����� ��� 
			}
			else
				print_wrong_input_range(); 		// 0-5������ ����� �Է����� ��� 
					
		}
		
		check_result();		// ��� ��� 

	}

	

