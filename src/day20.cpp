#include <stdio.h>

#define STEPS 50
#define S 100
#define O (STEPS+2)
#define N (S+2*O)

char field[N][N];
char field2[N][N];

int main(int argc, char *argv[])
{
	char buffer[1001];
	fgets(buffer, 1000, stdin);
	int algo[1000];
	int n = 0;
	for (char *s = buffer; *s == '.' || *s == '#'; s++)
		algo[n++] = *s == '#';
		
	for (int i = 0; i < n; i++)
		printf("%c", algo[i] ? '#' : '.');
	printf("\n\n");
	
	fgets(buffer, 200, stdin);
	
	bool scan[S][S];
	
	for (int j = 0; j < S; j++)
	{
		fgets(buffer, 200, stdin);
		for (int i = 0; i < S; i++)
			scan[i][j] = buffer[i] == '#';
	}
	
	/*
	for (int j = 0; j < S; j++)
	{
		for (int i = 0; i < S; i++)
			printf("%c", scan[i][j] ? '#' : '.');
		printf("\n");
	}
	//*/

	/*	
	int i = 2;
	int j = 2;
	
	int nr = 0;
	for (int j1 = -1; j1 <= 1; j1++)
		for(int i1 = -1; i1 <= 1; i1++)
		{
			nr *= 2;
			printf("%c", scan[i+i1][j+j1] ? '#' : '.');
			if (scan[i+i1][j+j1])
				nr++;
		}
	printf(" %d\n", nr);
	//*/
	
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			field[i][j] = 0;
	
	for (int j = 0; j < S; j++)
		for (int i = 0; i < S; i++)
			field[O+i][O+j] = scan[i][j] ? 1 : 0;
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
			printf("%c", field[i][j] == 1 ? '#' : '.');
		printf("\n");
	}
	
	for (int s = 0; s < STEPS; s++)
	{		
		printf("\n");
		for (int j = 0; j < N; j++)
			for (int i = 0; i < N; i++)
				field2[i][j] = (s + 1) % 2;
				
		for (int j = 1; j < N-1; j++)
		{
			for (int i = 1; i < N-1; i++)
			{
				int nr = 0;
				for (int j1 = -1; j1 <= 1; j1++)
					for(int i1 = -1; i1 <= 1; i1++)
					{
						nr *= 2;
						if (field[i+i1][j+j1] == 1)
							nr++;
					}
				//printf("%4d", nr);
				field2[i][j] = algo[nr] ? 1 : 0;
			}
			//printf("\n");
		}
			
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				field[i][j] = field2[i][j];
				printf("%c", field[i][j] == 1 ? '#' : '.');
				if (field[i][j] == 1)
					count++;
			}
			printf("\n");
		}
		printf("count %d\n", count);
	}
	
}