#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__
#include "OrderBookEntry.h"
#include <string>
#include <iostream>
#include <ostream>
namespace witchpot {
    class Transaction {
        Timestamp timestamp;
        std::string symbol;
        float price; //
        float stopPrice;
        float takeProfitPrice;
        OrderSide side;
        OrderType executionType;
        int quantity;
    
    public:
        Transaction(
            const Timestamp & timestamp_,
            std::string symbol_,
            float price_,
            float stopPrice_,
            float takeProfitPrice_,
            OrderSide side_,
            OrderType executionType_,
            int quantity_
        ): timestamp(timestamp_), symbol(symbol_), price(price_), stopPrice(stopPrice_), takeProfitPrice(takeProfitPrice_), side(side_), executionType(executionType_), quantity(quantity_) {}        

        Transaction(
            const Timestamp & timestamp,
            const OrderBookEntry & orderBookEntry,
            OrderType executionType
        ): Transaction(
            timestamp,
            orderBookEntry.getMarketOrder().getSymbol(),
            orderBookEntry.getMarketOrder().getPrice(),
            orderBookEntry.getStopOrder().getPrice(),
            orderBookEntry.getTakeProfitOrder().getPrice(),
            orderBookEntry.getMarketOrder().getSide(),
            executionType,
            orderBookEntry.getMarketOrder().getQuantity()
        )
         {

        }

        const Timestamp & getTimestamp() const { return timestamp; }
        std::string getSymbol() const { return symbol; }
        float getPrice() const { return price; }
        float getStopPrice() const { return stopPrice; }
        float getTakeProfitPrice() const { return takeProfitPrice; }
        OrderSide getSide() const { return side; }
        OrderType getExecutionType() const { return executionType; }
        int getQuantity() const { return quantity; }

    };

    class TransactionSummary {
        public:
            int buyCount;
            int sellCount;
            float totalWon;
            float totalLost;            
        // define an << operator that outputs this class elements to the ostream. I want two version for this operator. One for TransactionSummary references and another for TransactionSummary pointers.
        friend std::ostream & operator<<(std::ostream & os, const TransactionSummary & summary) {
            os << "Buy Count: " << summary.buyCount << std::endl;
            os << "Sell Count: " << summary.sellCount << std::endl;
            os << "Total Won: " << summary.totalWon << std::endl;
            os << "Total Lost: " << summary.totalLost << std::endl;
            return os;
        }
    };



}
#endif