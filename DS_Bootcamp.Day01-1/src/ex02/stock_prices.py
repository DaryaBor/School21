import sys



def finder(comp):
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
    comp = comp[0].upper()+comp[1:]
    if comp in COMPANIES:
        print(STOCKS[COMPANIES[comp]])
    else:
        print("Unknown company")
    

if __name__ == '__main__':
    comp = str(sys.argv[1])
    finder(comp)
