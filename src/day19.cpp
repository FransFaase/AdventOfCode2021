#include <stdio.h>

struct Scanner
{
	int nr;
	int n;
	int ps[30][3];
	int relpos[3];
};
Scanner scanners[40];
int n;

int rot[24][3] = {
   {  1,  2,  3 },
   {  2, -1,  3 },
   { -1, -2,  3 },
   { -2,  1,  3 },
   {  1, -2, -3 },
   {  2,  1, -3 },
   { -1,  2, -3 },
   { -2, -1, -3 },
   {  2,  3,  1 },
   { -3,  2,  1 },
   { -2, -3,  1 },
   {  3, -2,  1 },
   {  2, -3, -1 },
   { -3, -2, -1 },
   { -2,  3, -1 },
   {  3,  2, -1 },
   {  3,  1,  2 },
   { -1,  3,  2 },
   { -3, -1,  2 },
   {  1, -3,  2 },
   {  3, -1, -2 },
   { -1, -3, -2 },
   { -3,  1, -2 },
   {  1,  3, -2 },
};

void apply(int r, int *a, int *b)
{
    for (int j = 0; j < 3; j++)
        if (rot[r][j] < 0)
            b[j] = -a[-rot[r][j]-1];
        else
            b[j] = a[rot[r][j]-1];
}

void forward(int *r, int *a, int *b)
{
    for (int j = 0; j < 3; j++)
    if (r[j] < 0)
        b[j] = -a[-r[j]-1];
    else
        b[j] = a[r[j]-1];
}

void backward(int *r, int *a, int *b)
{
    for (int j = 0; j < 3; j++)
    if (r[j] < 0)
        b[-r[j]-1] = -a[j];
    else
        b[r[j]-1] = a[j];
}

struct Matching
{
	int s1;
	int s2;
	int rot[3];
	int tr[3];
};

