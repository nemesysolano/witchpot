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
        std::string orderEntryId;
    public:
        Transaction(
            const Timestamp & timestamp_,
            std::string symbol_,
            float price_,
            float stopPrice_,
            float takeProfitPrice_,
            OrderSide side_,
            OrderType executionType_,
            int quantity_,
            const std::string & orderEntryId_
        ): timestamp(timestamp_),
            symbol(symbol_),
            price(price_),
            stopPrice(stopPrice_),
            takeProfitPrice(takeProfitPrice_),
            side(side_),
            executionType(executionType_),
            quantity(quantity_),
            orderEntryId(orderEntryId_) {

        }        

        Transaction(
            const Timestamp & timestamp_,
            std::string symbol_,
            float price_,
            float stopPrice_,
            float takeProfitPrice_,
            OrderSide side_,
            OrderType executionType_,
            int quantity_,
            const std::string && orderEntryId_
        ): timestamp(timestamp_),
            symbol(symbol_),
            price(price_),
            stopPrice(stopPrice_),
            takeProfitPrice(takeProfitPrice_),
            side(side_),
            executionType(executionType_),
            quantity(quantity_),
            orderEntryId(orderEntryId_) {
        }

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
            orderBookEntry.getMarketOrder().getQuantity(),
            orderBookEntry.getOrderId()
        )
         {

        }

        inline const Timestamp & getTimestamp() const { return timestamp; }
        inline const std::string & getSymbol() const { return symbol; }
        inline float getPrice() const { return price; }
        inline float getStopPrice() const { return stopPrice; }
        inline float getTakeProfitPrice() const { return takeProfitPrice; }
        inline float getProfit() const { return takeProfitPrice - price; }
        inline OrderSide getSide() const { return side; }
        inline OrderType getExecutionType() const { return executionType; }
        inline int getQuantity() const { return quantity; }
        inline const std::string & getOrderEntryId() const { return orderEntryId; }        
    };

    class TransactionSummary {
        public:
            int buyCount = 0;
            int sellCount = 0;
            float totalWon = 0.0;
            float totalLost = 0.0;            
        // define an << operator that outputs this class elements to the ostream. I want two version for this operator. One for TransactionSummary references and another for TransactionSummary pointers.
        friend std::ostream & operator<<(std::ostream & os, const TransactionSummary & summary) {
            os << "(buy_count=" << summary.buyCount;
            os << ", sell_count=" << summary.sellCount;
            os << ", net_profit=" << summary.totalWon - summary.totalLost;
            os << ", total_won=" << summary.totalWon;
            os << ", total_lost=" << summary.totalLost << ')';
            return os;
        }
    };



}
#endif