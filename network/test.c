#include <stdio.h>

int main(int argc, char* argv[])
{
	int i = 0;
	printf("인자갯수 : %d\n", argc);
	printf("실행파일 : %s\n", argv[0]);

	for(i = 1; i <argc; i++)
	{
		printf("추가된인자 : %s\n", argv[i]);
	}
	return 0;
}

