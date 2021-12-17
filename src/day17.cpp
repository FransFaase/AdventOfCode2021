#include <stdio.h>

int main(int argc, char *argv[])
{
	int tx_min;
	int tx_max;
	int ty_min;
	int ty_max;
	fscanf(stdin, "target area: x=%d..%d, y=%d..%d", &tx_min, &tx_max, &ty_min, &ty_max);
	printf("target area: x=%d..%d, y=%d..%d\n", tx_min, tx_max, ty_min, ty_max);
	
	int highest_hit_y = 0;
	int max_hit_vy = 0;
	for (int i_vy = 0; i_vy < 100; i_vy++)
	{
		for (int i_vx = 0; i_vx < 100; i_vx++)
		{
			int max_y = 0;
			int vx = i_vx;
			int vy = i_vy;
			int x = 0;
			int y = 0;
			bool hit = false;
			while (y >= ty_min && x <= tx_max)
			{
				x += vx;
				y += vy;
				if (y > max_y)
					max_y = y;
				if (vx > 0)
					vx--;
				vy--;
				if (tx_min <= x && x <= tx_max && ty_min <= y && y <= ty_max)
				{
					hit = true;
				}
			}
			//printf("%2d %2d %3d %3d %s %d\n", i_vx, i_vy, x, y, hit ? "hit" : "missed", max_y);
			if (hit)
				max_hit_vy = i_vy;
			if (hit && max_y > highest_hit_y)
				highest_hit_y = max_y;
		}
	}
	printf("%d (%d)\n", highest_hit_y, max_hit_vy);

	int hits = 0;
	for (int i_vy = ty_min; i_vy <= max_hit_vy; i_vy++)
	{
		for (int i_vx = 0; i_vx <= tx_max; i_vx++)
		{
			int max_y = 0;
			int vx = i_vx;
			int vy = i_vy;
			int x = 0;
			int y = 0;
			bool hit = false;
			while (y >= ty_min && x <= tx_max)
			{
				x += vx;
				y += vy;
				if (y > max_y)
					max_y = y;
				if (vx > 0)
					vx--;
				vy--;
				if (tx_min <= x && x <= tx_max && ty_min <= y && y <= ty_max)
				{
					hit = true;
					break;
				}
			}
			//printf("%2d %2d %3d %3d %s %d\n", i_vx, i_vy, x, y, hit ? "hit" : "missed", max_y);
			if (hit)
				hits++;
		}
	}
	printf("hits = %d\n", hits);
}
