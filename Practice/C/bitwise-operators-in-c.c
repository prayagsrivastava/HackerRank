#include <stdio.h>

int main(void)

{
	printf("hello, world!\n");
}


//clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow    bitwise-operators-in-c.c  -lcrypt -lm -o bitwise-operators-in-c