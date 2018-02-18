#include <stdio.h>
#include <stdlib.h>

int stmt_cnt;

void increase(){	
	stmt_cnt++;
}

void print_stmt_cnt(){
	printf("Total instructions executed: %d\n",stmt_cnt);
}

void init(){
	stmt_cnt=0;
	atexit(print_stmt_cnt);
}
