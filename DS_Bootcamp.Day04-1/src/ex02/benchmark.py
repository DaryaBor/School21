import timeit
import sys

def loop(emails):
    gmail=[]
    for em in emails:
        if '@gmail' in em:
            gmail.append(em)
    return gmail

def generate(emails):
    gmail=[em for em in emails if  '@gmail' in em]
    return gmail

def map_list(emails):
    gmail=list(map(lambda x: x if '@gmail' in x else None, emails ))
    return gmail

def filter_list(emails):
    gmail=list(filter(lambda x: x if '@gmail' in x else None, emails ))
    return gmail

if __name__ == '__main__':
    if len(sys.argv)==3:
        function  = sys.argv[1]
        times=sys.argv[2]
        functions=["loop", "generate", "map_list", "filter_list"]
        emails = 5 * ['john@gmail.com', 'james@gmail.com', 'alice@yahoo.com', 'anna@live.com', 'philipp@gmail.com']
        if function in functions:
            stmt= f'{function}(emails)'
            setup = f'from __main__ import {function}, emails'
            time = timeit.timeit(stmt, setup = setup, number=int(times))
            print(time)
        else:
            raise Exception("Incorrect name of function")
    else:
        raise Exception("Incorrect number of input values")
