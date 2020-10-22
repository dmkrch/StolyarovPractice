#include <stdio.h>

int main(int argc, char* argv[])
{
	char ptr[] = "Hello";

	ptr[3] = 'a';

	printf("%s", ptr);

	return 0;
}
