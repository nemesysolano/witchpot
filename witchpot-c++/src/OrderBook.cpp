#include "OrderBook.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace witchpot;     
using namespace std;

static void scramble_string(string& text) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(text.begin(), text.end(), gen);
}

static string createOrderId(
    Timestamp & timestamp,
    std::string & symbol,
    float price,
    int quantity,
    float stop,
    float limit,    
    OrderSide side,
    OrderType type
) {
    stringstream ss;
    ss << timestamp << ',' << symbol << ',' << price << ',' << quantity << ',' << stop << ',' << limit << ',' << side << ',' << side << ',' << type;    
    string clerText = ss.str();
    scramble_string(clerText);
    return clerText;
}

unique_ptr<OrderBookEntry> OrderBook::createOrder(
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float limit,
    OrderSide side
) {
   Timestamp timestamp = Timestamp::now();    

    Order * marketOrder = new MarketOrder(
        timestamp,
        createOrderId(timestamp, symbol, price, quantity, stop, limit, side, OrderType::MARKET),
        symbol,
        price,
        quantity,
        side
    );
    this->allOrderEntries.insert(std::make_pair(marketOrder->getOrderId(), unique_ptr<Order>(marketOrder)));
    this->pendingOrderEntries.insert(marketOrder->getOrderId());
    this->acceptedOrderEntries.insert(marketOrder->getOrderId());
    
    Order * limitOrder(new LimitOrder(
        createOrderId(timestamp, symbol, price, quantity, stop, limit, side == OrderSide::BUY ? OrderSide::SELL : OrderSide::BUY, OrderType::LIMIT),
        limit,
        (*(MarketOrder *)marketOrder)
    ));
    this->allOrderEntries.insert(std::make_pair(limitOrder->getOrderId(), unique_ptr<Order>(limitOrder)));
    this->pendingOrderEntries.insert(limitOrder->getOrderId());
    this->acceptedOrderEntries.insert(limitOrder->getOrderId());

    Order * stopOrder = new StopOrder(
        createOrderId(timestamp, symbol, price, quantity, stop, limit, side == OrderSide::BUY ? OrderSide::SELL : OrderSide::BUY, OrderType::STOP),
        stop,
        (*(MarketOrder *)marketOrder)
    );
    this->allOrderEntries.insert(std::make_pair(stopOrder->getOrderId(), unique_ptr<Order>(stopOrder)));
    this->pendingOrderEntries.insert(stopOrder->getOrderId());
    this->acceptedOrderEntries.insert(stopOrder->getOrderId());

    return unique_ptr<OrderBookEntry>(new OrderBookEntry (OrderStatus::ACCEPTED, marketOrder->getOrderId(), limitOrder->getOrderId(), stopOrder->getOrderId()));
}

unique_ptr<OrderBookEntry> OrderBook::createBuyOrder (
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float limit
) {
    return createOrder(symbol, price, quantity, stop, limit, OrderSide::BUY);

}

unique_ptr<OrderBookEntry> OrderBook::createSellOrder (
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float limit
) {
    return createOrder(symbol, price, quantity, stop, limit, OrderSide::SELL);
}