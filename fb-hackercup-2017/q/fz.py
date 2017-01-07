from collections import namedtuple
from functools import wraps
from math import floor
from itertools import accumulate

class Cache(dict):
    __slots__ = ('function',)

    def __init__(self, function):
        self.function = function
    
    def __getitem__(self, args):
        if not isinstance(args, tuple):
            args = (args,)
        if args not in self:
            super().__setitem__(args, self.function(*args))
        return super().__getitem__(args)

    def __setitem__(self, *args, **kwargs):
        raise TypeError("Cannot set value to Cache object")

def memoized(function):
    '''Use as decorator
    DOES NOT SUPPORT kwargs for function! Will ignore all kwargs.
    '''
    cache = Cache(function)
    @wraps(function)
    def memoized(*args, **kwargs):
        return cache[args]
    memoized.cache = cache
    return memoized

@memoized
def binom(n, m):
    assert(n >= 0)
    if n < m or m < 0:
        return 0
    if m == 0 or n == m:
        return 1
    return binom(n - 1, m - 1) + binom(n - 1, m)
# avoid recursion depth limit by stepping stone computations
binom(100, 50), binom(200, 100)

@memoized
def dicesum1(n, m):
    """distribution of sum of n dice {1,...,m}
    closed form expression, same as dicesum"""
    return [0] + [sum((-1) ** (i % 2) * binom(n, i) * binom(k - i * m - 1, n - 1)
             for i in range(min(floor(k / (m + 1)), n) + 1))
         for k in range(1, n * m + 1)]

@memoized
def dicesum(n, m):
    """distribution of sum of n dice {1,...,m}
    ...the same as dicesum1 but this is probably more sane"""
    if n <= 0:
        return [1]
    sum1 = dicesum(n - 1, m)
    ret = [0 for i in range(n * m + 1)]
    for r in range(1, m + 1):
        for s, c in enumerate(sum1):
            ret[s + r] += c
    return ret

@memoized
def dicesumcum(n, m):
    return list(accumulate(dicesum(n, m)))

def kill_prob(x, y, z, h):
    h = h - z
    c = dicesumcum(x, y)
    if h > len(c) - 1:
        return 0.
    if h <= 0:
        return 1.
    return 1. - c[h - 1] / y ** x

class Spell(namedtuple("Spell", "x y z")):
    def __new__(cls, x, y, z=0):
        # add default values
        return super().__new__(cls, x, y, z)

if __name__ == "__main__":
    in_name = "fighting_the_zombie.txt"
    #in_name = "fighting_the_zombie_example_input.txt"
    out_name = "py_out.txt"
    with open(in_name, 'r') as input:
        n_cases = int(input.readline())
        with open(out_name, 'w') as output:
            for case in range(1, n_cases + 1):
                [h, _] = [int(x) for x in input.readline().strip().split()]
                spells = input.readline().strip().split()
                for i, info in enumerate(spells):
                    spells[i] = Spell(*(int(x) for x in info.replace('d', ' ').replace('+', ' +').replace('-', ' -').split()))
                p = max(kill_prob(s.x, s.y, s.z, h) for s in spells)
                output.write("Case #{}: {:.6f}\n".format(case, p))