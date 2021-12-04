#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 100

int main(int argc, char *argv[])
{
	char line[1001];

	int numbers[100];
	int nr_numbers = 0;
	fgets(line, 1000, stdin);
	printf("%s", line);
	char *s = line;
	for (;;)
	{
		int nr = 0;
		for (;'0' <= *s && *s <= '9'; s++)
			nr = 10 * nr + *s - '0';
		numbers[nr_numbers++] = nr;
		if (*s != ',')
			break;
		s++;
	}
	
	int boards[100][5][5];
	bool marked[100][5][5];
	
	for (int b = 0; b < N; b++)
	{
		fgets(line, 1000, stdin);
		for (int i = 0; i < 5; i++)
		{
			fgets(line, 1000, stdin);
			char *s = line;
			for (int j = 0; j < 5; j++)
			{
				while (*s == ' ') s++;
				int nr = 0;
				for (;'0' <= *s && *s <= '9'; s++)
					nr = 10 * nr + *s - '0';
				boards[b][i][j] = nr;
				marked[b][i][j] = false;
			}
		}
	}
	
	/*
	for (int b = 0; b < N; b++)
	{
		printf("\n");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				printf("%3d", boards[b][i][j]);
			}
			printf("\n");
		}
	}*/
	
	for (int p = 0; p < nr_numbers; p++)
	{
		int nr = numbers[p];
		printf("draw %d: ", nr);
		
		for (int b = 0; b < N; b++)
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					if (boards[b][i][j] == nr)
						marked[b][i][j] = true;
			bool row = false;
			for (int i = 0; i < 5; i++)
			{
				bool all_marked = true;
				for (int j = 0; j < 5; j++)
					all_marked = all_marked && marked[b][i][j];
				if (all_marked)
					row = true;
			}
			bool col = false;
			for (int j = 0; j < 5; j++)
			{
				bool all_marked = true;
				for (int i = 0; i < 5; i++)
					all_marked = all_marked && marked[b][i][j];
				if (all_marked)
					col = true;
			}
			if (row || col)
			{
				int sum = 0;
				for (int j = 0; j < 5; j++)
					for (int i = 0; i < 5; i++)
						if (!marked[b][i][j])
							sum += boards[b][i][j];
				
				printf("\nWinner is %d %d %d\n", b, sum, nr * sum);
				return 0;
			}
		}
		printf("\n");
	}
}