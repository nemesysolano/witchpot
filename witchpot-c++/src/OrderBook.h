#ifndef __ORDER_BOOK_H__
#define __ORDER_BOOK_H__
#include "Timeseries.h"
#include "Order.h"
#include <set>
#include <map>
#include <memory>
namespace witchpot {
    struct OrderBookEntry {
        OrderStatus status;
        std::string orderId;
        std::string limitOrderId;
        std::string stopOrderId;
        OrderBookEntry(OrderStatus status, std::string orderId, std::string limitOrderId, std::string stopOrderId): status(status), orderId(orderId), limitOrderId(limitOrderId), stopOrderId(stopOrderId) {}
    };

    class OrderBook{
        protected:
            std::set<std::string> pendingOrderEntries;
            std::set<std::string> acceptedOrderEntries;
            std::set<std::string> failedOrderEntries;
            std::set<std::string> cancelledOrderEntries;            
            std::set<std::string> filledOrderEntries;
            std::map<std::string, std::unique_ptr<Order>> allOrderEntries;            
            std::unique_ptr<OrderBookEntry> createOrder(
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit,
                OrderSide side
            );
        public:
            OrderBook() {}
            OrderBook(const OrderBook & orderBook) = delete;
            OrderBook & operator=(const OrderBook & orderBook) = delete;
            OrderBook(OrderBook && orderBook) = delete;
            OrderBook & operator=(OrderBook && orderBook) = delete;

            std::unique_ptr<OrderBookEntry> createBuyOrder (
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit
            );

            std::unique_ptr<OrderBookEntry> createSellOrder (
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit
            );            
    };
}
#endif