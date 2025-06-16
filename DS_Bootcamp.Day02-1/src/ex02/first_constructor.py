import sys

class Research:
        def __init__(self, file):
                self.file = file

        def file_reader(self):
                flag=0
                with open(self.file) as f:
                        text= f.readlines()
                        if ',' in text[0]:
                                if len(text[0].split(',')) == 2:
                                       flag=1
                        if(flag==1):
                                for line in text[1:]:
                                        if(len(line.split(','))!=2 or ((int(line.split(',')[0])==1 and int(line.split(',')[1])==1 ) or (int(line.split(',')[1])==0 and int(line.split(',')[0])==0 ))):
                                                raise ValueError('Incorrect line')
                        else:
                                raise ValueError('Incorrect line')
                        full_text = ''.join([line.strip() for line in text])
                        return ''.join(text)

if __name__ == '__main__':
    m=Research(sys.argv[1])
    print(m.file_reader())