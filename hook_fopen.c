#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

typedef FILE *(*fopen_t)(const char *pathname, const char *mode);
fopen_t real_fopen;

FILE *fopen(const char *pathname, const char *mode) {
  fprintf(stderr, "called fopen(%s, %s)\n", pathname, mode);
  if (!real_fopen) {
    real_fopen = dlsym(RTLD_NEXT, "fopen");
  }

  return real_fopen(pathname, mode);
}

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
/* LD_PRELOAD=./hf.so ./test
run output:
called fopen(a, r)
*/
