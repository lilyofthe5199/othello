#define N 6
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int gameboard[N][N];
void main() {
	//�ʿ��� ������ ����;
	int othello();			// ���� �ʱ�ȭ

	while (isGameEnd() == 0) {	// Game ���� ���� Ȯ��
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
}
