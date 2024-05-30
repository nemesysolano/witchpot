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
            std::unordered_map<std::string, const OrderBookEntry *> * acceptedOrderEntries = nullptr;
            std::unordered_map<std::string, const OrderBookEntry *> * filledOrderEntries = nullptr;
            std::unordered_map<std::string, const OrderBookEntry *> * cancelledOrderEntries = nullptr;
            bool is_owner;
            void createOrder(
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit,
                OrderSide side
            );
        public:
            OrderBook():                
                acceptedOrderEntries(new std::unordered_map<std::string, const OrderBookEntry *>()),
                filledOrderEntries(new std::unordered_map<std::string, const OrderBookEntry *>()),
                cancelledOrderEntries(new std::unordered_map<std::string, const OrderBookEntry *>()),
                is_owner(true)
             {
            }
            OrderBook(const OrderBook && other) = delete;
            OrderBook & operator=(const OrderBook && other) = delete;
            OrderBook(const OrderBook & other);
            OrderBook & operator=(const OrderBook & other);

            void createBuyOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit
            );

            inline void createBuyOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                float stop,
                float limit
            ) { createBuyOrder(timestamp, symbol, price, 1, stop, limit); }

            void createSellOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit
            );   

            inline void createSellOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                float stop,
                float limit
            ) { createSellOrder(timestamp, symbol, price, 1, stop, limit); } 

            std::vector<const OrderBookEntry *> fillOrders(const Timeseries<FeedEntry> & timeSeries, const Timestamp & current); // This function is not thread safe
            
            inline int acceptedOrdersCount() const { return (int)acceptedOrderEntries->size(); }// This function is not thread safe
            inline int filledOrdersCount() const { return (int)filledOrderEntries->size(); }// This function is not thread safe
            inline int cancelledOrdersCount() const { return (int)cancelledOrderEntries->size(); }// This function is not thread safe
            virtual ~OrderBook();
            
    };
}
#endif