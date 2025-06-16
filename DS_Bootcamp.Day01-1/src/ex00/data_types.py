def data_types():
    elements= [3, "word", 4.23,True,[], {}, (), set()]
    arr=[]
    for elem in elements:
        el = type(elem).__name__
        arr.append(el)
    print("[" + ', '.join(arr) + "]")



if __name__ == '__main__':
    data_types()