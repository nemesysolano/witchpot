#ifndef __ORDER_BOOK_ENTRY_H__
#define __ORDER_BOOK_ENTRY_H__
#include "Order.h"
#include <map>
namespace witchpot {
    struct OrderBookEntry {
        private:
            OrderStatus status;
            MarketOrder order ;
            TakeProfitOrder limitOrder;
            StopOrder stopOrder;
            std::map<std::string, float> additionalInfo;
        public:

        OrderBookEntry(
            MarketOrder & order_,
            TakeProfitOrder & limitOrder_,
            StopOrder & stopOrder_
        ): status(OrderStatus::ACCEPTED), order(order_), limitOrder(limitOrder_), stopOrder(stopOrder_), additionalInfo({}) {            
        }

        inline OrderBookEntry(
            MarketOrder & order_,
            TakeProfitOrder & limitOrder_,
            StopOrder & stopOrder_,
            std::map<std::string, float> & additionalInfo_
        ): status(OrderStatus::ACCEPTED), order(order_), limitOrder(limitOrder_), stopOrder(stopOrder_), additionalInfo(additionalInfo_) {            
        }     

        OrderBookEntry(std::string symbol,
            Timestamp & timestamp,
            float price,
            int quantity,
            float stop,
            float takeProfit,
            OrderSide side
        ) ;

        OrderBookEntry(std::string symbol,
            Timestamp & timestamp,
            float price,
            int quantity,
            float stop,
            float takeProfit,
            OrderSide ,
            std::map<std::string, float> & additionalInfo_
        );

        inline OrderBookEntry(std::string symbol,
            Timestamp & timestamp,
            float price,
            int quantity,
            float stop,
            float takeProfit,
            OrderSide side,
            std::map<std::string, float> && additionalInfo_
        ): OrderBookEntry(symbol, timestamp, price, quantity, stop, takeProfit, side, additionalInfo_){            
        }

        inline OrderBookEntry(std::string symbol,
            Timestamp & timestamp,
            float price,
            float stop,
            float takeProfit,
            OrderSide side
        ): OrderBookEntry(symbol, timestamp, price, 1, stop, takeProfit, side){            
        }

        inline const MarketOrder & getMarketOrder() const {
            return order;
        }

        inline const TakeProfitOrder & getTakeProfitOrder() const {
            return limitOrder;
        }

        inline const StopOrder & getStopOrder() const {
            return stopOrder;
        }

        inline OrderStatus getStatus() const {
            return status;
        }

        inline const std::string & getOrderId() const {
            return order.getOrderId();
        }
        
        inline const std::map<std::string, float> & getAdditionalInfo() const {
            return additionalInfo;
        }
        
        virtual ~OrderBookEntry();
    };
    

}

#endif