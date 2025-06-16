import time 
import requests
from bs4 import BeautifulSoup
import sys
import httpx
import pstats
import profile


def resp_req(path):
    my_user_agent = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36 Edg/124.0.0.0"}
    headers = my_user_agent
    response = httpx.get(path, headers=headers)

    
    if "noData yf-wnifss" in response.text:
        raise Exception("Unknown ticker")
    return response 

def parse(html, row):
    soup = BeautifulSoup(html.text, 'html.parser')
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
            p = profile.Profile()
            p.run("resp_req(path);parse(resp_req(path),row)")
            s = pstats.Stats(p)
            s.sort_stats("cumtime").print_stats(5)
    else:
        raise Exception("Incorrect count of arguments")