#ifndef __TRANSACTIONLOG_H__
#define __TRANSACTIONLOG_H__

#include "Transaction.h"
#include <vector>
#include <memory>

namespace witchpot {
    class TransactionLog {
        protected:
            std::vector<Transaction *> * transactions;
            bool is_owner;
        public:
            TransactionLog(): transactions(new std::vector<Transaction *>()), is_owner(true)  {}
            TransactionLog(const TransactionLog && other) = delete;
            TransactionLog & operator=(const TransactionLog && other) = delete;
            TransactionLog(const TransactionLog & other);
            TransactionLog & operator=(const TransactionLog & other);
            inline const Transaction & operator[](size_t index) const {
                return *transactions->at(index);
            }
            inline size_t size() const {
                return transactions->size();
            }
            inline void add(
                const Timestamp & timestamp,
                const OrderBookEntry & orderBookEntry,
                OrderType executionType
            ) {
                transactions->push_back(new Transaction(timestamp, orderBookEntry, executionType));
            }            

            TransactionSummary getTransactionSummary();            
            virtual ~TransactionLog();
    } ;
}
#endif