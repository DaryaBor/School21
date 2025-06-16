from config import *
from analytics import Research
import os


def main():
    m=Research(input)
    file=m.file_reader(has_header)
    results=m.calculations.counts()
    count = len(file)
    percent =m.calculations.fractions(results)
    parts =  percent.split()
    predict= m.analytic.predict_random(num_of_steps)
    result_list = [sum(x) for x in zip(*predict)]
    # m.analytic.predict_last()
    filled_text = text.format(count, results[0], results[1], float(parts[0]), float(parts[1]), num_of_steps, result_list[0], result_list[1])
    m.analytic.save_file(filled_text, output, 'txt')
#     if not os.path.exists("analytics.log"):
#          message ="The report hasn’t been created due to an error"
       
#     else:
#          message="The report has been successfully created"
#     m.send_messages(token, chat_id)

if __name__ == '__main__':
    main()
   
   