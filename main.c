#define N 6
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define W 0
#define B 1

int gameboard[N][N];

int othello()		// ���� �ʱ�ȭ 
{
	//memset( gameboard, Empty, sizeof( gameboard ) );
	gameboard[(N/2)-1][(N/2)-1] = B; // BLACK
	gameboard[(N/2)+1][(N/2)+1] = B; // BLACK
	gameboard[(N/2)-1][(N/2)+1] = W; // WHITE
	gameboard[(N/2)+1][(N/2)-1] = W; // WHITE
}

int print_othello()	// ��ġ ���� �� �� 
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
	//�ʿ��� ������ ����;
	othello();			// ���� �ʱ�ȭ

	//while (isGameEnd() == 0) {	// Game ���� ���� Ȯ��
		print_othello();			// ��ġ ���� ��� ��
		if (��ġ�� ������ ĭ�� �ִ��� Ȯ��)
				continue;			// �� playter ��� ��ġ�� �Ұ����ϸ� �ݺ����� ���������� ��
			��ġ�� ��ǥ �Է� �ޱ�;
		
		if (�Է� ��ǥ�� �������� üũ)
			if (������ �õ�) {
				� ���������� ���;
				�� �ٲ�;
			}
			else
				�������� �Է����� ���;
			}
		check_result();			// ��� ���
}*/
