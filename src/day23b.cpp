#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

//#define SECOND
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
#define HALL_OF_ROOM(R) (ROOMS + 2 + 2 * (R))



void print_state(char *state)
{
	for (int i = 0; i < NR; i++)
		printf("%c", state[i]);
	printf(" ");
}

long price[NR_ROOMS] = { 1, 10, 100, 1000 };

int steps;

bool free_route(char *state, int r, int d, int h)
{
	steps = 1 + d;
	if (d > 0)
	{
		d--;
		if (state[ROOM(r,d)] != '.')
		{
			return false;
		}
	}
	int p = HALL_OF_ROOM(r);
	while (p != h)
	{
		if (state[p] != '.' && state[p] != ' ')
		{
			return false;
		}
		if (p < h)
			p++;
		else
			p--;
		steps++;
	}
	return true;
}

long long expected_cost(char *state)
{
	int nr_correct[4];
	for (int r = 0; r < 4; r++)
	{
		nr_correct[r] = 0;
		for (int d = DEPTH-1; d >= 0; d--)
			if (state[ROOM(r, d)] == 'A' + r)
			{
				nr_correct[r]++;
			}
			else
				break;
	}
	long long result = 0;
	int nr_blocks = 0;
	for (int r = 0; r < 4; r++)
	{
		for (int d = DEPTH-1 - nr_correct[r]; d >= 0; d--)
			if (state[ROOM(r, d)] != '.')
			{
				int tr = state[ROOM(r, d)]-'A';
				int h1 = HALL_OF_ROOM(r);
				int h2 = HALL_OF_ROOM(tr);
				
				int c_l = h1 - ROOMS + h2 - ROOMS;
				int c_r = (NR-1) - h1 + (NR-1) - h2;
				int c = c_l > c_r ? c_l : c_r;
				result += price[tr] * (d + 1 + c + DEPTH - nr_correct[tr]);
			}
	}
	for (int h1 = ROOMS; h1 < NR; h1++)
		if (state[h1] != '.' && state[h1] != ' ')
		{
			int tr = state[h1]-'A';
			int h2 = HALL_OF_ROOM(tr);
			int c = h1 < h2 ? h2 - h1 : h1 - h2;
			result += price[tr] * (c + DEPTH - nr_correct[tr]);
			
		}
	return result;
}

int blockings(char *state)
{
	int nr_correct[4];
	int nr_wrong[4];
	for (int r = 0; r < 4; r++)
	{
		nr_correct[r] = 0;
		for (int d = DEPTH-1; d >= 0; d--)
			if (state[ROOM(r, d)] == 'A' + r)
			{
				nr_correct[r]++;
			}
			else
				break;
		nr_wrong[r] = 0;
		for (int d = DEPTH-1 - nr_correct[r]; d >= 0; d--)
			if (state[ROOM(r, d)] != '.')
				nr_wrong[r]++;
	}
	int nr_blocks = 0;
	for (int r = 0; r < 4; r++)
	{
		for (int d = DEPTH-1 - nr_correct[r]; d >= 0; d--)
			if (state[ROOM(r, d)] != '.')
			{
				int tr = state[ROOM(r, d)]-'A';
				int h1 = HALL_OF_ROOM(r);
				int h2 = HALL_OF_ROOM(tr);
				nr_blocks += nr_wrong[tr];
				for (int d2 = d - 1; d2 >= 0; d2--)
					if (state[ROOM(r, d2)] != '.')
						nr_blocks++;
				for (int h = h1; h != h2;)
				{
					if (state[h] != '.' && state[h] != ' ')
						nr_blocks++;
					if (h < h2)
						h++;
					else
						h--;
				}
			}
	}
	for (int h1 = ROOMS; h1 < NR; h1++)
		if (state[h1] != '.' && state[h1] != ' ')
		{
			int tr = state[h1]-'A';
			int h2 = HALL_OF_ROOM(tr);
			nr_blocks += nr_wrong[tr];
			for (int h = h1; h != h2;)
			{
				if (state[h] != '.' && state[h] != ' ')
					nr_blocks++;
				if (h < h2)
					h++;
				else
					h--;
			}
		}
	return nr_blocks;
}

struct State
{
	char state[NR];
	long cost;
	State *next;
	State *from;
};
State *all_states = 0;

