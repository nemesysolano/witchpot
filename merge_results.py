import os
import sys
from multiprocessing import Pool
def list_files(file_path):
    listing = []
    for file in os.listdir(file_path):
        if file.endswith('.csv'):
            listing.append(os.path.join(file_path, file))
        
    return listing

def merge_results(symbols_path, merged_path):
    file_paths = list_files(symbols_path)
    with open(merged_path,"wt") as fout:
        print('"direction","take_profit","stop_loss","open","high","low","close","weight","volume","result"', file=fout)
        for file_path in file_paths:
            print(file_path)
            with open(file_path, "rt") as f:
                next(f)
                for line in f:
                    fout.write(line)

if __name__ == '__main__':
    paths = [
        ('data/results/test/normalized', 'data/results/merged/normalized/test.csv'),
        ('data/results/train/normalized', 'data/results/merged/normalized/train.csv'),
        ('data/results/validate/normalized', 'data/results/merged/normalized/validate.csv')
    ]
    pool = Pool(processes=3)
    pool.starmap(merge_results, paths)
    