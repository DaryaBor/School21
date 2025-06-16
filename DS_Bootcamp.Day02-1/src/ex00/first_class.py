class Must_read:
    file='data.csv'
    with open(file) as f:
        print(f.read())


if __name__ == '__main__':
    Must_read()