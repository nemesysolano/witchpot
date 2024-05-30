#ifndef __DRIVER_H__
#define __DRIVER_H__
#include <string>
#include <map>
#include "TransactionLog.h"
#include "FeedEntry.h"
#include "OrderBook.h"
#include "Schema.h"
#include "Omen.h"
#include <memory>
#include "Timeseries.h"

namespace witchpot {
    class Driver {
        protected:
            const std::map<std::string, std::unique_ptr<Schema>> & schemaMap;
            const std::map<std::string, std::unique_ptr<Omen>> & omenMap;
            const Timeseries<FeedEntry> & timeSeries;
            OrderBook * orderBook;
            TransactionLog * transactionLog;
            
        public:
            Driver(
                const Timeseries<FeedEntry> & timeSeries_,
                const std::map<std::string, std::unique_ptr<Schema>> & schemaMap_,
                const std::map<std::string, std::unique_ptr<Omen>> & omenMap_
            ): schemaMap(schemaMap_), omenMap(omenMap_), timeSeries(timeSeries_), orderBook(new OrderBook()), transactionLog(new TransactionLog()) {}
           

            void run();
            std::vector<const OrderBookEntry *> fillOrders(const Timestamp & current);
            void createTransactions(const std::vector<const OrderBookEntry *> & filledOrders, const Timestamp & current);      
            void checkOmens(const Timestamp & current);
            void applySchemas(Timestamp & current);
            inline OrderBook & getOrderBook() {return *orderBook;}
            inline TransactionLog & getTransactionLog() { return *transactionLog;}
            virtual ~Driver() {
                delete orderBook;
                delete transactionLog;
            }
    };

};
#endif 