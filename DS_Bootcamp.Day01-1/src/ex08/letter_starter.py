import sys

def generate(text):
    with open("employees.tsv", "r") as f2:
        name=text.split(".")[0].capitalize()
        for line in f2:
            if line.split()[0]==name:
                print(f"Dear {name}, welcome to our team. We are sure that it will be a pleasure to work with you. That’s a precondition for the professionals that our company hires.")
            
if __name__ == '__main__':
    text = str(sys.argv[1])
    generate(text)