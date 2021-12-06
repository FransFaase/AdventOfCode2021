#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define S 1000


int get_nr(char * &s)
{
	int nr = 0;
	while ('0' <= *s && *s <= '9')
		nr = 10 * nr + *s++ - '0';
	return nr;
}

#define N 100000

int age[N];
int nr_fish = 0;

int main(int argc, char *argv[])
{
	int foa[9];
	for (int i = 0; i < 9; i++)
		foa[i] = 0;

	char line[10000];
	fgets(line, 100000, stdin);

	
	for (char *s = line; '0' <= *s && *s <= '9'; s++)
	{
		int a = get_nr(s);
		//age[nr_fish++] = a;
		foa[a]++;
		printf("%d,", a);
	}
	printf("\n");
	//for (int i = 0; i < nr_fish; i++)
	//	printf("%d,", age[i]);
	//printf(" ");
	for (int i = 0; i < 9; i++)
		printf("%d ", foa[i]);
	printf("\n");
	
	for (int d = 0; d < 80; d++)
	{
		int new_nr_fish = nr_fish;
		/*
		for (int i = 0; i < nr_fish; i++)
		{
			age[i]--;
			if (age[i] < 0)
			{
				age[i] = 6;
				age[new_nr_fish++] = 8;
				
				if (new_nr_fish > N)
				{
					printf("Error!");
					return 0;
				}
			}
		}
		*/
		
		int spawn = foa[0];
		for (int i = 0; i < 8; i++)
			foa[i] = foa[i+1];
		foa[6] += spawn;
		foa[8] = spawn;
		
		//nr_fish = new_nr_fish;
		printf("%2d: ", d+1);
		//for (int i = 0; i < nr_fish; i++)
		//	printf("%d,", age[i]);
		//printf(" %d |", nr_fish);
		for (int i = 0; i < 9; i++)
			printf("%d ", foa[i]);
		int sum = 0;
		for (int i = 0; i < 9; i++)
			sum += foa[i];
		printf(" %d\n", sum);
	}		
}