from __future__ import (absolute_import, division, print_function, unicode_literals)
import pandas as pd
import numpy as np
import datetime
import backtrader as bt
from multiprocessing import Pool, cpu_count
import sys

context = {
    'candle_frequency': None,
    'candle_indicator': None,
    'lookback': 6,
    'candle_columns': ["CDL_3BLACKCROWS","CDL_3INSIDE","CDL_3LINESTRIKE","CDL_3OUTSIDE","CDL_3STARSINSOUTH","CDL_3WHITESOLDIERS","CDL_ABANDONEDBABY","CDL_ADVANCEBLOCK","CDL_BELTHOLD","CDL_BREAKAWAY","CDL_CLOSINGMARUBOZU","CDL_CONCEALBABYSWALL","CDL_COUNTERATTACK","CDL_DARKCLOUDCOVER","CDL_DOJI_10_0.1","CDL_DOJISTAR","CDL_DRAGONFLYDOJI","CDL_ENGULFING","CDL_EVENINGDOJISTAR","CDL_EVENINGSTAR","CDL_GAPSIDESIDEWHITE","CDL_GRAVESTONEDOJI","CDL_HAMMER","CDL_HANGINGMAN","CDL_HARAMI","CDL_HARAMICROSS","CDL_HIGHWAVE","CDL_HIKKAKE","CDL_HIKKAKEMOD","CDL_HOMINGPIGEON","CDL_IDENTICAL3CROWS","CDL_INNECK","CDL_INSIDE","CDL_INVERTEDHAMMER","CDL_KICKING","CDL_KICKINGBYLENGTH","CDL_LADDERBOTTOM","CDL_LONGLEGGEDDOJI","CDL_LONGLINE","CDL_MARUBOZU","CDL_MATCHINGLOW","CDL_MATHOLD","CDL_MORNINGDOJISTAR","CDL_MORNINGSTAR","CDL_ONNECK","CDL_PIERCING","CDL_RICKSHAWMAN","CDL_RISEFALL3METHODS","CDL_SEPARATINGLINES","CDL_SHOOTINGSTAR","CDL_SHORTLINE","CDL_SPINNINGTOP","CDL_STALLEDPATTERN","CDL_STICKSANDWICH","CDL_TAKURI","CDL_TASUKIGAP","CDL_THRUSTING","CDL_TRISTAR","CDL_UNIQUE3RIVER","CDL_UPSIDEGAP2CROWS","CDL_XSIDEGAP3METHODS"]
}

class CandleFrequencyStrategy(bt.Strategy):

    params = {
        'printlog': False,
        'stop_loss': None,
        'take_profit': None
    }

    def __init__(self):
        self.candle_frequency = context["candle_frequency"]
        self.candle_indicator = context["candle_indicator"]
        self.candle_columns = context['candle_columns']
        self.stop_loss = self.params.stop_loss / 100.00
        self.take_profit = self.params.take_profit / 100.00
        self.brackets = None
    
    def log(self, txt, dt=None, doprint=False):
        dt = dt or self.datas[0].datetime.date(0)
        print('%s, %s' % (dt.isoformat(), txt))

    def notify_order(self, order):
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

    def notify_trade(self, trade):
        if not trade.isclosed:
            return

        self.log('OPERATION PROFIT, GROSS %.2f, NET %.2f' %
                 (trade.pnl, trade.pnlcomm))


    def next(self):
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
            

            bullish_strength = (np.min([self.candle_frequency[candle_name].loc[1] for candle_name in candle_list]) + np.max([self.candle_frequency[candle_name].loc[1] for candle_name in candle_list]))/2
            bearish_strength = (np.min([self.candle_frequency[candle_name].loc[-1] for candle_name in candle_list]) + np.max([self.candle_frequency[candle_name].loc[-1] for candle_name in candle_list]))/2
            price = self.data.close[0]

            if bullish_strength > bearish_strength:
               # self.log('BUY CREATE, %.2f' % self.data.close[0])
                self.brackets = self.buy_bracket(
                    limitprice =self.data.high[0] * (1 + self.take_profit), 
                    price = (self.data.high[0] + self.data.low[0]) / 2, 
                    stopprice = self.data.low[0]  * (1 - self.stop_loss)
            )
            elif bearish_strength > bullish_strength:
                # self.log('SELL CREATE, %.2f' % self.data.close[0])
                self.brackets = self.sell_bracket(
                    limitprice = self.data.low[0] * (1 - self.take_profit), 
                    price = (self.data.high[0] + self.data.low[0]) / 2, 
                    stopprice = self.data.high[0] * (1 + self.stop_loss)
                )
            else:
                self.log('NO DECISION, %.2f' % self.data.close[0])

    def stop(self):
        self.log('Ending Value %.2f' %(self.broker.getvalue(), ), doprint=True)


def load_candle_indicator(data_path):
    candle_indicator = pd.read_csv(data_path, parse_dates=False)
    candle_indicator['Date'] = candle_indicator['Date'].apply(lambda x: x[0: 10])
    candle_indicator.set_index('Date', inplace=True)
    return candle_indicator


def epoch(data_path, candle_frequency, stop_loss, take_profit):
    context['candle_frequency'] = candle_frequency
    context['candle_indicator'] = load_candle_indicator(data_path)
    data = bt.feeds.YahooFinanceCSVData(
        dataname= data_path,
        reverse=False
     )
    cerebro = bt.Cerebro()

    # Add a strategy
    strats = cerebro.optstrategy(
        CandleFrequencyStrategy,
        stop_loss = stop_loss,
        take_profit = take_profit
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

if __name__ == "__main__":
    data_path = f"data/symbols/train/{sys.argv[1]}.csv"
    candle_frequency = pd.read_csv("data/merged/candle_frecuency.csv", index_col='TrendDirection')
    results = list()
    pool = Pool(cpu_count())
    for stop_loss in range(1, 10):
        for take_profit in range(1, 10):
            results.append(epoch(data_path, candle_frequency, stop_loss, take_profit))
    print(results)