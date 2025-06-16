import timeit
import random
from collections import Counter

def make_dict_count(numbers):
     return Counter(numbers)
    
def popular_count(numbers):
    return Counter(numbers).most_common(10)

def make_dict(numbers):
    dict_value = {item: 0 for item in numbers}
    for item in numbers:
        if item in dict_value:
            dict_value[item]+=1
    return dict_value

def popular(numbers):
    my_dict=make_dict(numbers)
    sorted_dict = dict(sorted(my_dict.items(), key=lambda item: item[1], reverse=True))
    return list(sorted_dict.items())[:10]

if __name__ == '__main__':
    numbers=[random.randint(0,100) for _ in range(1000000)]
    setup = "from __main__ import make_dict,make_dict_count, popular, popular_count, numbers"
    make_dict_time = timeit.timeit("make_dict(numbers)", setup = setup, number=100)
    make_dict_count_time = timeit.timeit("make_dict_count(numbers)", setup = setup, number=100)
    popular_time = timeit.timeit("popular(numbers)", setup = setup, number=100)
    popular_count_time = timeit.timeit("popular_count(numbers)", setup = setup, number=100)
    print(f"my function: {make_dict_time}")
    print(f"Counter: {make_dict_count_time}")
    print(f"my top: {popular_time}")
    print(f"Counter's top: {popular_count_time}")