#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

#define SECOND
#ifdef SECOND
#define DEPTH 4
#else
#define DEPTH 2
#endif

#define NR_ROOMS 4
#define ROOM(R,D) (DEPTH*(R) + (D))
#define ROOMS (NR_ROOMS * DEPTH)
#define HALLS 11
#define NR (HALLS + ROOMS)

struct State
{
	char state[NR];
	long cost;
	State *next;
	State *from;
};
State *all_states = 0;

State *solution = 0;

void add_state(char *state, State *from, long cost)
{
	// remove if present and higher cost
	State **ref_state = &all_states;
	for (; (*ref_state) != 0; ref_state = &(*ref_state)->next)
	{
		bool equal = true;
		for (int i = 0; i < NR; i++)
			if ((*ref_state)->state[i] != state[i])
			{
				equal = false;
				break;
			}
		if (equal)
		{
			if (cost >= (*ref_state)->cost)
				return;
			(*ref_state) = (*ref_state)->next;
			break;
		}
	}
	// insert at right place
	ref_state = &all_states;
	while ((*ref_state) != 0 && (*ref_state)->cost < cost)
		ref_state = &(*ref_state)->next;
	State *new_state = new State;
	for (int i = 0; i < NR; i++)
		new_state->state[i] = state[i];
	new_state->cost = cost;
	new_state->next = (*ref_state);
	new_state->from = from;
	(*ref_state) = new_state;
#ifndef SECOND
	if (strncmp(state, "AABBCCDD", 8) == 0)
		solution = new_state;
#else
	if (strncmp(state, "AAAABBBBCCCCDDDD", 16) == 0)
		solution = new_state;
#endif
}
	


char state[NR];
void print_state(char *state)
{
/*
	printf("#############\n");
	printf("#%c%c.%c.%c.%c.%c%c#\n", state[0], state[1], state[4], state[7], state[10], state[13], state[14]);
	printf("###%c#%c#%c#%c###\n", state[2], state[5], state[8], state[11]);
	printf("  #%c#%c#%c#%c#\n", state[3], state[6], state[9], state[12]);
	printf("  #########\n");
*/
	for (int i = 0; i < NR; i++)
		printf("%c", state[i]);
	printf(" ");
}

int sum = 0;

bool room(int i) { return i < ROOMS; }
bool hall[NR];

long price[NR_ROOMS] = { 1, 10, 100, 1000 };

int steps;

bool free_route(int r, int d, int h)
{
	//printf("[");
	steps = 1 + d;
	if (d > 0)
	{
		d--;
		//printf("%d|%c ", r, state[r]);
		if (state[ROOM(r,d)] != '.')
		{
			//printf("]");
			return false;
		}
	}
	int p = ROOMS + 2 + 2 * r;
	while (p != h)
	{
		//printf("%d_%c ", p, state[p]);
		if (state[p] != '.' && state[p] != ' ')
		{
			//printf("]");
			return false;
		}
		if (p < h)
			p++;
		else
			p--;
		steps++;
	}
	//printf("!]");
	return true;
}

int top_full_pos(int room)
{
	for (int d = 0; d < DEPTH; d--)
	{
		if (state[ROOM(room, d)] != '.')
			return d;
	}
	return DEPTH;
}

