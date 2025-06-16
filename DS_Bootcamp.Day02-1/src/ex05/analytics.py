import sys
from random import randint

class Research():
        def __init__(self, file):
            self.file = file
            self.results = self.file_reader(has_header=True)
            self.calculations = self.Calculations(self.results) 
            self.analytic=self.Analytics(self.results)

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
            def __init__(self, results):
                self.results = results

            def counts(self):
                    heads_and_tails = [0, 0]
                    for k in self.results:
                        if (k[0]==1):
                            heads_and_tails[0]+=1
                        else:
                            heads_and_tails[1]+=1
                    return heads_and_tails          
                    
            def fractions(self, heads_and_tails):
                heads_per = heads_and_tails[0]/12 * 100
                tails_per = heads_and_tails[1]/12 * 100
                return f"{heads_per} {tails_per}"
            
        class Analytics(Calculations):
                
            def predict_random(self, steps):
                    dict={0:[0,1],1:[1,0]}
                    return [dict[randint(0, 1)] for k in range(steps)]
            
            def predict_last(self):
                    return self.results[-1]
            
            def save_file(self, data, name, txt):
                  with open(f'{name}.{txt}', "w") as f:
                        f.write(data)

