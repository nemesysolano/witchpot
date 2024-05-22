#include "Omen.h"
#include "Schema.h"
#include "witchpot.h"
#include <map>
#include <filesystem>
#include <fstream>
#include <cassert>
#include "OrderBook.h"
#include "Driver.h"
#include <iostream>

using namespace std;
using namespace witchpot;

void timeSeriesTest() {
        vector<string> files;
    string path = "/Volumes/samsung-ex/workspaces/witchpot/data/symbols/";

    for (const auto &entry : filesystem::directory_iterator(path))
    {
        ifstream is(entry.path().string());
        if (entry.is_directory())
            continue;
        Timeseries<FeedEntry> timeSeries(is, entry.path().string());
        cout << entry.path().string() << ' ' << timeSeries.size() << ' ' << timeSeries.getStart() << ' ' << timeSeries.getEnd() << ' ';
        
        if (timeSeries.size() > 0)
        {
            auto end = timeSeries.getEnd();
            auto start = timeSeries.getStart();
            auto eof = timeSeries.getEof();
            auto current(start);
            assert(timeSeries.contains(start) && timeSeries.contains(end));
            size_t counter = 0;
            cout << current << endl;

            while (current != eof)
            {                
                assert(timeSeries.contains(current));
                timeSeries.goToNext(current);
            }
            assert(counter = timeSeries.size());
            assert(current == eof);
        }

        cout << endl;
    }
}


void transactionsAllBuyWinnersTest() {    
    string symbol("AAPL");
    Timeseries <FeedEntry> timeSeries;
    map<string, unique_ptr<Schema>> schemaMap;
    map<string, unique_ptr<Omen>> omenMap;
    Driver driver(timeSeries, schemaMap, omenMap);
    OrderBook & orderBook = driver.getOrderBook();
    auto timestamp = Timestamp::now();
    
    orderBook.createBuyOrder(timestamp, symbol, 16, 1, 14, 20);
    ++timestamp;
    timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, 15, 10,	19,	17, 17, 1));
    
    orderBook.createBuyOrder(timestamp, symbol, 15, 1, 13, 21);    
    ++timestamp;
    timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, 14,	9,	18,	16, 16, 1));    
    
    orderBook.createBuyOrder(timestamp, symbol, 14, 1, 12, 22);    
    ++timestamp;
    timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, 13,	8,	17,	15, 15, 1));
    
    Timestamp start(timeSeries.getStart());
    TransactionSummary transactionSummary;

    while(start != timeSeries.getEof()) {
        auto filledOrders = driver.fillOrders(start);        
        driver.createTransactions(filledOrders, start);
        transactionSummary = driver.getTransactionLog().getTransactionSummary();
        cout << transactionSummary << endl;

        timeSeries.goToNext(start);
    }

    assert((int)transactionSummary.buyCount == 3);
    assert((int)transactionSummary.sellCount == 0);
    assert((int)transactionSummary.totalWon == 18);
    assert((int)transactionSummary.totalLost == 0);
    
}

void transactionsAllSellWinnersTest() {    
    string symbol("AAPL");
    Timeseries <FeedEntry> timeSeries;
    map<string, unique_ptr<Schema>> schemaMap;
    map<string, unique_ptr<Omen>> omenMap;
    Driver driver(timeSeries, schemaMap, omenMap);
    OrderBook & orderBook = driver.getOrderBook();
    auto timestamp = Timestamp::now();
    
    orderBook.createSellOrder(timestamp, symbol, 14, 1, 19, 9);
    ++timestamp;
    timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, 13,	8,	18,	15,	15, 1));
    
    orderBook.createSellOrder(timestamp, symbol, 13, 1, 18, 8);    
    ++timestamp;
    timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, 12,	7,	17,	14,	14, 1));    
    
    orderBook.createSellOrder(timestamp, symbol, 11, 1, 16, 6);    
    ++timestamp;
    timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, 10,	6,	15,	13,	13, 1));
    
    Timestamp start(timeSeries.getStart());
    TransactionSummary transactionSummary;

    while(start != timeSeries.getEof()) {
        auto filledOrders = driver.fillOrders(start);        
        driver.createTransactions(filledOrders, start);
        transactionSummary = driver.getTransactionLog().getTransactionSummary();
        cout << transactionSummary << endl;

        timeSeries.goToNext(start);
    }

    assert((int)transactionSummary.buyCount == 0);
    assert((int)transactionSummary.sellCount == 3);
    assert((int)transactionSummary.totalWon == 15);
    assert((int)transactionSummary.totalLost == 0);
    
}
int main()
{
    // timeSeriesTest();    
     transactionsAllBuyWinnersTest();
     transactionsAllSellWinnersTest();
    return 0;
}