#ifdef PROCESS_INPUT
Matching matchings[50];
int nr_m = 0;
#else
Matching matchings[50] = {
{  0,  9, { -1, -3, -2 }, {    -2, -1164,   -41 }},
{  0, 11, {  1, -3,  2 }, {   -27,  -140,  1287 }},
{  0, 29, {  3,  1,  2 }, { -1137,    32,    57 }},
{  1,  4, {  2,  1, -3 }, {  1386,   125,    39 }},
{  1, 25, {  3, -2,  1 }, {   150,  1364,  -100 }},
{  1, 28, { -3, -2, -1 }, {    -1, -1152,    25 }},
{  2, 17, {  2, -1,  3 }, { -1279,    65,   -10 }},
{  2, 30, { -2, -3,  1 }, {    22, -1068,  -105 }},
{  2, 32, {  2,  3,  1 }, {   -70,  1322,   -25 }},
{  3,  5, {  2,  3,  1 }, {    70, -1270,   158 }},
{  3,  7, { -1, -2,  3 }, {  1223,  -103,    75 }},
{  3, 32, {  3, -1, -2 }, { -1097,   -74,   171 }},
{  4,  5, {  1,  3, -2 }, {    36,  -105,  1265 }},
{  4,  7, {  3, -2,  1 }, {   -47,  1062,   112 }},
{  4, 21, { -3, -1,  2 }, {  -117,  -112, -1066 }},
{  4, 33, {  1,  2,  3 }, {  1099,  -152,   120 }},
{  5, 31, { -3, -1,  2 }, {   -78, -1176,   -52 }},
{  6, 18, {  2,  3,  1 }, { -1204,    94,    37 }},
{  6, 28, { -2,  3, -1 }, {   -88,   174, -1172 }},
{  8, 12, { -2, -3,  1 }, {  1171,  -136,  -121 }},
{  8, 16, {  3, -1, -2 }, {   -75,  1223,   -33 }},
{  8, 35, { -1, -3, -2 }, {    66,  -143,  1049 }},
{  8, 36, {  1, -3,  2 }, { -1118,   -91,   -89 }},
{  9, 10, { -1,  3,  2 }, {  1287,   -78,    77 }},
{  9, 19, {  3,  2, -1 }, {   -47, -1232,    10 }},
{ 10, 28, {  3, -2,  1 }, { -1030,   -37,   -36 }},
{ 10, 29, {  3, -1, -2 }, {   152, -1273,   -20 }},
{ 10, 34, { -2,  1,  3 }, {   147,   111,  1201 }},
{ 11, 19, { -3, -2, -1 }, {    72,   -96,  1034 }},
{ 12, 37, {  3, -1, -2 }, {   151, -1185,  -151 }},
{ 13, 27, {  2, -3, -1 }, {  1089,    11,     5 }},
{ 14, 34, { -3, -1,  2 }, {    41,  1089,     9 }},
{ 15, 20, { -2,  3, -1 }, { -1119,   -42,   -80 }},
{ 15, 27, {  1, -2, -3 }, {     8,    56,  1145 }},
{ 15, 29, {  2,  3,  1 }, {  1296,    37,    48 }},
{ 15, 34, { -3, -2, -1 }, {    75,    32, -1336 }},
{ 16, 18, { -1,  2, -3 }, {    21,    71, -1127 }},
{ 16, 24, { -2, -3,  1 }, {   155, -1144,   149 }},
{ 18, 36, { -3, -2, -1 }, { -1293,   -15,   -84 }},
{ 19, 26, {  2,  3,  1 }, { -1326,    26,   -16 }},
{ 22, 37, { -2,  1,  3 }, {  1148,    29,    45 }},
{ 23, 35, { -2, -1, -3 }, {  -100,  1262,   -20 }},
{ 23, 36, {  2,  1, -3 }, { -1238,    78,    32 }},
{ 24, 35, { -1, -3, -2 }, {    -8, -1211,   -62 }},
{ 25, 33, { -3, -1,  2 }, {    19,   140,  1084 }},
{ 28, 36, {  3,  2, -1 }, {    84,  1131,  -164 }},
{ 29, 36, {  2, -3, -1 }, {  -105,   -68, -1346 }},
{ 31, 32, { -3, -1,  2 }, {    -9,  1248,   -91 }},
};
int nr_m = 48;
#endif

void match(Scanner &s1, Scanner &s2)
{
	for (int r = 0; r < 24; r++)
		for (int i1 = 0; i1 < s1.n; i1++)
			for (int i2 = 0; i2 < s2.n; i2++)
			{
				
				int fp[3];
				apply(r, s2.ps[i2], fp);
				
				int tr[3];
				tr[0] = fp[0] - s1.ps[i1][0];
				tr[1] = fp[1] - s1.ps[i1][1];
				tr[2] = fp[2] - s1.ps[i1][2];
				
				int nr_match = 0;
				for (int j2 = 0; j2 < s2.n; j2++)
				{
					int p[3];
					apply(r, s2.ps[j2], p);
					p[0] -= tr[0];
					p[1] -= tr[1];
					p[2] -= tr[2];
					
					for (int j1 = 0; j1 < s1.n; j1++)
						if (s1.ps[j1][0] == p[0] && s1.ps[j1][1] == p[1] && s1.ps[j1][2] == p[2])
						{
							nr_match++;
							break;
						}							
				}					
				
				if (nr_match >= 12)
				{
					printf("%2d %2d ", s1.nr, s2.nr);
					printf("%2d.%2d,%2d ", rot[r][0], rot[r][1], rot[r][2]);
					printf("%5d,%5d.%5d ", tr[0],tr[1],tr[2]);
					printf("%3d %3d %d\n", i1, i2, nr_match);
					matchings[nr_m].s1 = s1.nr;
					matchings[nr_m].s2 = s2.nr;
					matchings[nr_m].rot[0] = rot[r][0];
					matchings[nr_m].rot[1] = rot[r][1];
					matchings[nr_m].rot[2] = rot[r][2];
					matchings[nr_m].tr[0] = tr[0];
					matchings[nr_m].tr[1] = tr[1];
					matchings[nr_m].tr[2] = tr[2];
					nr_m++;
					return;
				}
			}
} 

