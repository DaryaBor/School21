import time 
import requests
from bs4 import BeautifulSoup
from random import randint
from selenium import webdriver 
from selenium.webdriver.edge.options import Options 
import sys



def resp_req(path):
    my_user_agent =["Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36 Edg/124.0.0.0"]    
    edge_options = Options() 
    edge_options.add_argument(f"--user-agent={my_user_agent[0]}") 
    edge_options.add_experimental_option('excludeSwitches', ['enable-logging'])
    driver = webdriver.Chrome(options=edge_options) 
    driver.get(path)
    if "noData yf-wnifss" in driver.page_source:
            raise Exception("Unknown ticker")
    time.sleep(5) 
    return driver 

def parse(driver, row):
    soup = BeautifulSoup(driver.page_source, 'html.parser') 
    elem=soup.find_all('div', class_='row lv-0 yf-t22klz')
    result_list = []
    result_list.append(row)
    for el in elem:
        if (el.find('div', class_='rowTitle yf-t22klz').get_text()==row):
            tag1 = el.find_all('div', class_='column yf-t22klz alt')
            tag2 = el.find_all('div', class_='column yf-t22klz')
            for t in tag1 + tag2:
                result_list.append(t.get_text())
        else:
            continue
    if len(result_list)==1:
        raise Exception("Incorrect name of row")
    result_tuple = tuple(result_list)
    print(result_tuple)


if __name__ == "__main__":
    if len(sys.argv) == 3:
            ticker = sys.argv[1]
            row = sys.argv[2]
            path = f"https://finance.yahoo.com/quote/{ticker}/financials/?p={ticker}"
            get= resp_req(path)
            parse(get,row)
    else:
        raise Exception(
                "Incorrect count of arguments")