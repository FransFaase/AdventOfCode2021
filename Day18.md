# Snailfish numbers

[Day 18](https://adventofcode.com/2021/day/18) of Advent of Code 2021
is about Snailfish numbers, which are represented like a tree using
square brackets and have a complex method of adding which consists of
making a combined tree of two numbers and then through 'explosions' and
'splits' reduce the tree to a depth of most four. Both the explosions
and the splits affect numbers on neighbouring leaves (if present) to
make things complicated.

I decided to use a tree representation for [my solution](src/day18.cpp),
but while I was doing this, I several times complementated to use a flat
representation when I was struggling to implement an iterator that walks
over the leaves of the tree. It took me 2:20:41 to finish the first puzzle
and another ten minutes to solve the second puzzle.

Then in the afternoon, I tried to implement the algorithm using an array to
store the numbers together with their depth. But again I struggled and
resorted to implementing an iterator and a builder (kind of output stream)
to implement the explosion and split passes. In the end, it took me even more
time.

Then in the evening, I thought a bit more about it. I realized that the
explosions could be done in one pass. I also realized that a split at depth four,
leads to a single explosion, which combined lead to a 'distrution' of the
value to surrounding values, and which can be done in a single step. splits
at lower levels only lead to more nodes and never to any explosions. I also
realized that with some clever moving around this can also be done in a single
pass. But it would be rather awkward to implement this with arrays (requiring
a lot of copying). So, I turned to a double linked list and implemented a
third solution using the above optimized algorithm.

Both the first and the third solution are making memory allocations and are
thus not very memory efficient. (I did not spend any time on deleting any
allocated memory, as this would require more coding.) I wonder if this could
be done in a smarter way taking into account the fact that Snailfish numbers
are at most four levels deep and thus contain at most 31 nodes and leafs.
The idea is to asume that you have a tree with fullest depth and then you
number the nodes, from left to right, starting with 1. If you decide to use
-1 for the representation of a node or a missing leaf, you only need an
array of 31 integers to represent every possible snailfish number. (I used
an array of size 32 out of convenience.)  With this I implemented the
fourth solution. I tested the solutions on the example input given at the
end of the description for the first puzzle. The code can be found in the
program [day18_4sol.cpp](src/day18_4sol.cpp). With the command line option
`-t`, the program gives some detailed output of all the additions.
