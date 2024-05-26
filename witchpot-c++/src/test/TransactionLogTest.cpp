
#include "TransactionLogTest.h"
using namespace std;
using namespace witchpot;

void transactionsAllBuyWinnersTest() {    
    string symbol("AAPL");
    Timeseries <FeedEntry> timeSeries;
    map<string, unique_ptr<Schema>> schemaMap;
    map<string, unique_ptr<Omen>> omenMap;
    Driver driver(timeSeries, schemaMap, omenMap);
    OrderBook & orderBook = driver.getOrderBook();
    auto timestamp = Timestamp::now();

    // CSV values
    std::vector<std::vector<double>> csvValues = {
        {5, 4, 10, 8, 5, 3, 7},
        {6, 5, 11, 9, 6, 4, 8},
        {7, 6, 12, 10, 7, 5, 9}
    };

    for (auto& values : csvValues) {
        orderBook.createBuyOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }

    Timestamp start(timeSeries.getStart());
    TransactionSummary transactionSummary;

    while(start != timeSeries.getEof()) {
        auto filledOrders = driver.fillOrders(start);        
        driver.createTransactions(filledOrders, start);
        transactionSummary = driver.getTransactionLog().getTransactionSummary();
        timeSeries.goToNext(start);
    }
    cout << transactionSummary << endl;
    assert((int)transactionSummary.buyCount == 3);
    assert((int)transactionSummary.sellCount == 0);
    assert((int)transactionSummary.totalWon == 6);
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

    // CSV values
    std::vector<std::vector<double>> csvValues = {
        {5, 3, 4, 4, 5, 7, 3},
        {6, 4, 5, 5, 6, 8, 4},
        {7, 5, 6, 6, 7, 9, 5}
    };

    for (auto& values : csvValues) {
        orderBook.createSellOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }

    Timestamp start(timeSeries.getStart());
    TransactionSummary transactionSummary;

    while(start != timeSeries.getEof()) {
        auto filledOrders = driver.fillOrders(start);        
        driver.createTransactions(filledOrders, start);
        transactionSummary = driver.getTransactionLog().getTransactionSummary();

        timeSeries.goToNext(start);
    }

    cout << transactionSummary << endl;
    assert((int)transactionSummary.buyCount == 0);
    assert((int)transactionSummary.sellCount == 3);
    assert((int)transactionSummary.totalWon == 6);
    assert((int)transactionSummary.totalLost == 0);
    
}


void transactionsBuyAndSellWinTest() {
    string symbol("AAPL");
    Timeseries <FeedEntry> timeSeries;
    map<string, unique_ptr<Schema>> schemaMap;
    map<string, unique_ptr<Omen>> omenMap;
    Driver driver(timeSeries, schemaMap, omenMap);
    OrderBook & orderBook = driver.getOrderBook();
    auto timestamp = Timestamp::now();
   // CSV values
    std::vector<std::vector<double>> buyCSVValues = {
        {5, 4, 10, 8, 5, 3, 7},
        {6, 5, 11, 9, 6, 4, 8},
        {7, 6, 12, 10, 7, 5, 9}
    };
   // CSV values
    std::vector<std::vector<double>> sellCSVValues = {
        {5, 3, 4, 4, 5, 7, 3},
        {6, 4, 5, 5, 6, 8, 4},
        {7, 5, 6, 6, 7, 9, 5}
    };

    //BUY
    for (auto& values : buyCSVValues) {
        orderBook.createBuyOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }
  
    //SELL
    for (auto& values : sellCSVValues) {
        orderBook.createSellOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }
  
    Timestamp start(timeSeries.getStart());
    TransactionSummary transactionSummary;

    while(start != timeSeries.getEof()) {
        auto filledOrders = driver.fillOrders(start);        
        driver.createTransactions(filledOrders, start);
        transactionSummary = driver.getTransactionLog().getTransactionSummary();

        timeSeries.goToNext(start);
    }

    cout << transactionSummary << endl;
    assert((int)transactionSummary.buyCount == 3);
    assert((int)transactionSummary.sellCount == 3);
    assert((int)transactionSummary.totalWon == 12);
    assert((int)transactionSummary.totalLost == 0);
}

