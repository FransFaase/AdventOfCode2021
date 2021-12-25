#include <stdio.h>

#define ROWS 137
#define COLS 139

char field[ROWS][COLS];

int main(int argc, char *argv[])
{
	for (int r = 0; r < ROWS; r++)
	{
		char buffer[COLS+5];
		fgets(buffer, COLS+4, stdin);
		for (int c = 0; c < COLS; c++)
			field[r][c] = buffer[c];
	}

	int steps = 1;	
	for (bool move = true; move;)
	{
		move = false;
		
		for (int r = 0; r < ROWS; r++)
		{
			for (int c = 0; c < COLS; c++)
				printf("%c", field[r][c]);
			printf("\n");
		}
		printf("\n");

		// East facing
		for (int r = 0; r < ROWS; r++)
		{
			bool first_full = field[r][0] != '.';
			int c_last = 0;
			for (int c = 0; c < COLS-1; c++)
				if (field[r][c] == '>' && field[r][c+1] == '.')
				{
					move = true;
					field[r][c] = '.';
					field[r][c+1] = '>';
					c++;
					c_last = c;
				}
			if (c_last != COLS-1 && field[r][COLS-1] == '>' && !first_full)
			{
				field[r][COLS-1] = '.';
				field[r][0] = '>';
			}
		}
		
		// South facing
		for (int c = 0; c < COLS; c++)
		{
			bool first_full = field[0][c] != '.';
			int r_last = 0;
			for (int r = 0; r < ROWS-1; r++)
				if (field[r][c] == 'v' && field[r+1][c] == '.')
				{
					move = true;
					field[r][c] = '.';
					field[r+1][c] = 'v';
					r++;
					r_last = r;
				}
			if (r_last != ROWS-1 && field[ROWS-1][c] == 'v' && !first_full)
			{
				field[ROWS-1][c] = '.';
				field[0][c] = 'v';
			}
		}
		if (move)
			steps++;
	}
	printf("%d\n", steps);
}
