#include <stdio.h>

int dices_c[10];

struct Player
{
	int nr;
	int p;
	int score;
	void print() { printf(" %d, %d, %d", nr, p, score); }
};

long long won[2] = { 0, 0 };


void go(Player *p1, Player *p2, long long n, int depth)
{
	//if (depth == 2) return;
	
	/*
	printf("%*.*sgo", 2*depth, 2*depth, "");
	p1->print();
	printf(" -");
	p2->print();
	printf(" (%lld)\n", n);
	//*/
	for (int i = 3; i <= 9; i++)
	{
		Player np = *p1;
		np.p = (np.p - 1 + i) % 10 + 1;
		np.score += np.p;
		long long nn = n * dices_c[i];
		/*
		printf("%*.*s %d: ", 2*depth, 2*depth, "", i);
		np.print();
		printf("\n");
		//*/
		if (np.score >= 21)
			won[np.nr-1] += nn;
		else
			go(p2, &np, nn, depth + 1);
	}
}

int main(int argc, char *argv[])
{
	int player[2];
	
	char buffer[50];
	fgets(buffer, 49, stdin);
	int s1 = buffer[28] - '0';
	player[0] = s1;
	fgets(buffer, 49, stdin);
	int s2 = buffer[28] - '0';
	player[1] = s2;
	
	printf("%d, %d\n", player[0], player[1]);
	
	int dice = 1;
	long score[2] = { 0, 0 };
	
	int k = 0;
	int nr_rolls = 0;
	
	for (;; k = 1 - k)
	{
		for (int i = 0; i < 3; i++)
		{
			player[k] += dice;
			dice++;
		}
		nr_rolls += 3;
		player[k] = (player[k] - 1) % 10 + 1;
		score[k] += player[k];
		//printf("player %d %ld\n", k + 1, score[k]);
		if (score[k] >= 1000)
		{
			//printf("Player %d won\n", k+1);
			break;
		}
	}
	printf("%ld %d = %ld\n", score[1-k], nr_rolls, score[1-k] * nr_rolls);
	
	// First puzzle again:
	for (int i = 0; i < 10; i++) dices_c[i] = 0;
	for (int i1 = 1; i1 <= 3; i1++)
		for (int i2 = 1; i2 <= 3; i2++)
			for (int i3 = 1; i3 <= 3; i3++)
				dices_c[i1 + i2 + i3]++;
	for (int i = 3; i < 10; i++)
		printf(" %d:%d", i, dices_c[i]);
	printf("\n");

	Player p1;
	p1.nr = 1;
	p1.p = s1;
	p1.score = 0;
	
	Player p2;	
	p2.nr = 2;
	p2.p = s2;
	p2.score = 0;
	go (&p1, &p2, 1, 0);
	
	printf("%lld %lld %lld\n", won[0], won[1], won[0] > won[1] ? won[0] : won[1]);
	
}