int main(int argc, char *argv[])
{
	for (int i = 0; i < NR; i++)
		hall[i] = !room(i);
	for (int i = 1; i <= NR_ROOMS; i++)
		hall[ROOMS + 2 * i] = false;
	//init_edge();
	
	for (int i = 0; i < NR; i++)
		state[i] = hall[i] ? '.' : ' ';
		
	char buffer[30];
	fgets(buffer, 29, stdin);
	fgets(buffer, 29, stdin);
	fgets(buffer, 29, stdin);
	for (int r = 0; r < NR_ROOMS; r++)
		state[ROOM(r,0)] = buffer[3 + 2*r];
#ifndef SECOND
	fgets(buffer, 29, stdin);
	for (int r = 0; r < NR_ROOMS; r++)
		state[ROOM(r,1)] = buffer[3 + 2*r];
#else		
	for (int r = 0; r < NR_ROOMS; r++)
		state[ROOM(r,1)] = "  #D#C#B#A#"[3 + 2*r];
	for (int r = 0; r < NR_ROOMS; r++)
		state[ROOM(r,2)] = "  #D#B#A#C#"[3 + 2*r];
	fgets(buffer, 29, stdin);
	for (int r = 0; r < NR_ROOMS; r++)
		state[ROOM(r,3)] = buffer[3 + 2*r];
#endif
	//print_state(state);printf("\n");

/*
###C#D#A#B###
  #D#C#B#A#
  #D#B#A#C#
  #B#A#D#C#
CDDBDCBAABADBACC
CDDBDCBAABADBACC
	fgets(buffer, 29, stdin);

*/

	//const char *test = "DACBBCAD.. . . . ..";
	//for (int i = 0; i < NR; i++)
	//	state[i] = test[i];

	add_state(state, 0, 0);
	for (State *cur_state = all_states; cur_state != 0; cur_state = cur_state->next)
	{
		for (int i = 0; i < NR; i++)
			state[i] = cur_state->state[i];
		//print_state(state); printf(" %ld\n", cur_state->cost);
		//printf("  Into room:\n");

		// See if we can move something to a room
		bool moved_in = false;
		for (int r = 0; r < NR_ROOMS; r++)
		{
			char a = r + 'A';
			int empty_pos = -1;
			bool only_correct = true;
			for (int d = DEPTH-1; d >= 0; d--)
			{
				if (state[ROOM(r,d)] == '.') 
				{
					empty_pos = d;
					break;
				}
				if (state[ROOM(r,d)] != a)
					only_correct = false;
			}
			if (empty_pos != -1 && only_correct)
			{
				for (int f = ROOMS; f < NR; f++)
					if (state[f] == a && free_route(r, empty_pos, f))
					{
						char new_state[NR];
						for (int i = 0; i < NR; i++)
							new_state[i] = state[i];
						new_state[ROOM(r,empty_pos)] = a;
						new_state[f] = '.';
						long cost = steps * price[r];						
						add_state(new_state, cur_state, cur_state->cost + cost);
						//printf("I ");print_state(new_state);
						//printf("%d + %d = %d\n", cur_state->cost, cost, cur_state->cost + cost);
						moved_in = true;
					}
			}
		}
		if (moved_in)
			continue;

		// Try move something out of a room
		//printf("  Move out room:\n");
		for (int r = 0; r < NR_ROOMS; r++)
		{
			int empty_pos = -1;
			bool only_correct = true;
			for (int d = DEPTH-1; d >= 0; d--)
			{
				if (state[ROOM(r,d)] == '.')
				{
					empty_pos = d;
					break;
				}
				if (state[ROOM(r,d)] != r + 'A')
					only_correct = false;
			}
			if (!only_correct && empty_pos < DEPTH-1)
			{
				int top_pos = empty_pos + 1;
				char a = state[ROOM(r,top_pos)];
				//printf("%d %d %c\n", only_correct, empty_pos, a);
				
				for (int t = ROOMS; t < NR; t++)
					if (state[t] == '.' && free_route(r, top_pos, t))
					{
						char new_state[NR];
						for (int i = 0; i < NR; i++)
							new_state[i] = state[i];
						new_state[ROOM(r,top_pos)] = '.';
						new_state[t] = a;
						long cost = steps * price[a-'A'];						
						add_state(new_state, cur_state, cur_state->cost + cost);
						//printf("O ");print_state(new_state);
						//printf("%d + %d = %d\n", cur_state->cost, cost, cur_state->cost + cost);
					}
			}
		}
		if (solution != 0);					
	}
	
	
	for (State *s = solution; s != 0; s = s->from)
	{
		char *state = s->state;		
		printf("#############\n");
		printf("#");
		for (int i = ROOMS; i < NR; i++)
			printf("%c", state[i]);
		printf("#\n");
		for (int d = 0; d < DEPTH; d++)
		{
			printf("%s", d == 0 ? "###" : "  #");
			for (int r = 0; r < NR_ROOMS; r++)
				printf("%cX", state[ROOM(r,d)]);
			printf("%s\n", d == 0 ? "##" : "");
		}
		printf("  #########");

		printf(" %ld", s->cost);
		if (s->from)
			printf(" %ld", s->cost - s->from->cost);
		printf("\n\n");
	} 
	
#ifdef BY_HAND	
	/*
	#############
	#...........#
	###C#D#A#B###
	  #B#A#D#C#
	  #########
	*/
	move('A', 8, 0);		
	/*
	#############
	#A ........ #  7
	###C#D# #B###
	  #B#A#D#C#
	  #########
	*/
	move('B', 11, 1);		
	/*
	#############
	#AB........ #  80
	###C#D# # ###
	  #B#A#D#C#
	  #########
	*/
	move('C', 12, 13);		
	/*
	#############
	#AB.......C #  300
	###C#D# # ###
	  #B#A#D# #
	  #########
	*/
	move('D', 9, 12);		
	/*
	#############
	#AB.......C #  7000
	###C# # # ###
	  #B#A#D#D#
	  #########
	*/
	move('D', 5, 11);
	/*
	#############
	#AB.......C #
	###C# # #D###  5000
	  #B#A# #D#
	  #########
	*/
	move('C', 2, 9);		
	/*
	#############
	#AB.......C #
	### # # #D###  700
	  #B#A#C#D#
	  #########
	*/
	move('C', 13, 8);		
	/*
	#############
	#AB.......  #
	### # #C#D###  400
	  #B#A#C#D#
	  #########
	*/
	move('A', 6, 7);		
	/*
	#############
	#AB...A...  #
	### # #C#D###  3 
	  #B# #C#D#
	  #########
	*/
	move('B', 3, 6);		
	/*
	#############
	#AB...A...  #
	### # #C#D###  60
	  # #B#C#D#
	  #########
	*/
	move('B', 1, 5);		
	/*
	#############
	#A ...A...  #  40
	### #B#C#D###
	  # #B#C#D#
	  #########
	*/
	move('A', 7, 3);		
	/*
	#############
	#A ... ...  #  5
	### #B#C#D###
	  #A#B#C#D#
	  #########
	*/
	move('A', 0, 2);		
	/*
	#############
	#  ... ...  #  3
	###A#B#C#D###
	  #A#B#C#D#
	  #########
	*/	
#endif
	return 0;
}

