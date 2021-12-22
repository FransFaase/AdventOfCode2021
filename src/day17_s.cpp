#include <stdio.h>

int main(int argc, char *argv[])
{
	int tx_min;
	int tx_max;
	int ty_min;
	int ty_max;
	fscanf(stdin, "target area: x=%d..%d, y=%d..%d", &tx_min, &tx_max, &ty_min, &ty_max);

	// It can be assumed that ty_max is smaller than zero
	if (ty_max >= 0)
	{
		printf("ERROR input\n");
		return 0;
	}
	
	// the y moves (by step) as a second degree polynomial.
	// If it starts with a positive speed (vy), than after vy steps
	// it will reach the maximum of vy*(vy+1)/2. After 2*vy steps,
	// y will be zero again and it will have a negative speed of -vy-1.
	// The next value will be -vy-1. If ty_min is larger than -vy-1,
	// then it will drop below the target area, without touching it.
	// From this we can concluse that the maximum value for vy is -ty_min-1.
	
	int max_hit_vy = -ty_min-1;
	printf("Answer: %d\n", -ty_min-1);
	
	// We can simply calculate the number of possibel one time hits:
	int hits = (ty_max - ty_min + 1) * (tx_max - tx_min + 1);
	
	// Now try all left over vertical speeds
	for (int i_vx = 0; i_vx < tx_min; i_vx++)
	{
		// At this vertical speed, can we ever reach the target area
		int max_x = i_vx * (i_vx + 1) / 2;
		if (max_x < tx_min)
			continue;
			
		// calculate the minimal number of steps to get to target area
		int min_s = 0;
		int vx = i_vx;		
		int x = 0;
		while (x < tx_min)
		{
			x += vx;
			vx--;
			min_s++;
		}
		
		// Did it acdentially overshoot the target area?
		if (x > tx_max)
			continue;
			
		printf("%4d: ", i_vx);
		int min_s2 = min_s * (min_s - 1) / 2;
		int vy_min = (ty_min + min_s2) / min_s;
		
		// Look at all possible speeds horizontal speeds
		for (int i_vy = vy_min; i_vy <= max_hit_vy; i_vy++)
		{
			// Based on the minimal number of steps:
			int nx = x;
			int nvx = vx;
			int y = min_s * i_vy - min_s2;
			int yv = i_vy - min_s;
			bool overshoot = false;
			for (;;)
			{
				// If got below the target area, we missed
				if (y < ty_min)
				{
					printf("_");
					break;
				}
	
				// If we are already in the target are, we have a hit
				if (y <= ty_max)
				{
					hits++;	
					printf("#");
					break;
				}
			
				// Continue with next step
				nx += nvx;
				if (nvx > 0)
				{
					// Still have positive speed, we could have overshot
					if (nx > tx_max)
					{
						overshoot = true;
						printf(">");
						break;
					}
					nvx--;
				}
				y += yv;
				yv--;
			}
			
			// If we have overshot, so will for any next larger
			// horizontal speed, because it will take longer to come down
			if (overshoot)
				break;
		}
		printf("\n");
	}
	printf("hits = %d\n", hits);
}
