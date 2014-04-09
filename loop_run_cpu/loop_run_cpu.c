#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
long loop(int num_loops){
	int i, j, k;
	long ret = 0;
	for (i = 0; i < num_loops; ++i){
		for (j = 0; j < 10000; ++j){
			for (k = 0; k < 10000; ++k){
				++ret;
			}
		}
	}
	return ret;
}
int main(int argc, char** argv){
	cpu_set_t mask;
	int num_loops;
	int i;
	long rst;
	if (argc < 2){
		printf("usage: %s <num-loops> <cpu_id0> <cpu_id1>...\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	num_loops = atoi(argv[1]);
	CPU_ZERO(&mask);
	for (i = 2; i <= argc; ++i){
		CPU_SET(atoi(argv[i]), &mask);
	}
	if (0 != sched_setaffinity(0, sizeof(cpu_set_t), &mask)){
		perror("sched_setaffinity");
		exit(EXIT_FAILURE);
	}
	rst = loop(num_loops);
	printf("rst = %ld\n", rst);
	exit(EXIT_SUCCESS);
}
