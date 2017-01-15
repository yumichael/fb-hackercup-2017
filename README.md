# Facebook Hacker Cup 2017

## Qualification Round
Fairly easy problems. The obvious solution is the fastest solution and the one that works.
I used Python for Fight the Zombies because calculating the integers involved in getting the precise probability values
go over the the maximum unsigned long long value. Using C++ would entail using floating point for the intermediate computations;
I am not experienced enough in scientific computing to have any idea what kind of precision loss I might end up having in that case,
so I took the safe route of using Python.

## Round 1
These are damn challenging problems. Not only are the actual solutions not obvious to see, but making the implementation run in
sane space and time also takes some thinking. I submitted Progress Pie and passed. I had no idea how to do Fight the Zombies.
I submitted Manic Moving but did not pass. I am not planning to debug this after the fact at the moment. But the solution in my
head for Manic Moving is the right solution, as taken up in the Facebook post. Finally, I was in the heat of working out
Beach Umbrellas as time ran out. I tested against the Dropbox sample input/output afterwards and passed those tests, 2 hours after
the contest, so if I had taken 2 more hours out of my day to spend on this I would have made the next round.
### Beach Umbrellas
This is one of the most involved piece of software I have ever written. The actual problem solution is the most conceptually simple
out of all the last 3 questions if you have seen that kind of combinatorial technique before, but being able to implement a program
that actually computes the solution takes some effort. Each case can be broken down into finding (N-2)! times a sum ranging over
at most (N choose 2) of the summand (s+N choose s) where s is O(M), all modulo the prime p = 1,000,000,007. I rearranged the result
number by factoring out  1/(N(N-1)) from the sum, resulting in the summand becoming a rising factorial of s going up N numbers
starting at s+1. Now M (up to p-1) is too large to memoize all factorials modulo p up to it. So I did this crazy thing where I
memoized the rising factorials over intervals of length powers of 4 in the range of M. This was an interesting thing to write.
I took care of the division by N(N-1) using a memoized inverse modulo p table found using the Euclidean algorithm
(N's range is small so this is possible). My solution runs in 2 minutes no problem.
