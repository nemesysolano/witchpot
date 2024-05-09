import pandas as pd
import numpy as np
import functools

if __name__ == "__main__":
    market_trends = pd.read_csv("data/symbols/train/merged/market_trends.csv")
    candle_columns =  tuple(filter(lambda name: len(name) > 0, tuple(market_trends.columns.map(lambda name: name if name.startswith('CDL_') else ''))))    
    table = pd.pivot_table(market_trends, values=candle_columns, index='TrendDirection', aggfunc="sum")

    table.drop(index = [0], inplace=True)
    table = table.applymap(lambda x: abs(x) )

    # Sum table values by columns
    sum_table = table.apply(lambda x: x.sum(), axis=0)

    # Normalize table values by columns
    for each in sum_table.index:
        table[each] = table[each] / sum_table[each]

    table.to_csv("data/merged/candle_frecuency.csv")