int pm[50];

int stack[20];
int mstack[20];

void fill_map(int m, int depth)
{
	pm[m]++;
	if (pm[m] > 1)
		return;
	stack[depth++] = m;
	for (int i = 0; i < depth; i++)
		printf("%3d", stack[i]);
	printf("\n");
	
	Scanner &s = scanners[m];
	for (int i = 0; i < s.n; i++)
	{
		int p[3];
		p[0] = s.ps[i][0];
		p[1] = s.ps[i][1];
		p[2] = s.ps[i][2];
		
		//printf("beacon %5d, %5d, %5d", p[0], p[1], p[2]);
		
		for (int d = depth - 2; d >= 0; d--)
		{
			Scanner &fs = scanners[stack[d]];
			Scanner &ts = scanners[stack[d+1]];
			Matching &m = matchings[mstack[d]];
			
			if (stack[d] < stack[d+1])
			{
				int p2[3];
				forward(m.rot, p, p2);
				p[0] = p2[0] - m.tr[0];
				p[1] = p2[1] - m.tr[1];
				p[2] = p2[2] - m.tr[2];
			}
			else
			{
				int p2[3];
				p2[0] = p[0] + m.tr[0];
				p2[1] = p[1] + m.tr[1];
				p2[2] = p[2] + m.tr[2];
				backward(m.rot, p2, p);
			}
		}
		printf("beacon %5d, %5d, %5d\n", p[0], p[1], p[2]);
		//printf("\n");
	}
	// For second puzzle:
	{
		int p[3] = { 0, 0, 0 };
		for (int d = depth - 2; d >= 0; d--)
		{
			Scanner &fs = scanners[stack[d]];
			Scanner &ts = scanners[stack[d+1]];
			Matching &m = matchings[mstack[d]];
			
			if (stack[d] < stack[d+1])
			{
				int p2[3];
				forward(m.rot, p, p2);
				p[0] = p2[0] - m.tr[0];
				p[1] = p2[1] - m.tr[1];
				p[2] = p2[2] - m.tr[2];
			}
			else
			{
				int p2[3];
				p2[0] = p[0] + m.tr[0];
				p2[1] = p[1] + m.tr[1];
				p2[2] = p[2] + m.tr[2];
				backward(m.rot, p2, p);
			}
		}
		printf("relpos %5d, %5d, %5d\n", p[0], p[1], p[2]);
		s.relpos[0] = p[0];
		s.relpos[1] = p[1];
		s.relpos[2] = p[2];
		//printf("\n");
	}	
	for (int i = 0; i < nr_m; i++)
	{
		mstack[depth-1] = i;
		if (matchings[i].s1 == m)
		{
			fill_map(matchings[i].s2, depth);
		}
		if (matchings[i].s2 == m)
		{
			fill_map(matchings[i].s1, depth);
		}
	}
}

int abs(int x) { return x < 0 ? -x : x; }

