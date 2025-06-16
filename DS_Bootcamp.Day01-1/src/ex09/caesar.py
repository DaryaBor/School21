import sys

def shifr(text, arr):
    result=''
    for word in text:
        if (ord(word)<=90 and ord(word)>=65):
            position= ord(word)-65
            result+=chr((position+arr) % 26 +65)
        if (ord(word)<=122 and ord(word)>=97):
            position= ord(word)-97
            result+=chr((position+arr) % 26 + 97)
        elif  (ord(word)<=127 and ord(word)>=0):
            result+=word
        else:
            raise ValueError("The script does not support your language yet")
    print(result)

if __name__ == '__main__':
    if(len(sys.argv)==4):
        text = str(sys.argv[2])
        if (sys.argv[1]=="encode"):
            shifr(text,int(sys.argv[3]))
        elif (sys.argv[1]=="decode"):
            shifr(text,-int(sys.argv[3]))
        else:
            raise ValueError("Incorrect command")
    else:
        raise ValueError("Incorrect number of arguments")