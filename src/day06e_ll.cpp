#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_nr(char * &s)
{
	int nr = 0;
	while ('0' <= *s && *s <= '9')
		nr = 10 * nr + *s++ - '0';
	return nr;
}


int main(int argc, char *argv[])
{
	long long int foa[9];
	for (int i = 0; i < 9; i++)
		foa[9] = 0;

	char line[10000];
	fgets(line, 10000, stdin);

	
	for (char *s = line; '0' <= *s && *s <= '9'; s++)
	{
		int a = get_nr(s);
		foa[a]++;
	}
	
	for (int d = 0; d < 256; d++)
	{
		long long int spawn = foa[0];
		for (int i = 0; i < 8; i++)
			foa[i] = foa[i+1];
		foa[6] += spawn;
		foa[8] = spawn;
		
		printf("%2d: ", d+1);
		for (int i = 0; i < 9; i++)
			printf("%lld ", foa[i]);
			
		long long int sum = 0;
		for (int i = 0; i < 9; i++)
			sum += foa[i];
		printf("%lld ", sum);
		printf("\n");
	}		
}