/*
#############
#...........#
###C#D#A#B###
  #B#A#D#C#
  #########
*/
	
/*
#############
#A ........ #  7
###C#D# #B###
  #B#A#D#C#
  #########

#############
#AB........ #  80
###C#D# # ###
  #B#A#D#C#
  #########

#############
#AB.......C #  300
###C#D# # ###
  #B#A#D# #
  #########

#############
#AB.......C #  7000
###C# # # ###
  #B#A#D#D#
  #########

#############
#AB.......C #
###C# # #D###  5000
  #B#A# #D#
  #########

#############
#AB.......C #
### # # #D###  700
  #B#A#C#D#
  #########

#############
#AB.......  #
### # #C#D###  400
  #B#A#C#D#
  #########

#############
#AB...A...  #
### # #C#D###  3 
  #B# #C#D#
  #########

#############
#AB...A...  #
### # #C#D###  60
  # #B#C#D#
  #########

#############
#A ...A...  #  40
### #B#C#D###
  # #B#C#D#
  #########
  
#############
#A ... ...  #  5
### #B#C#D###
  #A#B#C#D#
  #########

#############
#  ... ...  #  3
###A#B#C#D###
  #A#B#C#D#
  #########
  
*/
/*
int move(char a, int f, int t)
{
	bool debug = true;
	if (debug) printf("    ");//print_state();
	if (debug) printf("move %c from %2d to %2d ", a, f, t);
	static int price[4] = { 1, 10, 100, 1000 };
	if (state[f] != a)
	{
		if (debug) printf("ERROR %c not %c\n", state[f], a);
		return -1;
	}
	if (state[t] != '.')
	{
		if (debug) printf("ERROR %c not .\n", state[t]);
		return -1;
	}
	/*
	if (edge[f][t] == UNCONNECTED)
	{
		printf("ERROR illegal\n");
		return -1;
	}
	for (int i = 0; i < NR; i++)
	{
		if ((pass[f][t] & (1 << i)) != 0 && state[i] != '.')
		{
			printf("ERROR %d contain %c\n", i, state[i]);
			return -1;
		}
	}
	* /
	int steps = 1;
	int p = f;
	if (room(p))
	{
		// move from a room
		if ((p % 2) == 1)
		{
			p--;
			if (state[p] != '.')
			{
				if (debug) printf("ERROR top room\n");
				return -1;
			}
			steps++;
		}
		p = ROOMS + p * 2;
		while (p != t)
		{
			if (state[p] != '.')
			{
				if (debug) printf("ERROR blocked\n");
				return -1;
			}
			if (p < t)
				p++;
			else
				p--;
			steps++;
		}
	}
	else
	{
		// move into a room
		if (t / 2 != a - 'A')
		{
			if (debug) printf("ERROR wrong room\n");
			return -1;
		}
		if ((t % 2) == 1)
		{
			if (state[t-1] != '.')
			{
				if (debug) printf("ERROR blocked\n");
				return -1;
			}
			steps++;
		}
		int p1 = ROOMS + t * 2;				
		while (p != p1)
		{
			if (state[p] != '.')
			{
				if (debug) printf("ERROR blocked\n");
				return -1;
			}
			if (p < p1)
				p++;
			else
				p--;
			steps++;
		}
	}			
		
	state[t] = state[f];
	state[f] = '.';
	return price[a - 'A'] * steps;
}
*/


