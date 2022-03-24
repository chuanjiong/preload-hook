# preload-hook

https://tbrindus.ca/correct-ld-preload-hooking-libc/

//usage:

//gcc hook_fopen.c -o hf.so -fPIC -shared -ldl

//g++ test.cpp -o test

//LD_PRELOAD=./hf.so ./test

/* test.cpp

#include <stdio.h>

int main(int argc, char **argv)
{

	FILE *fp = fopen("a", "r");
	
	return 0;
}

*/

/*

LD_PRELOAD=./hf.so ./test

run output:

called fopen(a, r)

*/
