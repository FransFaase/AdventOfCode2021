#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define S 1000

int field[S][S];

int get_nr(char * &s)
{
	int nr = 0;
	while ('0' <= *s && *s <= '9')
		nr = 10 * nr + *s++ - '0';
	return nr;
}

int main(int argc, char *argv[])
{
	for (int i = 0; i < S; i++)
		for (int j = 0; j < S; j++)
			field[i][j] = 0;
			

	char line[101];
	while (fgets(line, 100, stdin))
	{
		printf("%s", line);
		char *s = line;
		int x1 = get_nr(s);
		s++;
		int y1 = get_nr(s);
		s += 4;
		int x2 = get_nr(s);
		s++;
		int y2 = get_nr(s);
		//printf("%d,%d -> %d,%d\n", x1, y1, x2, y2);
		
		int x = x1;
		int y = y1;
		
		while (x != x2 || y != y2)
		{
			field[x][y]++;
			
			if (x < x2) x++;
			if (x > x2) x--;
			if (y < y2) y++;
			if (y > y2) y--;
		}
		field[x2][y2]++;
	}
	
	/*
	for (int y = 0; y < S; y++)
	{
		for (int x = 0; x < S; x++)
			if (field[x][y] == 0)
				printf(".");
			else
				printf("%d", field[x][y]);
		printf("\n");
	}
	*/

	int count = 0;
	for (int i = 0; i < S; i++)
		for (int j = 0; j < S; j++)
			if (field[i][j] > 1)
				count++;
	printf("%d\n", count);
	
}