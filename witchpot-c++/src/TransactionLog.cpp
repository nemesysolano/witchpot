#include "TransactionLog.h"
using namespace std;
using namespace witchpot;
TransactionLog::TransactionLog(const TransactionLog & other): is_owner(false) {
    this->transactions = other.transactions;

}
TransactionLog & TransactionLog:: operator=(const TransactionLog & other) {
    this->transactions = other.transactions;
    is_owner = false;
    return *this;
}

TransactionSummary TransactionLog::getTransactionSummary() {
    TransactionSummary summary;
    for (auto & transaction : *transactions) {
        summary.buyCount += transaction->getSide() == OrderSide::BUY;
        summary.sellCount += transaction->getSide() == OrderSide::SELL;

        if (transaction->getExecutionType() == OrderType::STOP) {
            summary.totalLost += abs(transaction->getPrice() -  transaction->getStopPrice() * transaction->getQuantity());    
        }
        else if (transaction->getExecutionType() == OrderType::TAKE_PROFIT) {
            summary.totalWon += abs(transaction->getPrice() - transaction->getTakeProfitPrice() * transaction->getQuantity());            
        }
    }
    return summary;
}


TransactionLog::~TransactionLog() {
    if(is_owner) {
        for(auto & transaction : * transactions) {
            delete transaction;
        }
        delete transactions;
    }
}
// https://en.wikipedia.org/wiki/Hessian_matrix#Use_in_optimization