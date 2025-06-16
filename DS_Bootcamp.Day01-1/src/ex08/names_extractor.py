import sys

def generate(text):
    with open(text, "r") as f1:
        with open("employees.tsv", "w") as f2:
            f2.write('Name\tSurname\tE-mail\n')
            for line in f1:
                name=line.split(".")[0].capitalize()
                surname = line.split(".")[1].split("@")[0].capitalize()
                f2.write(f"{name}\t{surname}\t{line}")


if __name__ == '__main__':
    text = str(sys.argv[1])
    generate(text)