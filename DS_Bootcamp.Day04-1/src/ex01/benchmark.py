import timeit

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

if __name__ == '__main__':
    emails = 5 * ['john@gmail.com', 'james@gmail.com', 'alice@yahoo.com', 'anna@live.com', 'philipp@gmail.com']
    loop_time = timeit.timeit("loop(emails)", setup = "from __main__ import loop, emails", number=90000000)
    generate_time = timeit.timeit("generate(emails)", setup = "from __main__ import generate, emails", number=90000000)
    map_time = timeit.timeit("map_list(emails)", setup = "from __main__ import map_list, emails", number=90000000)
    time=sorted([loop_time,generate_time, map_time])
    if time[0]==loop_time:
        result="loop"
    elif time[0]==generate_time:
        result="list comprehension"
    elif time[0]==map_time:
        result="map"
    print(f'it is better to use a {result}')
    print(f'{time[0]} vs {time[1]}  vs {time[2]}')
