#include "OrderBook.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace witchpot;     
using namespace std;

OrderBook::OrderBook(const OrderBook & other): is_owner(false)  {
    acceptedOrderEntries = other.acceptedOrderEntries;
    filledOrderEntries = other.filledOrderEntries;
    cancelledOrderEntries = other.cancelledOrderEntries;
}

OrderBook & OrderBook::operator=(const OrderBook & other) {
    acceptedOrderEntries = other.acceptedOrderEntries;
    filledOrderEntries = other.filledOrderEntries;
    cancelledOrderEntries = other.cancelledOrderEntries;
    is_owner = false;
    return *this;
}


void OrderBook::createOrder(
    Timestamp & timestamp,
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float takeProfit,
    OrderSide side,
    std::map<std::string, float> & additionalInfo
) {   
    auto entry = new OrderBookEntry(
        symbol,
        timestamp,
        price,
        quantity,
        stop,
        takeProfit,
        side,
        additionalInfo
    );
    
    string orderId(entry->getMarketOrder().getOrderId());   
    allOrderEntries->insert_or_assign(orderId, entry); 
    acceptedOrderEntries->insert_or_assign(orderId, entry); 
}

void OrderBook::createBuyOrder (
        Timestamp & timestamp,
        std::string symbol,
        float price,
        int quantity,
        float stop,
        float takeProfit,
        std::map<std::string, float> & additionalInfo
    ) {
    createOrder(timestamp, symbol, price, quantity, stop, takeProfit, OrderSide::BUY, additionalInfo);

}

void OrderBook::createSellOrder (
    Timestamp & timestamp,
    std::string symbol,
    float price,
    int quantity,
    float stop,
    float takeProfit,
    std::map<std::string, float> & additionalInfo
) {
    createOrder(timestamp, symbol, price, quantity, stop, takeProfit, OrderSide::SELL, additionalInfo);
}

vector<const OrderBookEntry *> OrderBook::fillOrders(const Timeseries<FeedEntry> & timeSeries, const Timestamp & current) {
    std::vector<const OrderBookEntry *> result;
    for (auto const& [key, orderBookEntry] : *acceptedOrderEntries) {         //TODO: Fill accepted order entries.
        string orderId(orderBookEntry->getMarketOrder().getOrderId());
        auto marketOrder = orderBookEntry->getMarketOrder();     
        auto stopOrder = orderBookEntry->getStopOrder();
        auto takeProfitOrder = orderBookEntry->getTakeProfitOrder();
        bool fill = false;

        if(marketOrder.getTimestamp() < current && timeSeries.contains(current)){
            const FeedEntry & feedEntry = *timeSeries.get(current).value();
            
            if(marketOrder.getSide() == OrderSide::BUY) {            
                fill = feedEntry.getHigh() >= takeProfitOrder.getPrice() || feedEntry.getLow() <= stopOrder.getPrice();
            } else {
                fill = feedEntry.getLow() <= takeProfitOrder.getPrice() || feedEntry.getHigh() >= stopOrder.getPrice();
            }
        }

        if (fill) { //REMARK: filter func should use parallel processing if possible      
            result.push_back(orderBookEntry);
            filledOrderEntries->insert(std::make_pair(orderId, orderBookEntry));
        }
    }

    for(const OrderBookEntry * acceptedEntry : result) {
        auto orderId = acceptedEntry->getMarketOrder().getOrderId();
        acceptedOrderEntries->erase(orderId);
        filledOrderEntries->insert(std::make_pair(orderId, acceptedEntry));
    }

    return result;
}
    

OrderBook::~OrderBook() {
    if(is_owner) {            
        for(auto const& [key, value] : *allOrderEntries) {   
            delete value;
        }        
        allOrderEntries->clear();
        delete allOrderEntries;
        allOrderEntries = nullptr;
        
        acceptedOrderEntries->clear();
        delete acceptedOrderEntries;
        acceptedOrderEntries = nullptr;

        filledOrderEntries->clear();
        delete filledOrderEntries;
        filledOrderEntries = nullptr;

        cancelledOrderEntries->clear();
        delete cancelledOrderEntries;
        cancelledOrderEntries = nullptr;

        is_owner = false;
    }
}