/*

#############
#ab.e.h.k.no#
###c#f#i#l###
  #d#g#j#m#
  #########

abcdefghijklmno
012345678901234
          11111

c,d => a,b,e,h,k,n,o          
  
*/

/*
bool room[19];


int edge[15][15];
long pass[15][15];


void connect(int a, int b, int d) { edge[a][b] = d; edge[b][a] = d; }
#define UNCONNECTED 100

void init_edge()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			edge[i][j] = UNCONNECTED;
			pass[i][j] = 0;
		}
		room[i] = false;
	}
	connect(0, 1, 1);
	for (int k = 1; k <= 10; k += 3)
	{
		connect(k,   k+1, 2);
		connect(k,   k+3, 2);
		connect(k+1, k+3, 2);
		connect(k+1, k+2, 1);
		room[k+1] = true;
		room[k+2] = true;
	}
	connect(13, 14, 1);
	
	// floyds
	for (int j = 0; j < 15; j++)
		for (int i = 0; i < 15; i++)
			for (int k = 0; k < 15; k++)
				if (edge[i][j] + edge[j][k] < edge[i][k])
				{
					edge[i][k] = edge[i][j] + edge[j][k];
					pass[i][k] = pass[i][j] | pass[j][k] | (1 << k);
				}
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (!room[i] && !room[j])
				edge[i][j] = UNCONNECTED;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			if (edge[i][j] == UNCONNECTED)
				printf("   ");
			else
				printf("%3d", edge[i][j]);
		printf("\n");
	}
	printf("----\n");
}
*/	