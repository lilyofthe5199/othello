#include <stdio.h>
#include <stdlib.h>	
	
	int print_wrong_input_flip(){	// flip이 불가능한 입력임을 출력 
		printf("invalid input!\n");
		printf("(no flip happens)\n");
	}

	int print_wrong_input_range(){	// 0-5범위를 벗어나는 입력임을 출력 
		printf("invalid input!");
		printf("(should be less than 6)\n");
	}
		
