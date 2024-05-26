#ifndef __ORDER_BOOK_H__
#define __ORDER_BOOK_H__
#include "Timeseries.h"
#include "OrderBookEntry.h"
#include <set>
#include <map>
#include <memory>
namespace witchpot {
    class OrderBook{
        private:
            std::unordered_map<std::string, const OrderBookEntry *> * orderEntries;
            std::unordered_map<std::string, const OrderBookEntry *> * acceptedOrderEntries;
            std::unordered_map<std::string, const OrderBookEntry *> * filledOrderEntries;
            std::unordered_map<std::string, const OrderBookEntry *> * cancelledOrderEntries;
            bool is_owner;
            const OrderBookEntry & createOrder(
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit,
                OrderSide side
            );
        public:
            OrderBook(): is_owner(true) {
                orderEntries = new std::unordered_map<std::string, const OrderBookEntry *>();
                acceptedOrderEntries = new std::unordered_map<std::string, const OrderBookEntry *>();
                filledOrderEntries = new std::unordered_map<std::string, const OrderBookEntry *>();
                cancelledOrderEntries = new std::unordered_map<std::string, const OrderBookEntry *>();
            }
            OrderBook(const OrderBook && other) = delete;
            OrderBook & operator=(const OrderBook && other) = delete;
            OrderBook(const OrderBook & other);
            OrderBook & operator=(const OrderBook & other);

            const OrderBookEntry & createBuyOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit
            );

            inline const OrderBookEntry & createBuyOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                float stop,
                float limit
            ) { return createBuyOrder(timestamp, symbol, price, 1, stop, limit); }

            const OrderBookEntry & createSellOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit
            );   

            inline const OrderBookEntry & createSellOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                float stop,
                float limit
            ) { return createSellOrder(timestamp, symbol, price, 1, stop, limit); } 

            std::vector<const OrderBookEntry *> fillOrders(std::function<bool(const OrderBookEntry &)> filterFunc); // This function is not thread safe
            std::vector<const OrderBookEntry *> acceptedOrders(std::function<bool(const OrderBookEntry &)> filterFunc);// This function is not thread safe
            std::vector<const OrderBookEntry *> acceptedOrders();// This function is not thread safe
            inline size_t acceptedOrdersCount() const { return acceptedOrderEntries->size(); }// This function is not thread safe

            virtual ~OrderBook();
            
    };
}
#endif