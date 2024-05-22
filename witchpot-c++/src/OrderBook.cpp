#include "OrderBook.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace witchpot;     
using namespace std;

OrderBook::OrderBook(const OrderBook & other): is_owner(false)  {
    orderEntries = other.orderEntries;
    acceptedOrderEntries = other.acceptedOrderEntries;
    filledOrderEntries = other.filledOrderEntries;
    cancelledOrderEntries = other.cancelledOrderEntries;
}

OrderBook & OrderBook::operator=(const OrderBook & other) {
    orderEntries = other.orderEntries;
    acceptedOrderEntries = other.acceptedOrderEntries;
    filledOrderEntries = other.filledOrderEntries;
    cancelledOrderEntries = other.cancelledOrderEntries;
    is_owner = false;
    return *this;
}


const OrderBookEntry & OrderBook::createOrder(
    Timestamp & timestamp,
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float takeProfit,
    OrderSide side
) {   
    auto entry = new OrderBookEntry(
        symbol,
        timestamp,
        price,
        quantity,
        stop,
        takeProfit,
        side
    );
    
    const string orderId = entry->getMarketOrder().getOrderId();
    orderEntries->insert(std::make_pair(orderId, entry));    
    acceptedOrderEntries->insert(std::make_pair(entry->getMarketOrder().getOrderId(), entry));
    return *entry;
}

const OrderBookEntry & OrderBook::createBuyOrder (
    Timestamp & timestamp,
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float takeProfit
) {
    return createOrder(timestamp, symbol, price, quantity, stop, takeProfit, OrderSide::BUY);

}

const OrderBookEntry & OrderBook::createSellOrder (
    Timestamp & timestamp,
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float takeProfit
) {
    return createOrder(timestamp, symbol, price, quantity, stop, takeProfit, OrderSide::SELL);
}

vector<const OrderBookEntry *> OrderBook::fillOrders(std::function<bool(const OrderBookEntry &)> filterFunc) {
    std::vector<const OrderBookEntry *> result;
    for (auto const& [key, value] : *acceptedOrderEntries) {         //TODO: Fill accepted order entries.
        if (filterFunc(*value)) { //REMARK: filter func should use parallel processing if possible      
            result.push_back(value);
            filledOrderEntries->insert(std::make_pair(value->getMarketOrder().getOrderId(), value));
            acceptedOrderEntries->erase(value->getMarketOrder().getOrderId());            
        }
    }

    return result;
}
    
vector<const OrderBookEntry *> OrderBook::acceptedOrders(std::function<bool(const OrderBookEntry &)> filterFunc) {
    std::vector<const OrderBookEntry *> result;
    for (auto const& [key, value] : *acceptedOrderEntries) {
        if (filterFunc(*value)) { //REMARK: filter func should use parallel processing if possible
            result.push_back(value);
        }
    }
    return result;
}

OrderBook::~OrderBook() {
    if(is_owner) {
        for(auto const& [key, value] : *orderEntries) {
            delete value;
        }

        orderEntries->clear();
        delete orderEntries;
        
        acceptedOrderEntries->clear();
        delete acceptedOrderEntries;

        filledOrderEntries->clear();
        delete filledOrderEntries;

        cancelledOrderEntries;
        delete cancelledOrderEntries;
    }
}

