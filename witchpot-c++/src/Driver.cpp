#include "Driver.h"
#include <optional>

using namespace witchpot;
using namespace std;

void Driver::run() {
    Timestamp eof(timeSeries.getEof());
    Timestamp current(timeSeries.getStart());

    while(current < eof) {
        timeSeries.goToNext(current);        
        auto filledOrders = fillOrders(current);
        createTransactions(filledOrders, current);
        checkOmens(current);
        applySchemas(current);
    }
}   

vector<const OrderBookEntry *> Driver::fillOrders(Timestamp & current) {
    OrderBook & orderBook = * this->orderBook;  
    auto filledOrders = orderBook.fillOrders([&](const OrderBookEntry & orderBookEntry) {   
        auto marketOrder = orderBookEntry.getMarketOrder();     
        auto stopOrder = orderBookEntry.getStopOrder();
        auto takeProfitOrder = orderBookEntry.getTakeProfitOrder();
        
        cout << "Market Order: " << marketOrder.getTimestamp() << ", Stop Order: " << stopOrder.getTimestamp() << ", Take Profit Order: " << takeProfitOrder.getTimestamp() << ", Current: " << current << endl;
        if(marketOrder.getTimestamp() < current){
            auto feedEntry = timeSeries.get(current).value();
            
            if(marketOrder.getSide() == OrderSide::BUY) {            
                cout << "BUY->  High: " << feedEntry->getHigh() << ", Low: " << feedEntry->getLow() << ", Take Profit: " << takeProfitOrder.getPrice() << ", Stop: " << stopOrder.getPrice() << endl;
                return feedEntry->getHigh() >= takeProfitOrder.getPrice() || feedEntry->getLow() <= stopOrder.getPrice();
            } else {
                cout << "SELL-> High: " << feedEntry->getHigh() << ", Low: " << feedEntry->getLow() << ", Take Profit: " << takeProfitOrder.getPrice() << ", Stop: " << stopOrder.getPrice() << endl;  
                return feedEntry->getLow() <= takeProfitOrder.getPrice() || feedEntry->getHigh() >= stopOrder.getPrice();
            }
        }

        return false;
    });
    
    return filledOrders;    
}

void Driver::createTransactions(const vector<const OrderBookEntry *> & filledOrders, const Timestamp & current) {
    for(auto orderBookEntry : filledOrders) {
        auto start = filledOrders.begin();
        auto end = filledOrders.end();
        auto ticket = timeSeries.get(current).value();
        auto marketOrder = orderBookEntry->getMarketOrder();     
        auto stopOrder = orderBookEntry->getStopOrder();
        auto takeProfitOrder = orderBookEntry->getTakeProfitOrder();       
        const OrderBookEntry & entry = *orderBookEntry;     
        cout << filledOrders.size() << endl;
        if(
            ticket->getHigh() >= takeProfitOrder.getPrice() || 
            ticket->getLow() <= takeProfitOrder.getPrice())
        {             
            transactionLog->add(current, entry, OrderType::TAKE_PROFIT);   
        } else if(
            ticket->getLow() <= stopOrder.getPrice() || 
            ticket->getHigh() >= stopOrder.getPrice()
        ) {            
            transactionLog->add(current, entry, OrderType::STOP);
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
    
}