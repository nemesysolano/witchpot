from __future__ import (absolute_import, division, print_function, unicode_literals)
import gc
import functools
import pandas as pd
import numpy as np
import datetime
import backtrader as bt
from multiprocessing import Pool, cpu_count
import sys
import os

candle_columns = ("CDL_3BLACKCROWS","CDL_3INSIDE","CDL_3LINESTRIKE","CDL_3OUTSIDE","CDL_3STARSINSOUTH","CDL_3WHITESOLDIERS","CDL_ABANDONEDBABY","CDL_ADVANCEBLOCK","CDL_BELTHOLD","CDL_BREAKAWAY","CDL_CLOSINGMARUBOZU","CDL_CONCEALBABYSWALL","CDL_COUNTERATTACK","CDL_DARKCLOUDCOVER","CDL_DOJI_10_0.1","CDL_DOJISTAR","CDL_DRAGONFLYDOJI","CDL_ENGULFING","CDL_EVENINGDOJISTAR","CDL_EVENINGSTAR","CDL_GAPSIDESIDEWHITE","CDL_GRAVESTONEDOJI","CDL_HAMMER","CDL_HANGINGMAN","CDL_HARAMI","CDL_HARAMICROSS","CDL_HIGHWAVE","CDL_HIKKAKE","CDL_HIKKAKEMOD","CDL_HOMINGPIGEON","CDL_IDENTICAL3CROWS","CDL_INNECK","CDL_INSIDE","CDL_INVERTEDHAMMER","CDL_KICKING","CDL_KICKINGBYLENGTH","CDL_LADDERBOTTOM","CDL_LONGLEGGEDDOJI","CDL_LONGLINE","CDL_MARUBOZU","CDL_MATCHINGLOW","CDL_MATHOLD","CDL_MORNINGDOJISTAR","CDL_MORNINGSTAR","CDL_ONNECK","CDL_PIERCING","CDL_RICKSHAWMAN","CDL_RISEFALL3METHODS","CDL_SEPARATINGLINES","CDL_SHOOTINGSTAR","CDL_SHORTLINE","CDL_SPINNINGTOP","CDL_STALLEDPATTERN","CDL_STICKSANDWICH","CDL_TAKURI","CDL_TASUKIGAP","CDL_THRUSTING","CDL_TRISTAR","CDL_UNIQUE3RIVER","CDL_UPSIDEGAP2CROWS","CDL_XSIDEGAP3METHODS")

def strategy_constructor_factory(candle_frequency, candle_indicator, candle_columns, stop_loss, take_profit, debug = False):
    def constructor(self):
        self.candle_frequency = candle_frequency
        self.candle_indicator = candle_indicator
        self.candle_columns = candle_columns
        self.stop_loss = stop_loss / 100.00
        self.take_profit = take_profit / 100.00
        self.brackets = None
        self.debug = debug
    return constructor
    
def strategy_log(self, txt, dt=None, doprint=False):
    if(self.debug):
        dt = dt or self.datas[0].datetime.date(0)
        print('%s, %s' % (dt.isoformat(), txt))

 

def strategy_notify_order(self, order):
    if order.status in [order.Submitted, order.Accepted]:
        # Buy/Sell order submitted/accepted to/by broker - Nothing to do
        return

    # Check if an order has been completed
    # Attention: broker could reject order if not enough cash
    if order.status in [order.Completed]:
        if order.isbuy():
            self.log(
                'BUY EXECUTED, Price: %.2f, Cost: %.2f, Comm %.2f' %
                (order.executed.price,
                    order.executed.value,
                    order.executed.comm))

            self.buyprice = order.executed.price
            self.buycomm = order.executed.comm
        else:  # Sell
            self.log('SELL EXECUTED, Price: %.2f, Cost: %.2f, Comm %.2f' %
                        (order.executed.price,
                        order.executed.value,
                        order.executed.comm))

        self.bar_executed = len(self)

    elif order.status in [order.Canceled, order.Margin, order.Rejected]:
        self.log('Order Canceled/Margin/Rejected')

    # Write down: no pending order
    self.brackets = None

def strategy_notify_trade(self, trade):
    if not trade.isclosed:
        return

    self.log('OPERATION PROFIT, GROSS %.2f, NET %.2f' %
        (trade.pnl, trade.pnlcomm))

