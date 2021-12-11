#include <stdio.h>

int main(int argc, char *argv[])
{
	int energy[10][10];
	for (int i = 0; i < 10; i++)
	{
		char buffer[20];
		fgets(buffer, 19, stdin);
		for (int j = 0; j < 10; j++)
			energy[i][j] = buffer[j] - '0';
	}
	
	long total_flashes = 0;
	for (int step = 0; ; step++)
	{
		bool flashed[10][10];
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				energy[i][j]++;
				flashed[i][j] = false;
			}
			
		int flashes = 0;
		bool go = true;
		while (go)
		{
			go = false;
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					if (energy[i][j] > 9 && !flashed[i][j])
					{
						flashes++;
						flashed[i][j] = true;
						for (int i1 = i-1; i1 <= i+1; i1++) if (i1 >= 0 && i1 < 10)
							for (int j1 = j-1; j1 <= j+1; j1++) if (j1 >= 0 && j1 < 10)
								if (i1 != i || j1 != j)
									energy[i1][j1]++;
						go = true;
					}
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (energy[i][j] > 9)
					energy[i][j] = 0;
				printf("%c", energy[i][j] + '0');
			}
			printf("\n");
		}
		printf("\nflashes = %d\n\n", flashes);
		if (step < 100)
			total_flashes += flashes;
		if (flashes == 100)
		{
			printf("first = %d\n", step + 1);
			break;
		}
;
	}
	printf("total = %ld\n", total_flashes);
}
			
			