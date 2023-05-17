#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	printf("%s\n", envp[1]);
	return 0;
}
