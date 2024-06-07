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
            std::unordered_map<std::string, const OrderBookEntry *> * allOrderEntries = nullptr;
            bool is_owner;
            void createOrder(
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit,
                OrderSide side,
                std::map<std::string, float> & additionalInfo
            );
        public:
            OrderBook():                
                acceptedOrderEntries(new std::unordered_map<std::string, const OrderBookEntry *>()),
                filledOrderEntries(new std::unordered_map<std::string, const OrderBookEntry *>()),
                cancelledOrderEntries(new std::unordered_map<std::string, const OrderBookEntry *>()),
                allOrderEntries(new std::unordered_map<std::string, const OrderBookEntry *>()),
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
                float takeProfit,
                std::map<std::string, float> & additionalInfo
            );

            inline void createBuyOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float takeProfit,
                std::map<std::string, float> && additionalInfo_
            )  {
                createBuyOrder(timestamp, symbol, price, quantity, stop, takeProfit, additionalInfo_);
            }

            inline void createBuyOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float takeProfit
            ) {
                std::map<std::string, float> additionalInfo;
                createBuyOrder(timestamp, symbol, price, quantity, stop, takeProfit, additionalInfo);
            }

            void createSellOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit,
                std::map<std::string, float> & additionalInfo
            );   

            void createSellOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit,
                std::map<std::string, float> && additionalInfo_
            ) {
                createSellOrder(timestamp, symbol, price, quantity, stop, limit, additionalInfo_);
            } 

            inline void createSellOrder (
                Timestamp & timestamp,
                std::string symbol,
                float price,
                int quantity,
                float stop,
                float limit
            ) {
                std::map<std::string, float> additionalInfo;
                createSellOrder(timestamp, symbol, price, quantity, stop, limit, additionalInfo); 
            }

            std::vector<const OrderBookEntry *> fillOrders(const Timeseries<FeedEntry> & timeSeries, const Timestamp & current); // This function is not thread safe
            
            inline int acceptedOrdersCount() const { return (int)acceptedOrderEntries->size(); }// This function is not thread safe
            inline int filledOrdersCount() const { return (int)filledOrderEntries->size(); }// This function is not thread safe
            inline int cancelledOrdersCount() const { return (int)cancelledOrderEntries->size(); }// This function is not thread 
            inline const OrderBookEntry & operator [] (const std::string &  orderId) const { return *allOrderEntries->at(orderId); }// This function is not thread safe  
            inline const OrderBookEntry & operator [] (const std::string && orderId) const { return *allOrderEntries->at(orderId); }// This function is not thread safe  
            virtual ~OrderBook();
            
    };
}
#endif