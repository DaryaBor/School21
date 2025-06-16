def read(input, output):
    replacements = {'false,': 'false\t', 'true,': 'true\t', '",': '"\t'}
    with open(input, "r") as f1:
        with open(output, "w") as f2:
            for line in f1: 
                for old, new in replacements.items():
                    line = line.replace(old, new)
                f2.write(line)


if __name__ == '__main__':
    input = 'ds.csv'
    output = 'ds.tsv'
    read(input, output)