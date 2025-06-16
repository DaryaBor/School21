import sys
from random import randint
import logging
import requests
from config import token, chat_id

class Research():
        def __init__(self, file):
            self.file = file
            self.results = self.file_reader(has_header=True)
            self.calculations = self.Calculations(self.results) 
            self.analytic=self.Analytics(self.results)

        logging.basicConfig(
        level=logging.INFO, filename="analytics.log", filemode="a",
        format='%(asctime)s %(message)s',
        datefmt='%Y-%m-%d %H:%M:%S'
                )


        def file_reader(self, has_header):
                flag=0
                try:
                        with open(self.file) as f:
                                text= f.readlines()
                                if ',' not in text[0] or len(text[0].split(',')) != 2:
                                        has_header=False
                                        logging.error('Incorrect line')
                                if(has_header==True):
                                        results=[]
                                        for line in text[1:]:
                                                if(len(line.split(','))!=2 or ((int(line.split(',')[0])==1 and int(line.split(',')[1])==1 ) or (int(line.split(',')[1])==0 and int(line.split(',')[0])==0 ))):
                                                        logging.error('Incorrect line or duplicate values')
                                                        raise ValueError('Incorrect line')
                                                else:
                                                        results.append([int(line.split(',')[0]),int(line.split(',')[1])])
                                else:
                                        logging.error('Incorrect file')
                                        raise ValueError('Incorrect line')
                except Exception:
                        logging.error("File hasn't been read")
                        self.send_messages(token, chat_id,False)
                        raise
                self.send_messages(token,chat_id,True)
                return results
                
        def send_messages(self,token, chat_id, status):
                message =  'The report has been successfully created' if status else "The report hasn’t been created due to an error"
                url = f"https://api.telegram.org/bot{token}/sendMessage"
                payload = {
                'chat_id': chat_id,
                'text': message
                }
                response = requests.post(url, json=payload)
                return response.json()
                
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
                    logging.info('Counting heads and tails')
                    return heads_and_tails          
                    
            def fractions(self, heads_and_tails):
                heads_per = heads_and_tails[0]/12 * 100
                tails_per = heads_and_tails[1]/12 * 100
                logging.info('Counting fractions')
                return f"{heads_per} {tails_per}"
            
        class Analytics(Calculations):
                
            def predict_random(self, steps):
                    dict={0:[0,1],1:[1,0]}
                    logging.info('Predicting values')
                    return [dict[randint(0, 1)] for k in range(steps)]
            
            def predict_last(self):
                    logging.info('Typing last value')
                    return self.results[-1]
            
            def save_file(self, data, name, txt):
                  with open(f'{name}.{txt}', "w") as f:
                        f.write(data)
                  logging.info('Saving file')

