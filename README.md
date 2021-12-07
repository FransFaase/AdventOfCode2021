# Advent Of Code 2021

My effort of the [Advent of Code 2021](https://adventofcode.com) contest

### Programs for December 1, 2021

Programs:
  * [day01.cpp](day01.cpp)
  * [day01e.cpp](day01e.cpp)

After having read that someone wrote their own programming language
to solve the Advent of Code, it got me thinking about a specification
language for this kind of puzzles. I wrote [something](https://www.iwriteiam.nl/D2112.html#1)
about it on my website.

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
  1   01:20:45  11747      0   01:39:14  11235      0
```

### December 2, 2021:

Programs:
  * [day02.cpp](day02.cpp)
  * [day02e.cpp](day02e.cpp)
  
I had set my alarm at 6 AM [CET] but woke up ten minutes early.
About 6:03, I was ready to start solving todays puzzles. The second
one required some debugging using the sample input.

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
  2   00:14:44   8720      0   00:26:15   9663      0
```

### December 3, 2021:

Programs:
  * [day03.cpp](day03.cpp)
  * [day03e.cpp](day03e.cpp)
  
I had set my alarm at 5:50 AM [CET] but in the middle of a dream,
I thought: 'It is time'. I woke up and it was 5:47.
The sources are the raw sources that I used for solving the puzzle,
including all debug statements. Took me about 51 minutes to solve
the puzzles.

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
  3   00:13:38   4692      0   00:50:06   5418      0
```
  
Afterwards, I realized that it is also possible to build a counting
tree. In the evening, I wrote this implementation using this:
  * [day03e2.cpp](day03e2.cpp)


### December 4, 2021:

Programs:
  * [day04.cpp](day04.cpp)
  * [day04e.cpp](day04e.cpp)

I woke way too early. Probably I am taking this a little bit to
serious. It took me 32 minutes to solved the first puzzle and
another 5 to solve the second puzzle.

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
  4   00:32:01   2876      0   00:36:50   2211      0
```
  
### December 5, 2021:

Programs:
  * [day05.cpp](day05.cpp)
  * [day05e.cpp](day05e.cpp)

I woke up just before 5 AM. For the second puzzle, I actually
implemented a more generic algorithm. There was one Boolean
bug in there that took me some time to find.


```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
  5   00:18:14   2156      0   00:29:31   1988      0
```

### December 6, 2021:

Programs:
  * [day06.cpp](day06.cpp)
  * [day06e.cpp](day06e.cpp)

I woke up by the alarm that went of at 5:50 AM (CET).
I did not do very well this time. I should have thought about
the puzzle a little longer than I did and realize a little
sooner that you only have to keep a count of the number of
fish of each 'age'. With the second puzzle, I saw some
negative number when using 'long long', so, I implemented
my own big number type. Later, a tried again with 'long long'
and it did work. I guess, I might have used '%ld' instead of
'%lld' in the printf call. Below a cleaned up version of the
program and one that uses 'long long int';
  * [day06e_c.cpp](day06e_c.cpp)
  * [day06e_ll.cpp](day06e_ll.cpp)

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
  6   00:34:05   9002      0   00:58:39   6733      0
```

### December 7, 2021:

Programs:
  * [day07.cpp](day07.cpp)
  * [day07e.cpp](day07e.cpp)

I woke up by the alarm that went of at 5:50 AM (CET).
I just did these puzzle with brute force, not even bothering
to think about the short formulea for adding number 1 to n.
Later, I thought more about it during the day, and came up
with a more efficient solution:
  * [day07_c.cpp](day07_c.cpp)

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
  7   00:21:24   8260      0   00:28:08   7030      0
```
