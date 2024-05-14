#ifndef __ORDER_H__
#define __ORDER_H__

#include <string>
#include "Timestamp.h"

namespace witchpot {
    enum OrderSide {
        SELL, BUY
    };

    enum OrderType {
        MARKET, // A market order is an order to buy or sell a security immediately.
        LIMIT,  // A limit order is an order to buy or sell a security at a specific price or better.
        STOP, // A stop order is an order to buy or sell a security when its price moves past a particular point, ensuring a higher probability of achieving a predetermined entry or exit price.
    };

    enum OrderStatus {
        PENDING, // Order has been created but not yet processed. Main, stop and limit orders are in this state.
        ACCEPTED, // Order has been accepted by the exchange. Main, stop and limit orders are in this state.
        FAILED, // Order has been rejected by the exchange. Main, stop and limit orders are in this state.
        CANCELLED, // Order has been cancelled by the user
        FILLED // Order has been filled by the exchange. Main order is in this state while only one of stop or limit order is in this state at a time and the other is in cancelled state.
    };

    class Order {
        protected:
            Timestamp timestamp;
            std::string orderId;            
            std::string symbol;
            float price;
            int quantity;
            OrderSide side;
            OrderType type;
            std::string parentOrderId;
        public:
            Order(
                Timestamp timestamp,
                std::string orderId,
                std::string symbol,
                float price,
                int quantity,
                OrderSide side,
                OrderType type,
                std::string parentOrderId
            ): timestamp(timestamp), orderId(orderId), symbol(symbol), price(price), quantity(quantity), side(side), type(type), parentOrderId(parentOrderId) {}
        Order(
                Timestamp timestamp,
                std::string orderId,
                std::string symbol,
                float price,
                int quantity,
                OrderSide side,
                OrderType type
            ): timestamp(timestamp), orderId(orderId), symbol(symbol), price(price), quantity(quantity), side(side), type(type){}       
        // generate java like getters
        inline const Timestamp & getTimestamp() const {return timestamp;}
        inline const std::string & getOrderId() const {return orderId;}
        inline const std::string & getSymbol() const {return symbol;}
        inline float getPrice() const {return price;}
        inline int getQuantity() const {return quantity;}
        inline OrderSide getSide() const {return side;}
        inline OrderType getType() const {return type;}
        inline const std::string & getParentOrderId() const {return parentOrderId;}

    };

    class MarketOrder: public Order {
        public:
            MarketOrder(
                Timestamp timestamp,
                std::string orderId,
                std::string symbol,
                float price,
                int quantity,
                OrderSide side
            ): Order(timestamp, orderId, symbol, price, quantity, side, MARKET) {}
    };

    class LimitOrder: public Order {
        public:
            LimitOrder(
                std::string orderId,
                float price,                
                MarketOrder & parentOrder
            ): Order(
                parentOrder.getTimestamp(), 
                orderId, 
                parentOrder.getSymbol(), 
                price, 
                parentOrder.getQuantity(), 
                parentOrder.getSide() == BUY ? SELL : BUY, 
                LIMIT, 
                parentOrder.getOrderId()
            ) {}
    };

    class StopOrder: public Order {
        public:
            StopOrder(
                std::string orderId,
                float price,                
                MarketOrder & parentOrder
            ): Order(
                parentOrder.getTimestamp(), 
                orderId, 
                parentOrder.getSymbol(), 
                price, 
                parentOrder.getQuantity(), 
                parentOrder.getSide() == BUY ? SELL : BUY, 
                STOP, 
                parentOrder.getOrderId()
            ) {}
    };
}
#endif