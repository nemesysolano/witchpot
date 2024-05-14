import pandas as pd
import pandas_ta as ta
from multiprocessing import Pool, cpu_count
import yfinance as yf

def download_from_yahoo(symbol):
    file_name = "data/symbols/{}.csv".format(symbol, )
    train_file_name = "data/symbols/train/{}.csv".format(symbol, )
    validate_file_name = "data/symbols/validate/{}.csv".format(symbol, )
    test_file_name = "data/symbols/test/{}.csv".format(symbol, )

    try:
        df = yf.Ticker(symbol)
        history = df.history(period='max')    
        candles = history.ta.cdl_pattern()
        merged = pd.merge(history, candles, left_index=True, right_index=True)
        # Insert a new column called 'Adj Close' after 'Close'
        adj_close = merged['Close']
        merged.insert(4, 'Adj Close', adj_close)

        merged.to_csv(file_name)
        
        train_size = int(0.7 * len(merged))
        validate_size = int(0.2 * len(merged))
        test_size = len(merged) - train_size - validate_size
        index = merged.index
        
        train = merged.loc[index[:train_size]]
        train.to_csv(train_file_name)

        validate = merged.loc[index[train_size:train_size+validate_size]]
        validate.to_csv(validate_file_name)

        test = merged.loc[index[train_size+validate_size:]]        
        test.to_csv(test_file_name)

        merged.to_csv(file_name)
        return train_file_name
    except Exception as cause:
        print(f"Unexpected {cause}, {type(cause)}")
        return ''

if __name__ == "__main__":
    pool = Pool(cpu_count())
    sp500 = pd.read_csv('catalog/russell100.csv', index_col= 'Symbol')    
    pool.map(download_from_yahoo, sp500.index)
    
