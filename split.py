import pandas as pd
import numpy as np
import os
import sys

import functools
from multiprocessing import Pool, cpu_count
def normalize_data(df):
    price_columns = ['Open', 'High', 'Low', 'Close', 'Adj Close', 'Volume']
    price_dataset = df[price_columns]

    varOcg = price_dataset.rolling(6).mean()  # calculate the rolling mean
    std = price_dataset.rolling(6).std()  # calculate the rolling standard deviation
    normalized_df = (price_dataset - varOcg) / std  # normalize the DataFrame
    df[price_columns] = normalized_df
    return df

def split_file(file):
    if os.path.isfile(file) or file.split('.')[-1] == 'csv':    
        df = pd.read_csv(file, index_col="Date", parse_dates=True)

        # Drop na and duplicates and then sort index
        df.dropna( inplace=True)
        df.drop_duplicates( inplace=True)
        df.sort_index(inplace=True)        
        
        train_size = int(len(df) * 0.7)
        validate_size = int(len(df) * 0.2)
        test_size = len(df) - train_size - validate_size

        # Split the data into 3 sets: train, validate and test
        train, validate, test = df.loc[df.index[0: train_size]], df.loc[df.index[train_size: train_size + validate_size]], df.loc[df.index[train_size + validate_size:]]
        train.to_csv('data/symbols/train/bare/%s' % (file.split('/')[-1],))
        validate.to_csv('data/symbols/validate/bare/%s' % (file.split('/')[-1],))
        test.to_csv('data/symbols/test/bare/%s' % (file.split('/')[-1],))

        # Normalize data to conform to normal standard distribution by 6 periods

        df = normalize_data(df)
        
        train, validate, test = df.loc[df.index[0: train_size]], df.loc[df.index[train_size: train_size + validate_size]], df.loc[df.index[train_size + validate_size:]]
        train.to_csv('data/symbols/train/normalized/%s' % (file.split('/')[-1],))
        validate.to_csv('data/symbols/validate/normalized/%s' % (file.split('/')[-1],))
        test.to_csv('data/symbols/test/normalized/%s' % (file.split('/')[-1],))


if __name__ == "__main__":
    symbol_files = ['data/symbols/%s' % (file_name,) for file_name in os.listdir('data/symbols') ]
    with Pool(cpu_count()) as pool:
        pool.map(split_file, symbol_files)