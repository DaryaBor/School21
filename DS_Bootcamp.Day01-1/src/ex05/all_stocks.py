import sys


def print_result(text):
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
    words = text.split(',')
    for word in words:
        flag=0
        word=word.strip()
        for key in COMPANIES:
            if COMPANIES[key].lower()==word.lower():
                print(f"{word} is a ticker symbol for {key}")
                flag=1
            for key, value in COMPANIES.items():
                if word.lower() == key.lower() and flag!=2:  
                    print(f"{key} stock price is {STOCKS[COMPANIES[key]]}")
                    flag=2
        if flag==0:
            print(f"{word} is an unknown company or an unknown ticker symbol")



if __name__ == '__main__':
    text = str(sys.argv[1])
    if ',,' not in text and ','  in text:
        print_result(text)