int main(int argc, char *argv[])
{
	int p[3] = { 4, 5, 6 };
	for (int r = 0; r < 24; r++)
	{
		int p2[3];
		forward(rot[r], p, p2);
		int p3[3];
		backward(rot[r], p2, p3);
		if (p3[0] != 4 || p3[1] != 5 || p3[2] != 6)
		{
			printf("ERROR: %3d %3d %3d\n", p3[0], p3[1], p3[2]);
			return 0;
		}
	}
	
	char buffer[50];
	for (n = 0; fgets(buffer, 49, stdin); n++)
	{
		//printf("Scanner: %s", buffer);
		int i = 0;
		for (; fgets(buffer, 49, stdin); i++)
		{
			if (buffer[0] == '\r' || buffer[0] == '\n')
				break;
			
			scanners[n].nr = n;
			
			char *s = buffer;
			for (int j = 0; j < 3; j++)
			{
				bool minus = false;
				if (*s == '-')
				{
					minus = true;
					s++;
				}
				int v = 0;
				while ('0' <= *s && *s <= '9')
					v = 10 * v + *s++ - '0';
				if (minus)
					v = -v;
				scanners[n].ps[i][j] = v;
				s++;
			}
		}
		scanners[n].n = i;
		//printf("%d\n", n);
	}
	/*
	for (int i = 0; i < n; i++)
	{
		printf("--- scanner %d ---\n", i);
		for (int j = 0; j < scanners[i].n; j++)
			printf("%d,%d,%d\n", scanners[i].ps[j][0], scanners[i].ps[j][1], scanners[i].ps[j][2]);
		printf("\n");
	}
	*/

	if (nr_m == 0)
	{
		for (int i = 0; i < n-1; i++)
			for (int j = i+1; j < n; j++)
				match(scanners[i], scanners[j]);
	}
	
	for (int i = 0; i < nr_m; i++)
	{
		printf("{ %2d, %2d, { %2d, %2d, %2d }, { %5d, %5d, %5d }},\n",
					matchings[i].s1,
					matchings[i].s2,
					matchings[i].rot[0],
					matchings[i].rot[1],
					matchings[i].rot[2],
					matchings[i].tr[0],
					matchings[i].tr[1],
					matchings[i].tr[2]);
	}
	printf("%d\n", nr_m);
	
	/*	
	for (int i = 0; i < n; i++)
		printf(" %d", pm[i]);
	printf("\n");
	*/
	for (int i = 1; i < nr_m; i++)
	{
		/* check transformations */
		Scanner &s1 = scanners[matchings[i].s1];
		Scanner &s2 = scanners[matchings[i].s2];
		int f = 0;
		for (int j = 0; j < s2.n; j++)
		{
			int p2[3];
			forward(matchings[i].rot, s2.ps[j], p2);
			
			p2[0] -= matchings[i].tr[0];
			p2[1] -= matchings[i].tr[1];
			p2[2] -= matchings[i].tr[2];

			for (int j1 = 0; j1 < s1.n; j1++)
			{
				if (s1.ps[j1][0] == p2[0] && s1.ps[j1][1] == p2[1] && s1.ps[j1][2] == p2[2])
				{
					f++;
					break;
				}
			}
			
			int p3[3];			
			p3[0] = p2[0] + matchings[i].tr[0];
			p3[1] = p2[1] + matchings[i].tr[1];
			p3[2] = p2[2] + matchings[i].tr[2];

			int p4[3];
			backward(matchings[i].rot, p3, p4);
			if (p4[0] != s2.ps[j][0] || p4[1] != s2.ps[j][1] || p4[2] != s2.ps[j][2])
			{
				printf("ERROR: ");
				printf("%4d,%4d,%4d", s2.ps[j][0], s2.ps[j][1], s2.ps[j][2]);
				printf("  %4d,%4d,%4d", p2[0], p2[1], p2[2]);
				printf("  %2d", f);
				printf("  %4d,%4d,%4d\n", p4[0], p4[1], p4[2]);
				return 0;
			}
		}
		if (f < 12)
		{
			printf("ERROR %d\n", f);
			return 0;
		}
	}
	for (int i = 0; i < n; i++)
		pm[i] = 0;
	fill_map(0, 0);
	
	int max = 0;
	for (int i1 = 0; i1 < n - 1; i1++)
		for (int i2 = i1 + 1; i2 < n; i2++)
		{
			int d = abs(scanners[i1].relpos[0] - scanners[i2].relpos[0])
				  + abs(scanners[i1].relpos[1] - scanners[i2].relpos[1])
				  + abs(scanners[i1].relpos[2] - scanners[i2].relpos[2]);
			if (d > max)
				max = d;
		}
	printf("%d\n", max);
}