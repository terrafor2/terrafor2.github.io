#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid = fork();

	if(pid == 0)
	{
		puts("Hi, i am a child process");
	}
	else
	{
		printf("chil process id: %d \n", pid);
	}

	if(pid == 0)
		puts("End child process");
	else
		puts("End parent process");
	return 0;
}

