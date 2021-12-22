#include <stdio.h>

int get_nr(char *&s)
{
	bool min = false;
	if (*s == '-')
	{
		min = true;
		s++;
	}
	long r = 0;
	while ('0' <= *s && *s <= '9')
		r = 10 * r + *s++ - '0';
	if (min)
		r = -r;
	return r;
}	

int minv(long a, long b) { return a < b ? a : b; }
int maxv(long a, long b) { return a > b ? a : b; }

struct Range
{
	long min;
	long max;
	Range() : min(100000), max(-1000000) {}
	Range(int _min, int _max) : min(_min), max(_max) {}
	bool in(int i) { return min <= i && i <= max; }
	bool in(Range &other) { return min <= other.min && other.max <= max; }
	long long size() { return max - min + 1; }
	long overlap(Range &o) { return maxv(0, minv(max, o.max) - maxv(min, o.min) + 1); }
	void join(Range &other)
	{
		if (other.min < min) min = other.min;
		if (other.max > max) max = other.max;
	}
	void intersect(Range &other)
	{
		if (other.min > min) min = other.min;
		if (other.max < max) max = other.max;
	}
	
	void parse(char *&s)
	{
		min = get_nr(s);
		s += 2;
		max = get_nr(s);
	}
};

struct Command
{
	bool skip;
	bool on;
	Range x;
	Range y;
	Range z;
	int overlaps[20];
	int n;
	Command() : on(false), n(0) {}
	long long size() { return x.size() * y.size() * z.size(); }
	
	long overlap(Command &o) { return x.overlap(o.x) * y.overlap(o.y) * z.overlap(o.z); }
	long overlap(Range &ox, Range &oy, Range &oz) { return x.overlap(ox) * y.overlap(oy) * z.overlap(oz); }
};

Command coms[500];
int n = 0;

void printtree(int i, int depth)
{
	printf("%*.*s%d %s\n", 4*depth, 4*depth, "", i, coms[i].on ? "on" : "off");
	for (int j = 0; j < coms[i].n; j++)
		printtree(coms[i].overlaps[j], depth+1);
}

long long countIn(Range &xr, Range &yr, Range zr, int i)
{
/*
	long long o = 0;
	for (; i >= 0 && o == 0; i--)
		o = coms[i].overlap(xr, yr, zr);
	if (o == 0)
		return 0;
*/
	if (i < 0) return 0;
	
	printf("%d %lld %lld %lld\n", i, xr.size(), yr.size(), zr.size());
	long long o = coms[i].overlap(xr, yr, zr);
	if (o == 0)
		return countIn(xr, yr, zr, i-1);

	long long result = coms[i].on ? o : 0;
	result += countIn(xr, yr, zr, i-1);
	Range nxr = xr; nxr.intersect(coms[i].x);
	Range nyr = yr; nyr.intersect(coms[i].y);
	Range nzr = zr; nzr.intersect(coms[i].z);
	result -= countIn(nxr, nyr, nzr, i-1);
	return result;
}

int main(int argc, char *argv[])
{
	Range rx;
	Range ry;
	Range rz;

	char buffer[101];
	while (fgets(buffer, 100, stdin))
	{
		char *s = buffer;
		if (s[1] == 'n')
		{
			coms[n].on = true;
			s += 5;
		}
		else
		{
			coms[n].on = false;
			s += 6;
		}
		coms[n].skip = false;
		coms[n].x.parse(s);
		s += 3;
		coms[n].y.parse(s);
		s += 3;
		coms[n].z.parse(s);
		
		rx.join(coms[n].x);
		ry.join(coms[n].y);
		rz.join(coms[n].z);
		
		//printf("%s x=%ld..%ld,y=%ld..%ld,z=%ld..%ld\n", coms[n].on ? "on" : "off", coms[n].x.min, coms[n].x.max, coms[n].y.min, coms[n].y.max, coms[n].z.min, coms[n].z.max);
		//printf("%ld ", coms[n].size());
		n++;
	}
	printf("\n");
	
	printf("%d x=%ld..%ld,y=%ld..%ld,z=%ld..%ld\n", n, rx.min, rx.max, ry.min, ry.max, rz.min, rz.max);

	for (int i2 = 1; i2 < n; i2++)
	{
		for (int i1 = 0; i1 < i2; i1++)
		{
			long o = coms[i1].overlap(coms[i2]);
			if (o > 0)
			{
				printf("%d %d: %ld", i1, i2, o);
				for (int j = 0; j < i1; j++)
				{
					if (coms[j].overlap(coms[i1]) > 0 && coms[j].overlap(coms[i2]))
						printf(" E %d", j);
				}
				printf("\n");
			}
		}
	}
	
	long long r = countIn(rx, ry, rz, n-1);
	printf("%lld", r);
	
/*	
	for (int i2 = 1; i2 < n; i2++)
	{
		int nr_overlaps = 0;
		for (int i1 = 0; i1 < i2; i1++)
		{
			if (coms[i2].x.in(coms[i1].x) && coms[i2].y.in(coms[i1].y) && coms[i2].z.in(coms[i1].z))
			{
				printf("%d hides %d\n", i2, i1);
				coms[i1].skip = true;
				break;
			}
			if (coms[i2].x.overlap(coms[i1].x) && coms[i2].y.overlap(coms[i1].y) && coms[i2].z.overlap(coms[i1].z))
			{
				//printf("%d:%s overlaps %d:%s\n", i1, coms[i1].on ? "on" : "off", i2, coms[i2].on ? "on" : "off");
				coms[i2].overlaps[coms[i2].n++] = i1;
			}
		}
		if (nr_overlaps == 0)
		{
			printf("%d independ %s\n", i2, coms[i2].on ? "on" : "off");
		}
		//printf("max %d\n", nr_overlaps);
	}
	
	for (int i = 0; i < n; i++)
		if (coms[i].n > 0)
			printtree(i, 0);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < coms[i].n - 1; j++)
			for (int k = j+1; k < coms[i].n; k++)
				if (coms[coms[i].overlaps[j]].overlap(coms[coms[i].overlaps[k]]))
					printf("overlap %d %d %d\n", i, j, k);
	}
				
	return 0;
*/
}

/*
	
	long long count = 0;
	for (int x = -50; x <= +50; x++)
		for (int y = -50; y <= +50; y++)
			for (int z = -50; z <= +50; z++)
			{
				bool on = false;
				for (int i = n; i >= 0; i--)
				{
					if (coms[i].x.in(x) && coms[i].y.in(y) && coms[i].z.in(z))
					{
						on = coms[i].on;
						break;
					}
				}
				if (on)
					count++;
			}
	printf("%lld\n", count);	
*/