void transactionsBuyWinButSellLose()  {
    string symbol("AAPL");
    Timeseries <FeedEntry> timeSeries;
    map<string, unique_ptr<Schema>> schemaMap;
    map<string, unique_ptr<Omen>> omenMap;
    Driver driver(timeSeries, schemaMap, omenMap);
    OrderBook & orderBook = driver.getOrderBook();
    auto timestamp = Timestamp::now();
   
    // CSV values for winning BUY transactions
    std::vector<std::vector<double>> buyCSVValues = {
        {5, 4, 10, 8, 5, 3, 10},
        {6, 5, 11, 9, 6, 4, 11},
        {7, 6, 12, 10, 7, 5, 12},
        {8, 7, 13, 11, 8, 6, 13},
        {9, 8, 14, 12, 9, 7, 14},
        {10, 9, 15, 13, 10, 8, 15},
        {11, 10, 16, 14, 11, 9, 16}
    };

    // CSV values for losing SELL transactions
    std::vector<std::vector<double>> sellCSVValues = {
        {5, 6, 4, 6, 5, 7, 3},
        {6, 7, 5, 7, 6, 8, 4},
        {7, 8, 6, 8, 7, 9, 5},
        {8, 9, 7, 9, 8, 10, 6},
        {9, 10, 8, 10, 9, 11, 7}
    };

    //BUY
    for (auto& values : buyCSVValues) {
        orderBook.createBuyOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }
  
    //SELL
    for (auto& values : sellCSVValues) {
        orderBook.createSellOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }
  
    Timestamp start(timeSeries.getStart());
    TransactionSummary transactionSummary;

    while(start != timeSeries.getEof()) {
        auto filledOrders = driver.fillOrders(start);        
        driver.createTransactions(filledOrders, start);
        transactionSummary = driver.getTransactionLog().getTransactionSummary();        

        timeSeries.goToNext(start);
    }

    cout << transactionSummary << endl;
    assert((int)transactionSummary.buyCount == 7);
    assert((int)transactionSummary.sellCount == 2);
    assert((int)transactionSummary.totalWon == 35); // All BUY transactions win
    assert((int)transactionSummary.totalLost == 4); // All SELL transactions lose
}

void transactionsBuyLoseButSellWin()  {
    string symbol("AAPL");
    Timeseries <FeedEntry> timeSeries;
    map<string, unique_ptr<Schema>> schemaMap;
    map<string, unique_ptr<Omen>> omenMap;
    Driver driver(timeSeries, schemaMap, omenMap);
    OrderBook & orderBook = driver.getOrderBook();
    auto timestamp = Timestamp::now();

    // CSV values for losing BUY transactions
    std::vector<std::vector<double>> buyCSVValues = {
        {5, 7, 6, 4, 5, 7, 8},
        {6, 8, 7, 5, 6, 8, 9},
        {7, 9, 8, 6, 7, 9, 10},
        {8, 10, 9, 7, 8, 10, 11}
    };

    // CSV values for winning SELL transactions
    std::vector<std::vector<double>> sellCSVValues = {
        {5, 3, 4, 4, 5, 6, 3},
        {6, 4, 5, 5, 6, 7, 4},
        {7, 5, 6, 6, 7, 8, 5},
        {8, 6, 7, 7, 8, 9, 6},
        {9, 7, 8, 8, 9, 10, 7}
    };

    //BUY
    for (auto& values : buyCSVValues) {
        orderBook.createBuyOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }
  
    //SELL
    for (auto& values : sellCSVValues) {
        orderBook.createSellOrder(timestamp, symbol, values[4], values[5], values[6]); // Entry Price, Stop Loss, Take Profit
        ++timestamp;
        timeSeries.add(timestamp, new FeedEntry(symbol, timestamp, values[0], values[1], values[2], values[3])); // Open, Low, High, Close
    }
  
    Timestamp start(timeSeries.getStart());
    TransactionSummary transactionSummary;

    while(start != timeSeries.getEof()) {
        auto filledOrders = driver.fillOrders(start);        
        driver.createTransactions(filledOrders, start);
        transactionSummary = driver.getTransactionLog().getTransactionSummary();        

        timeSeries.goToNext(start);
    }

    cout << transactionSummary << endl;
    assert((int)transactionSummary.buyCount == 4);
    assert((int)transactionSummary.sellCount == 5);
    assert((int)transactionSummary.totalWon == 10); // All SELL transactions win
    assert((int)transactionSummary.totalLost == 8); // All BUY transactions lose
}