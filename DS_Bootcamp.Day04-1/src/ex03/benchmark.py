import timeit
import sys
from functools import reduce

def loop(numbers):
    sum=0
    for i in range(int(numbers)):
        sum=sum+i*i

def reduce_list(numbers):
    return reduce(lambda x, y: x+pow(y,2), [i for i in range(1, int(numbers) + 1)])


if __name__ == '__main__':
    if len(sys.argv)==4:
        function  = sys.argv[1]
        times=sys.argv[2]
        numbers=sys.argv[3]
        functions=["loop", "reduce_list"]
        if function in functions:
            stmt= f'{function}(numbers)'
            setup = f'from __main__ import {function}, numbers'
            time = timeit.timeit(stmt, setup = setup, number=int(times))
            print(time)
        else:
            raise Exception("Incorrect name of function")
    else:
        raise Exception("Incorrect number of input values")