void add_state(char *state, State *from, long cost)
{
	// remove if present and higher cost
	State **ref_state = &all_states;
	for (; (*ref_state) != 0; ref_state = &(*ref_state)->next)
	{
		if (strncmp((*ref_state)->state, state, NR) == 0)
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
}


int main(int argc, char *argv[])
{
	char first_state[NR];	
	for (int i = 0; i < NR; i++)
		first_state[i] = '.';
	for (int r = 0; r < NR_ROOMS; r++)
		first_state[HALL_OF_ROOM(r)] = ' ';
		
	char buffer[30];
	fgets(buffer, 29, stdin);
	fgets(buffer, 29, stdin);
	fgets(buffer, 29, stdin);
	for (int r = 0; r < NR_ROOMS; r++)
		first_state[ROOM(r,0)] = buffer[3 + 2*r];
#ifndef SECOND
	fgets(buffer, 29, stdin);
	for (int r = 0; r < NR_ROOMS; r++)
		first_state[ROOM(r,1)] = buffer[3 + 2*r];
#else		
	for (int r = 0; r < NR_ROOMS; r++)
		first_state[ROOM(r,1)] = "  #D#C#B#A#"[3 + 2*r];
	for (int r = 0; r < NR_ROOMS; r++)
		first_state[ROOM(r,2)] = "  #D#B#A#C#"[3 + 2*r];
	fgets(buffer, 29, stdin);
	for (int r = 0; r < NR_ROOMS; r++)
		first_state[ROOM(r,3)] = buffer[3 + 2*r];
#endif
	//print_state(state);printf("\n");

	add_state(first_state, 0, 0);
	
	
	State *solution = 0;
	
	for (State *cur_state = all_states; cur_state != 0; cur_state = cur_state->next)
	{
		char state[NR];
		for (int i = 0; i < NR; i++)
			state[i] = cur_state->state[i];
#ifndef SECOND
		if (strncmp(state, "AABBCCDD", 8) == 0)
#else
		if (strncmp(state, "AAAABBBBCCCCDDDD", 16) == 0)
#endif
		{
			solution = cur_state;
			break;
		}

		//print_state(state); printf(" %5ld\n", cur_state->cost);

		long cur_cost = cur_state->cost;

		// Try move something out of a room
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
				
				for (int t = ROOMS; t < NR; t++)
					if (state[t] == '.' && free_route(state, r, top_pos, t))
					{
						char new_state[NR];
						for (int i = 0; i < NR; i++)
							new_state[i] = state[i];
						new_state[ROOM(r,top_pos)] = '.';
						new_state[t] = a;
						long new_cost = cur_cost + steps * price[a-'A'];

						// See if we can move something to a room
						for (bool moved_in = true; moved_in;)
						{
							moved_in = false;
							for (int r = 0; r < NR_ROOMS; r++)
							{
								char a = r + 'A';
								int empty_pos = -1;
								bool only_correct = true;
								for (int d = DEPTH-1; d >= 0; d--)
								{
									if (new_state[ROOM(r,d)] == '.') 
									{
										empty_pos = d;
										break;
									}
									if (new_state[ROOM(r,d)] != a)
										only_correct = false;
								}
								if (only_correct)
								{
									for (int f = ROOMS; f < NR && empty_pos >= 0; f++)
										if (new_state[f] == a && free_route(new_state, r, empty_pos, f))
										{
											new_cost += steps * price[r];
											new_state[ROOM(r,empty_pos--)] = a;
											new_state[f] = '.';
											moved_in = true;
										}
									for (int rf = 0; rf < NR_ROOMS && empty_pos >= 0; rf++)
										if (rf != r)
										{
											int d = 0;
											while (d < DEPTH && new_state[ROOM(rf,d)] == '.')
												d++;
											while (d < DEPTH && new_state[ROOM(rf,d)] == a && free_route(new_state, r, empty_pos, HALL_OF_ROOM(rf)))
											{
												new_cost += (steps + d + 1) * price[r];
												new_state[ROOM(r,empty_pos--)] = a;
												new_state[ROOM(rf,d++)] = '.';
												moved_in = true;
											}
										}
								}
							}
						}
						add_state(new_state, cur_state, new_cost);
					}
			}
		}
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
		printf(" (%lld, %d)", s->cost + expected_cost(state), blockings(state));
		printf("\n\n");
	} 
	
	return 0;
}
	