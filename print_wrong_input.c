#include <stdio.h>
#include <stdlib.h>	
	
	int print_wrong_input_range(){	// 0-5������ ����� �Է����� ��� 
		printf(" invalid input!");
		printf("(should be less than 6)\n");
	}
		
	int print_wrong_input_occupied(){	// �� ������ �ƴ��� ��� 
		printf(" invalid input!");
		printf("(already occupied)\n");
	}
	
	int print_wrong_input_flip(){	// flip�� �Ұ����� �Է����� ��� 
		printf(" invalid input!");
		printf("(no flip happens)\n");
	}
