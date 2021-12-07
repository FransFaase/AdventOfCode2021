#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned long count = 0;
	
	long prev;
	scanf("%ld\n", &prev);
	long cur;
	while (scanf("%ld\n", &cur) > 0)
	{
		if (cur > prev)
			count++;
		prev = cur;
	}
	printf("%ld\n", count);
}