def strategy_next(self):
    # Simply log the closing price of the series from the reference
    # Check if an order is pending ... if yes, we cannot send a 2nd one
    if self.brackets:
        return
    
    
    if not self.position: 
        # Get previous date to get candle indicator
        previous_date = "{}".format(self.data.datetime.date(0)  - datetime.timedelta(days=1))
        
        # Check if previous date is in candle indicator
        if previous_date not in self.candle_indicator.index:
            return
        
        # Check if some candle has been found
        candle_list = tuple([candle_name for candle_name in self.candle_columns if int(self.candle_indicator[candle_name].loc[previous_date]) != 0])
        if len(candle_list) == 0:
            return
        

        bullish_strength = np.sum([self.candle_frequency[candle_name].loc[1] for candle_name in candle_list])
        bearish_strength = np.sum([self.candle_frequency[candle_name].loc[-1] for candle_name in candle_list])


        if bullish_strength > bearish_strength:
            self.log('BUY CREATE, %.2f' % self.data.close[0])
            self.brackets = self.buy_bracket(
                limitprice =self.data.high[0] * (1 + self.take_profit), 
                price = (self.data.open[0]  + self.data.close[0]) / 2, 
                stopprice = self.data.low[0]  * (1 - self.stop_loss)
        )
        elif bearish_strength > bullish_strength:
            self.log('SELL CREATE, %.2f' % self.data.close[0])
            self.brackets = self.sell_bracket(
                limitprice = self.data.low[0] * (1 - self.take_profit), 
                price = (self.data.open[0] + self.data.close[0]) / 2, 
                stopprice = self.data.high[0] * (1 + self.stop_loss)
            )
        else:
            self.log('NO DECISION, %.2f' % self.data.close[0])


def strategy_stop(self):
    self.log('Ending Value %.2f' %(self.broker.getvalue(), ), doprint=True)

def strategy_factory(name, candle_frequency, candle_indicator, candle_columns, stop_loss, take_profit, debug = False):
    return type(name, (bt.Strategy, ), { 
        "__init__": strategy_constructor_factory(candle_frequency, candle_indicator, candle_columns, stop_loss, take_profit, debug=debug), 
        "log": strategy_log, 
        "notify_order": strategy_notify_order,
        "notify_trade": strategy_notify_trade,
        "next": strategy_next,
        "stop": strategy_stop
    })

def load_candle_indicator(data_path):
    candle_indicator = pd.read_csv(data_path, parse_dates=False)
    candle_indicator['Date'] = candle_indicator['Date'].apply(lambda x: x[0: 10])
    candle_indicator.set_index('Date', inplace=True)
    return candle_indicator


def epoch(data_path, candle_frequency, stop_loss, take_profit, cash):
    candle_indicator = load_candle_indicator(data_path)
    data = bt.feeds.YahooFinanceCSVData(
        dataname = data_path,
        reverse=False
     )
    cerebro = bt.Cerebro()
    strategy = strategy_factory("CandleFrequencyStrategy_{}_{}".format(stop_loss, take_profit), candle_frequency, candle_indicator, candle_columns, stop_loss, take_profit)
    # Add a strategy
    strats = cerebro.optstrategy(
        strategy
    )

   # Add the Data Feed to Cerebro
    cerebro.adddata(data)

    # Set our desired cash start
    cerebro.broker.setcash(1000.0)

    # Add a FixedSize sizer according to the stake
    cerebro.addsizer(bt.sizers.FixedSize, stake=10)

    # Set the commission
    cerebro.broker.setcommission(commission=0.0)

    # Run over everything
    cerebro.run(maxcpus=1)    
    
    return (stop_loss, take_profit, cerebro.broker.getvalue())

def evaluate(symbol, cashh):
    train_path = f"data/symbols/train/{symbol}.csv"
    validate_path = f"data/symbols/validate/{symbol}.csv"
    test_path = f"data/symbols/test/{symbol}.csv"

    candle_frequency = pd.read_csv("data/symbols/train/merged/candle_frecuency.csv", index_col='TrendDirection')
    pool = Pool(cpu_count())

    train_search_space = [(train_path, candle_frequency, stop_loss, take_profit, cash) for stop_loss in range(1, 10) for take_profit in range(1, 10)]
    train_results = pd.DataFrame(
        data = tuple(filter(lambda t: int(t[2]) > int(cash), pool.starmap(epoch, train_search_space))),
        columns= ["stop_loss", "take_profit", "final_value"]
    )

    validate_search_space = [(validate_path, candle_frequency, stop_loss, take_profit, cash) for stop_loss, take_profit, _ in train_results.itertuples(index=False)]
    validate_results = pd.DataFrame(
        data = tuple(filter(lambda t: int(t[2]) > int(cash), pool.starmap(epoch, validate_search_space))),
        columns= ["stop_loss", "take_profit", "final_value"]
    )

    best_performants = validate_results[validate_results['final_value'] > cash]
    test_search_space = [(test_path, candle_frequency, stop_loss, take_profit, cash) for stop_loss, take_profit, _ in best_performants.itertuples(index=False)]
    test_results = pd.DataFrame(
        data = tuple(filter(lambda t: int(t[2]) > int(cash), pool.starmap(epoch, test_search_space))),
        columns= ["stop_loss", "take_profit", "final_value"]
    )

    return test_results

if __name__ == "__main__":
    all_results = pd.DataFrame(data = list(), columns= ["symbol", "stop_loss", "take_profit", "final_value"])
    symbols = list(map(lambda name: name.split(".")[0], os.listdir("data/symbols/train")))[0: 100]
    cash = 1000
    for symbol in symbols:
        results = evaluate(symbol, cash)
        if len(results) > 0:
            # insert a column with the symbol name as the 1st column
            results.insert(0, "symbol", symbol)
            print("Results for symbol: ", symbol)
            print(results)
            all_results = pd.concat([all_results, results], ignore_index=True)
            all_results.to_csv("data/results/all_results.csv")
            gc.collect()
