import sys



def finder(ticker):
    COMPANIES = {
    'Apple': 'AAPL',
    'Microsoft': 'MSFT',
    'Netflix': 'NFLX',
    'Tesla': 'TSLA',
    'Nokia': 'NOK'
    }

    STOCKS = {
    'AAPL': 287.73,
    'MSFT': 173.79,
    'NFLX': 416.90,
    'TSLA': 724.88,
    'NOK': 3.37
    }

    flag=0
    for key in COMPANIES:
        if COMPANIES[key]==ticker:
            print(key, STOCKS[ticker])
            flag=1
            return
    if flag==0:
        print("Unknown ticker")
    

if __name__ == '__main__':
    ticker = str(sys.argv[1])
    finder(ticker.upper())