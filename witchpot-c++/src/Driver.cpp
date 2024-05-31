#include "Driver.h"
#include <optional>

using namespace witchpot;
using namespace std;


void Driver::run() {
    Timestamp current(timeSeries.getStart());
    auto begin = TimeseriesIterator<FeedEntry>::begin(timeSeries);
    auto end = TimeseriesIterator<FeedEntry>::end(timeSeries);

    for_each(begin, end, [&](const FeedEntry & entry) {      
        auto current = entry.getTimestamp();
        auto filledOrders = fillOrders(current) ;
        createTransactions(filledOrders, current);
        checkOmens(current);
        applySchemas(current);
    });


    
}   

vector<const OrderBookEntry *> Driver::fillOrders(const Timestamp & current) {
    OrderBook & orderBook = * this->orderBook;  
    
    
    return orderBook.fillOrders(timeSeries, current);    
}

void Driver::createTransactions(const vector<const OrderBookEntry *> & filledOrders, const Timestamp & current) {
    for(auto orderBookEntry : filledOrders) {
        auto ticket = timeSeries.get(current).value();
        auto marketOrder = orderBookEntry->getMarketOrder();     
        auto stopOrder = orderBookEntry->getStopOrder();
        auto takeProfitOrder = orderBookEntry->getTakeProfitOrder();               
        const OrderBookEntry & entry = *orderBookEntry;     
        OrderSide side = marketOrder.getSide();

        if(side == OrderSide::BUY) {
            if(ticket->getHigh() >= takeProfitOrder.getPrice()) {             
                transactionLog->add(current, entry, OrderType::TAKE_PROFIT);   
            } else if(ticket->getLow() <= stopOrder.getPrice()) {            
                transactionLog->add(current, entry, OrderType::STOP);
            }
        } else if(side == OrderSide::SELL) {
            if(ticket->getLow() <= takeProfitOrder.getPrice()) {             
                transactionLog->add(current, entry, OrderType::TAKE_PROFIT);   
            } else if(ticket->getHigh() >= stopOrder.getPrice()) {            
                transactionLog->add(current, entry, OrderType::STOP);
            }
        }        
    }
}

void Driver::checkOmens(const Timestamp & current) {
    auto begin = omenMap.begin();
    auto end = omenMap.end();
    for(; begin != end; ++begin) {
        auto omen = begin->second.get();
        omen->calculate(timeSeries, current);
    }
}

void Driver::applySchemas(Timestamp & current) {
    auto begin = schemaMap.begin();
    auto end = schemaMap.end();
    for(; begin != end; ++begin) {
        auto schema = begin->second.get();
        schema->apply(timeSeries, omenMap, current, *orderBook);
    }
}