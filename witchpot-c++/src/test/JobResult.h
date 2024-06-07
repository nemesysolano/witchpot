#ifndef __RANDOM_ENTRY_SCHEMA_JOB_RESULT_H__
#define __RANDOM_ENTRY_SCHEMA_JOB_RESULT_H__
#include "TransactionLog.h"
#include <string>
#include <vector>
#include <filesystem>
namespace witchpot {
    class JobResult {
        private:
            float stopLossRate;
            float takeProfitRate;
            TransactionSummary summary;            
            int orderEntriesCount;
            int acceptedOrdersCount;
            int filledOrdersCount;
            int cancelledOrdersCount;

        public:
            inline JobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary & summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            ) : stopLossRate(stopLossRate), 
                takeProfitRate(takeProfitRate), 
                summary(summary), 
                acceptedOrdersCount(acceptedOrdersCount), 
                filledOrdersCount(filledOrdersCount), 
                cancelledOrdersCount(cancelledOrdersCount) {}   

            inline JobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary && summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            ) : stopLossRate(stopLossRate), 
                takeProfitRate(takeProfitRate), 
                summary(std::move(summary)), 
                acceptedOrdersCount(acceptedOrdersCount), 
                filledOrdersCount(filledOrdersCount), 
                cancelledOrdersCount(cancelledOrdersCount) {}
            inline float getStopLossRate() const {
                return stopLossRate;
            }
            inline float getTakeProfitRate() const {
                return takeProfitRate;
            }
            inline const TransactionSummary & getSummary() const {
                return summary;
            }
            inline int getOrderEntriesCount() const {
                return orderEntriesCount;
            }
            inline int getAcceptedOrdersCount() const {
                return acceptedOrdersCount;
            }
            inline int getFilledOrdersCount() const {
                return filledOrdersCount;
            }
            inline int getCancelledOrdersCount() const {
                return cancelledOrdersCount;
            }

    };
    std::ostream & operator<<(std::ostream & os, const JobResult & result);
}
#endif