#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
	intmax_t n;

	n = LONG_MAX;
	printf("n = %ld\n", n);
	n += LONG_MAX;
	printf("n = %ld\n", n);
}
