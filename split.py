import pandas as pd
import numpy as np
import os
import sys

import functools
from multiprocessing import Pool, cpu_count

def split_file(file):
    if os.path.isfile(file) or file.split('.')[-1] == 'csv':    
        df = pd.read_csv(file)
        # Split the data into 3 sets: train, validate and test
        train, validate, test = np.split(df.sample(frac=1), [int(.6*len(df)), int(.8*len(df))])
        train.to_csv('data/symbols/train/%s' % (file.split('/')[-1],), index=False)
        validate.to_csv('data/symbols/validate/%s' % (file.split('/')[-1],), index=False)
        test.to_csv('data/symbols/test/%s' % (file.split('/')[-1],), index=False)

if __name__ == "__main__":
    symbol_files = ['data/symbols/%s' % (file_name,) for file_name in os.listdir('data/symbols') ]
    with Pool(cpu_count()) as pool:
        pool.map(split_file, symbol_files)