# Advent Of Code 2021

My effort of the [Advent of Code 2021](https://adventofcode.com) contest

### Wednesday, December 1, 2021

Programs:
  * [day01.cpp](src/day01.cpp)
  * [day01e.cpp](src/day01e.cpp)

After having read that someone wrote their own programming language
to solve the Advent of Code, it got me thinking about a specification
language for this kind of puzzles. I wrote [something](https://www.iwriteiam.nl/D2112.html#1)
about it on my website.

### Thursday, December 2, 2021:

Programs:
  * [day02.cpp](src/day02.cpp)
  * [day02e.cpp](src/day02e.cpp)
  
I had set my alarm at 6 AM [CET] but woke up ten minutes early.
About 6:03, I was ready to start solving todays puzzles. The second
one required some debugging using the sample input.

### Friday, December 3, 2021:

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


### Saturday, December 4, 2021:

Programs:
  * [day04.cpp](src/day04.cpp)
  * [day04e.cpp](src/day04e.cpp)

I woke way too early. Probably I am taking this a little bit to
serious. It took me 32 minutes to solved the first puzzle and
another 5 to solve the second puzzle.

### Sunday, December 5, 2021:

Programs:
  * [day05.cpp](src/day05.cpp)
  * [day05e.cpp](src/day05e.cpp)

I woke up just before 5 AM. For the second puzzle, I actually
implemented a more generic algorithm. There was one Boolean
bug in there that took me some time to find.

### Monday, December 6, 2021:

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

### Tuesday, December 7, 2021:

Programs:
  * [day07.cpp](src/day07.cpp)
  * [day07e.cpp](src/day07e.cpp)

I woke up by the alarm that went of at 5:50 AM (CET).
I just did these puzzle with brute force, not even bothering
to think about the short formulea for adding number 1 to n.
Later, I thought more about it during the day, and came up
with a more efficient solution:
  * [day07_c.cpp](day07_c.cpp)

### Wednesday, December 8, 2021

Program:
 * [day08.cpp](src/day08.cpp)

I woke up early. I implemented the generic algorithm for
matching the segments, which resulted me in taking a long
time to solve the first puzzle and a relatevily short time
to solve the second. I used a permutation class which I have
been using before in many of [my other programs](https://www.iwriteiam.nl/Programs.html).
At some point, There are two encodings of the digits in
the program, because at some point, I thought that there
was an error in it.

### Thursday, December 9, 2021

Program:
 * [day09.cpp](src/day09.cpp)

I woke up by the alarm that went of at 5:50 AM (CET).
For the second puzzle, I used a simple recursive function
to find the basin, asuming that the stack was large enough
to hold the recursion depth. And it worked.

### Friday, December 10, 2021

Program:
 * [day10.cpp](src/day10.cpp)

I woke up a bit early. I decided to use a stack, instead of
recursive calls, for this puzzle. And I think it was the
right choice. It is possible to do it with a recursive
function, but it would require some additional Booleans
to get it working.

During the day, I thought about also calculating the minimum
number of brackets to add to fix every line. The program that
includes an algorithm for this is:
 * [day10_s.cpp](src/day10_s.cpp) 

### Saturday, December 11, 2021

Program:
 * [day11.cpp](src/day11.cpp)
 
I woke up a bit early. I was plagued by a one-of-error. (You
can still find it in the commented parts of the code.) This
first made me change the algorithm to accumulate the extra
energy in a separate array called `extra` and apply it after
the flashes had occured. Next, I implemented a recursive
method for applying the flashes, which sounds a bit similar
to the puzzle description. Only then I discovered that there
was a one-of-error. And after I had fixed it, I quickly found
the answers with my input file. Then I reverted many of the
changes, corrected the one-of-error, and verified that the
original algorithm did return the correct answers. See:
 * [day11_f.cpp](src/day11_f.cpp)


### Sunday, December 12, 2021

Program:
 * [day12.cpp](src/day12.cpp)

I woke up by the alarm that went of at 5:50 AM (CET). For
the second puzzle, I at first thought that you could visit
every small cave twice.

During the day, I came up with an extra puzzle. What if
you are allowed to change the 'small' or 'big' status of
each cave. What is the maximum number of paths you can find
(using the rule that one small cave may be visited twice).
The modified version of the program is:
 * [day12_e.cpp](src/day12_e.cpp)

 
### Monday, December 13, 2021

Program:
 * [day13.cpp](src/day13.cpp)

I woke up by the alarm that went of at 5:50 AM (CET). I
struggled a lot to get x and y direction correct.
 
### Tuesday, December 14, 2021

Program:
 * [day14.cpp](src/day14.cpp)

I woke up a bit earlier. After having read the description and
having seen my input (and realize that it was a bit longer),
I quickly decided not to reproduce the polymer, but to count
the number of pairs (matching the rules).
That resulted in me taking to solve the first puzzle a bit longer,
but the second (after changing `long` into `long long`) a bit
quicker.

### Wednesday, December 15, 2021

Program:
 * [day15.cpp](src/day15.cpp)
 * [day15b.cpp](src/day15b.cpp)

Very frustrating puzzle today. I was ready to give up, because I
was totally convinced that my answer was correct. From the example,
I was tricked into believing that path was always going down and
the left. After I visited [the forum](https://www.reddit.com/r/adventofcode),
I realized that nowhere in the description it states this requirement;
the path can also go up and left again. After having fixed this,
I quickly found the correct answers. When I looked at my personal
stats, I noticed that my rank was much lower than expected. I guess
that many others, especially those you are doing it for the first
time, have made the same mistake.

### Thursday,December 16, 2021

Program:
 * [day16.cpp](src/day16.cpp)

I woke up at 5:14. I immediately started writing stream classes.
All in all, it went quite smooth.

### Friday, December 17, 2021

Program:
 * [day17.cpp](src/day17.cpp)

I woke up by the alarm that went of at 5:50 AM (CET). I had no idea
if the brute force method (just scanning a large area) was going to
work, but it did. For the second puzzle I made some attempt to
restrict the search area, using the answer of the first puzzle, but
I wonder if it was really needed.

### Saturday, December 18, 2021

Program:
 * [day18.cpp](src/day18.cpp)
 * [day18b.cpp](src/day18b.cpp)

I woke up by the alarm that went of at 5:50 AM (CET). When starting
to read the problem, I had to think about [surreal numbers](https://en.wikipedia.org/wiki/Surreal_number)
It took me a long time to fix the iterator to walk through the numbers.
Several times, I considered to change to a list of numbers with their depth.
(Maybe that would have made calculating the magnitude a bit harder.)
I did not make any big errors in implementing the explode and split
operation. I did not spend any effort in deleting any of the pairs.

In the days after this, I worked on implementing three more solutions
with different data structures. See [Snailfish numbers](Day18.md).

### Sunday, December 19, 2021

Program:
 * [day19.cpp](src/day19.cpp)

I woke up by the alarm that went of at 5:50 AM (CET). I quickly
understood what this puzzle was about. I decided to test every step
of finding the solution. For the rotations, I borrowed some code
from my [gen_dpfpc](https://www.iwriteiam.nl/Ha_gen_dpfp_c.txt)
program. Because finding the matching between the various beaconds,
took more than a few seconds, I decided to store the data in the program.
To find the matchings, compile the program with `-D PROCESS_INPUT`. I made
use of `grep beacon | sort -u | wc` on the output, to solve the first
puzzle.

### Monday, December 20, 2021

Program:
 * [day20.cpp](src/day20.cpp)

I woke up early. I started about 10 minutes after 5 AM (CET) because
I wanted to update my website first. Being afraid of making a
small mistake, I worked through the example step for step. Only
to discover that my puzzle input (and probably of everyone) had
a little twist, but it was simple to fix. The second puzzle was
not really that hard.

### Tuesday, December 21, 2021

Program:
 * [day21.cpp](src/day21.cpp)
 
I woke up by the alarm that went of at 5:50 AM (CET). This first
puzzle was kind of simple. The second took me some more time. I
decided to first try a recursive approach and it worked in the
end. I struggled a bit with keeping track of the multiplicity of
a universe. I first counted it per player.

### Wednesday, December 22, 2021

Program:
 * [day22.cpp](src/day22.cpp)
 * [day22b.cpp](src/day22b.cpp)

I woke up about ten minutes before the alarm. I did the first
puzzle in a brute force manner. It took me a long time to figure
out how to solve the second puzzle. I think I could not find the
quiescence to solve it. As you can see from the code, I did a
lot of experimentation to find out of the input had certain
properties that would make it easy to solve the problem. A
cleaned up version of the program, which returns both answers, is:
 * [day22_s.cpp](src/day22_s.cpp)

In the evening, I finished improving my puzzle for December 17.
The first puzzle can simple be solved with some analytical reasoning.
The search area for the second puzzle can be reduced substantially.
This is demonstrated in the following program:
 * [day17_s.cpp](src/day17_s.cpp)

### Thursday, December 23, 2021

I do not like this puzzle. I started building some distance
table to figure out the number of steps between all positions.
Then about half an hour in, someone said that the first puzzle
could be done by hand. After some time, I tried this myself.
I found a solution, but when I submitted it was not the shortest.
To rule out that I made an error, I worked on some code to
verify every step. That did not work out. I got more and more
frustrated, trying to write code to find all states. The longer,
I worked, the more I got frustated and stressed, which did not
really help thinking about the code. After about five hours, I
gave up. I realized I was taking this all too serious, adapting
my normal scedule, all because I wanted to stay on top of the
private leaderboard of our company. I decided to quit. I removed
myself from the private leaderboard.

After dinner, I decided to give it a second try, now that I
had calmed down and no longer felt the pressure to compete. I
just managed to find the answers to both puzzles by brute force
expanding the state space until finding the solution. I still
had to get fix a bug in the function (`free_route`) that counted
the steps for getting the second result right. For this I added
so code to print out all the states from the final state back to
the input state. In the mean time, I did think a bit about finding
a method to estimate the 'additional' costs to the final state,
in order to narrow down the search space, but I still have no
idea how to approach it. The program, as it was when I finished
the second puzzle (and with a lot of code commented out that
I wrote earlier) is:
 * [day23.cpp](src/day23.cpp)

### Friday, December 24, 2021

My first approach was to convert the input to a `program.h`
file with equevalent C statement and than include this file
to do a brute-force search. In the mean time, I decided to
try to optimize the code, After some time I decided to use
a `Expr` struct. I also discovered that some expressions
could be simplified when taking in account the range of
possible values. When further studying the code, I noticed
a lot of multiplications and divisions with 26. This lead
me to implement 26-ary expressions in the struct called
`Expr26`. Analyzing the results, it seemed that there were
some restrictions in the input of the MONAD program, but I
could not figure out how. I decided to go back using the
`Expr` struct. I thought I was close to a solution using
the restrictions I had found earlier and implemented an
algorithm to find the answer. I did find an answer, but it
was incorrect. These are the programs with how far I got
today:
 * [day24.cpp](src/day24.cpp)
 * [day24s.cpp](src/day24s.cpp)

### Saturday, December 25, 2021

I got up at the end of the afternoon and had a short look
at the last puzzle and felt it was rather simple, at least
the first puzzle. But I had other obligations during the
day. It was only around nine in the evening, that I start
working on solving the first puzzle of today. It still
took me a little longer than expected: about one and half
hour. The program is:
 * [day25.cpp](src/day25.cpp)

Then I discovered that for solving the second (and
final) puzzle of today, I had to solve yesterdays puzzle.
I merged the two programs I wrote before into one program
and after some fiddling, It generated a program that
contained seven equalities between the fourteen digits.
With this seven equations, I could find the answers to
the first and second puzzle. And with this also get the
last of fifthy stars. The final program for yesterday is:
 * [day24b.cpp](src/day24b.cpp)

## Tuesday, December 28, 2021

In the past days, I continued working on a version for
the puzzle of December 24, that does calculate the answer
all by itself. The result of this, is the program:
 * [day24c.cpp](src/day24c.cpp)

### Personal stats


```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
 25   16:34:20   9301      0   18:03:18   5774      0
 24       >24h   7420      0       >24h   7311      0
 23   15:31:43   8129      0   17:44:30   5809      0
 22   00:33:12   2678      0   03:56:16   2367      0
 21   00:21:17   2234      0   01:26:07   1999      0
 20   00:54:38   1881      0   00:56:45   1689      0
 19   02:57:33   1350      0   03:08:05   1262      0
 18   02:20:41   1880      0   02:31:00   1869      0
 17   00:36:22   2461      0   00:57:56   2892      0
 16   01:05:46   2019      0   01:35:14   2323      0
 15   01:00:38   3927      0   01:16:39   2575      0
 14   00:46:41   7095      0   00:49:08   2148      0
 13   00:50:10   5529      0   00:53:08   4546      0
 12   00:37:55   3454      0   01:05:36   3699      0
 11   00:53:12   4930      0   00:58:02   4831      0
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