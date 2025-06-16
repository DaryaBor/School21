import sys
import os
import psutil
import time

def read_file(file):
    if not os.path.exists(file):
            raise Exception("Can't open file")
    with open (file, "r") as f:
        return f.readlines()
                
def main(file):
    rows=read_file(file)
    for row in rows:
        pass

    process = psutil.Process(os.getpid())
    memory_usage = process.memory_info().rss / 1024 / 1024 / 1024
    end_time = time.process_time()
    total_time = end_time - start_time
    print(f"Peak Memory Usage = {memory_usage:.3f} GB")
    print(f"User Mode Time + System Mode Time = {total_time:.2f}s")


if __name__ == '__main__':
    start_time = time.process_time()
    if len(sys.argv)==2:
        file  = sys.argv[1]
        main(file)
    else:
        raise Exception("Incorrect number of input values")