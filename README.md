# Advent Of Code 2021

My effort of the [Advent of Code 2021](https://adventofcode.com) contest

### December 1, 2021

Programs:
  * [day01.cpp](src/day01.cpp)
  * [day01e.cpp](src/day01e.cpp)

After having read that someone wrote their own programming language
to solve the Advent of Code, it got me thinking about a specification
language for this kind of puzzles. I wrote [something](https://www.iwriteiam.nl/D2112.html#1)
about it on my website.

### December 2, 2021:

Programs:
  * [day02.cpp](src/day02.cpp)
  * [day02e.cpp](src/day02e.cpp)
  
I had set my alarm at 6 AM [CET] but woke up ten minutes early.
About 6:03, I was ready to start solving todays puzzles. The second
one required some debugging using the sample input.

### December 3, 2021:

Programs:
  * [day03.cpp](src/day03.cpp)
  * [day03e.cpp](src/day03e.cpp)
  
I had set my alarm at 5:50 AM [CET] but in the middle of a dream,
I thought: 'It is time'. I woke up and it was 5:47.
The sources are the raw sources that I used for solving the puzzle,
including all debug statements. Took me about 51 minutes to solve
the puzzles.

Afterwards, I realized that it is also possible to build a counting
tree. In the evening, I wrote this implementation using this:
  * [day03e2.cpp](day03e2.cpp)


### December 4, 2021:

Programs:
  * [day04.cpp](src/day04.cpp)
  * [day04e.cpp](src/day04e.cpp)

I woke way too early. Probably I am taking this a little bit to
serious. It took me 32 minutes to solved the first puzzle and
another 5 to solve the second puzzle.

### December 5, 2021:

Programs:
  * [day05.cpp](src/day05.cpp)
  * [day05e.cpp](src/day05e.cpp)

I woke up just before 5 AM. For the second puzzle, I actually
implemented a more generic algorithm. There was one Boolean
bug in there that took me some time to find.

### December 6, 2021:

Programs:
  * [day06.cpp](src/day06.cpp)
  * [day06e.cpp](src/day06e.cpp)

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

### December 7, 2021:

Programs:
  * [day07.cpp](src/day07.cpp)
  * [day07e.cpp](src/day07e.cpp)

I woke up by the alarm that went of at 5:50 AM (CET).
I just did these puzzle with brute force, not even bothering
to think about the short formulea for adding number 1 to n.
Later, I thought more about it during the day, and came up
with a more efficient solution:
  * [day07_c.cpp](day07_c.cpp)

### December 8, 2021

Program:
 * [Day08.cpp](src/day08.cpp)

I woke up early. I implemented the generic algorithm for
matching the segments, which resulted me in taking a long
time to solve the first puzzle and a relatevily short time
to solve the second. I used a permutation class which I have
been using before in many of [my other programs](https://www.iwriteiam.nl/Programs.html).
At some point, There are two encodings of the digits in
the program, because at some point, I thought that there
was an error in it.

### December 9, 2021

Program:
 * [Day09.cpp](src/day09.cpp)

I woke up by the alarm that went of at 5:50 AM (CET).
For the second puzzle, I used a simple recursive function
to find the basin, asuming that the stack was large enough
to hold the recursion depth. And it worked.

### December 10, 2021

Program:
 * [Day10.cpp](src/day10.cpp)

I woke up a bit early. I decided to use a stack, instead of
recursive calls, for this puzzle. And I think it was the
right choice. It is possible to do it with a recursive
function, but it would require some additional Booleans
to get it working.

During the day, I thought about also calculating the minimum
number of brackets to add to fix every line. The program that
includes an algorithm for this is:
 * [Day10_s.cpp](src/day10_s.cpp) 

### Personal stats

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
 10   00:22:01   4923      0   00:32:37   4057      0
  9   00:12:27   2469      0   00:29:52   1850      0
  8   01:20:30  12650      0   01:23:27   3718      0
  7   00:21:24   8260      0   00:28:08   7030      0
  6   00:34:05   9002      0   00:58:39   6733      0
  5   00:18:14   2156      0   00:29:31   1988      0
  4   00:32:01   2876      0   00:36:50   2211      0
  3   00:13:38   4692      0   00:50:06   5418      0
  2   00:14:44   8720      0   00:26:15   9663      0
  1   01:20:45  11747      0   01:39:14  11235      0

```