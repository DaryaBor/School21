import time 
import requests
from bs4 import BeautifulSoup
import sys
import httpx
import pstats
import profile
import pytest

def test_parse():
    html = resp_req("PLTR")
    result = parse(html, "Basic EPS")
    assert len(result) == 6


def test_tuple():
    html = resp_req("MSFT")
    result = parse(html, "Total Revenue")
    isinstance(result, tuple)


def test_response():
    assert resp_req("PLTR") is not None


def test_get_total():
    html = resp_req("MSFT")
    result = parse(html, "Total Revenue")
    assert result is not None


def test_get_total_error():
    html = resp_req("MSFT")
    with pytest.raises(Exception):
        parse(html, "Total R")


def test_get_response_exception():
    with pytest.raises(Exception):
        resp_req("fhgbf")



def resp_req(ticker):
    my_user_agent = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36 Edg/124.0.0.0"}
    headers = my_user_agent
    path = f"https://finance.yahoo.com/quote/{ticker}/financials/?p={ticker}"
    response = httpx.get(path, headers=headers)
    if "noData yf-wnifss" in response.text or response.status_code != 200:
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
    return result_tuple


if __name__ == "__main__":
    if len(sys.argv) == 3:
            ticker = sys.argv[1]
            row = sys.argv[2]
            get= resp_req(ticker)
            parse(get,row)
    else:
        raise Exception("Incorrect count of arguments")