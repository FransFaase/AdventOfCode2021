#include <stdio.h>

#define N 100 //10
#define M 100 //5

int map[M][N];
bool basin[M][N];

int size = 0;

void fill(int i, int j)
{
	if (basin[i][j] || map[i][j] == 9)
		return;
	
	size++;
	basin[i][j] = true;
	if (i > 0) fill(i-1, j);
	if (i < M-1) fill(i+1, j);
	if (j > 0) fill(i,j-1);
	if (j < N-1) fill(i, j+1);
}

int main(int argc, char *argv[])
{
	
	for (int i = 0; i < M; i++)
	{
		char buffer[200];
		fgets(buffer, 200, stdin);
		for (int j = 0; j < N; j++)
			map[i][j] = buffer[j] - '0';
	}
	
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d", map[i][j]);
		printf("\n");
	}
	
	long answer = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (   (i ==   0 || map[i-1][j] > map[i][j])
			    && (i == M-1 || map[i+1][j] > map[i][j])
			    && (j ==   0 || map[i][j-1] > map[i][j])
			    && (j == N-1 || map[i][j+1] > map[i][j]))
			{
				printf("%d,%d = %d\n", i, j, map[i][j]);
				answer += map[i][j] + 1;
			}
		}
	}
	printf("%d\n", answer);

	for (int k = 0; k < M; k++)
		for (int l = 0; l < N; l++)
			basin[k][l] = false;
	answer = 1;
	
	int largest[3];
	int n = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (   (i ==   0 || map[i-1][j] > map[i][j])
			    && (i == M-1 || map[i+1][j] > map[i][j])
			    && (j ==   0 || map[i][j-1] > map[i][j])
			    && (j == N-1 || map[i][j+1] > map[i][j]))
			{
				size = 0;
				fill(i, j);
				
				printf("%d,%d = %d\n", i, j, size);
				if (size > 0)
				{
					for (int l = 0; l < n; l++)
					{
						if (largest[l] < size)
						{
							int s = largest[l];
							largest[l] = size;
							size = s;
						}
					}
					if (n < 4)
						largest[n++] = size;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
		answer *= largest[i];
	printf("%ld\n", answer);
}