import sys

class Research():
        def __init__(self, file):
            self.file = file
            self.calculations = self.Calculations() 

        def file_reader(self, has_header):
                flag=0
                with open(self.file) as f:
                        text= f.readlines()
                        if ',' not in text[0] or len(text[0].split(',')) != 2:
                                has_header=False
                        if(has_header==True):
                                results=[]
                                for line in text[1:]:
                                        if(len(line.split(','))!=2 or ((int(line.split(',')[0])==1 and int(line.split(',')[1])==1 ) or (int(line.split(',')[1])==0 and int(line.split(',')[0])==0 ))):
                                                raise ValueError('Incorrect line')
                                        results.append([int(line.split(',')[0]),int(line.split(',')[1])])
                        else:
                                raise ValueError('Incorrect line')
                    
                        return results
                
        class Calculations():
            def counts(self, results):
                    heads_and_tails = [0, 0]
                    for k in results:
                        if (k[0]==1):
                            heads_and_tails[0]+=1
                        else:
                            heads_and_tails[1]+=1
                    return heads_and_tails          
                    
            def fractions(self, heads_and_tails):
                heads_per = heads_and_tails[0]/12 * 100
                tails_per = heads_and_tails[1]/12 * 100
                return f"{heads_per} {tails_per}"

if __name__ == '__main__':
    m=Research(sys.argv[1])
    has_header=True
    file=m.file_reader(has_header)
    results=m.calculations.counts(file)
    percent =m.calculations.fractions(results)
    print(file)
    print(m.calculations.counts(file))
    print(m.calculations.fractions(results))