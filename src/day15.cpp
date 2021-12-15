#include <stdio.h>

#define N 100

int field[N][N];

int cost[N][N];

int min(int a, int b) { return a < b ? a : b; }

int main(int argc, char *argv[])
{
	for (int j = 0; j < N; j++)
	{
		char buffer[201];
		fgets(buffer, 200, stdin);
		
		for (int i = 0; i < N; i++)
			field[i][j] = buffer[i] - '0';
	}
	
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
			printf("%d", field[i][j]);
		printf("\n");
	}
	
	//return 0;
	
	/*
	for (int i = 1; i < N; i++)
		cost[i][0] = field[i][0] + cost[i-1][0];

	for (int j = 1; j < N; j++)
		cost[0][j] = field[0][j] + cost[0][j-1];
	
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++)
			cost[i][j] = field[i][j] + min(cost[i-1][j], cost[i][j-1]);
	*/
	/*
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (i == 0 && j == 0) continue;
			int left = i == 0 ? 1000 : cost[i-1][j];
			int top = j == 0 ? 1000 : cost[i][j-1];
			cost[i][j] = field[i][j] + min(left, top);
		}
	*/
	
#define MAX 10000	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cost[i][j] = field[i][j] + MAX;
	cost[0][0] = 0;
	
	for (bool go = true; go; )
	{
		go = false;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (i == 0 && j == 0) continue;
				int left = i == 0 ? MAX : cost[i-1][j];
				int top = j == 0 ? MAX : cost[i][j-1];
				int right = i == N-1 ? MAX : cost[i+1][j];
				int down = j == N-1 ? MAX : cost[i][j+1];
				int v = field[i][j] + min(min(left, right), min(top, down));
				if (v < cost[i][j])
				{
					go = true;
					cost[i][j] = v;
				}
			}
	}
		
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
			printf(" %d:%d", field[i][j], cost[i][j]);
		printf("\n");
	}
	printf("%d\n",cost[N-1][N-1]);
}
	
	