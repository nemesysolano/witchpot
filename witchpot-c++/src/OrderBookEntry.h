#ifndef __ORDER_BOOK_ENTRY_H__
#define __ORDER_BOOK_ENTRY_H__
#include "Order.h"
namespace witchpot {
    struct OrderBookEntry {
        private:
            OrderStatus status;
            MarketOrder * order;
            TakeProfitOrder * limitOrder;
            StopOrder * stopOrder;
        public:

        OrderBookEntry(
            MarketOrder * order_,
            TakeProfitOrder * limitOrder_,
            StopOrder * stopOrder_
        ): status(OrderStatus::ACCEPTED), order(order_), limitOrder(limitOrder_), stopOrder(stopOrder_) {
            
        }
        OrderBookEntry(std::string symbol,
            Timestamp & timestamp,
            float price,
            int quantity,
            float stop,
            float takeProfit,
            OrderSide side
        ) ;

        inline OrderBookEntry(std::string symbol,
            Timestamp & timestamp,
            float price,
            float stop,
            float takeProfit,
            OrderSide side
        ): OrderBookEntry(symbol, timestamp, price, 1, stop, takeProfit, side) {            
        }

        inline const MarketOrder & getMarketOrder() const {
            return *order;
        }

        inline const TakeProfitOrder & getTakeProfitOrder() const {
            return *limitOrder;
        }

        inline const StopOrder & getStopOrder() const {
            return *stopOrder;
        }

        inline OrderStatus getStatus() const {
            return status;
        }

        virtual ~OrderBookEntry();
    };
    

}

#endif