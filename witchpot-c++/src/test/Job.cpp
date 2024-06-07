#include "Job.h"

using namespace witchpot;
void Job::createJobResult(
    float stopLossRate,
    float takeProfitRate,
    TransactionSummary && summary,
    int acceptedOrdersCount,
    int filledOrdersCount,
    int cancelledOrdersCount
) {
    results.push_back(new JobResult(
        stopLossRate, 
        takeProfitRate, 
        std::move(summary), 
        acceptedOrdersCount, 
        filledOrdersCount, 
        cancelledOrdersCount
    ));
}

void Job::createJobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary & summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            ) {
    results.push_back(new JobResult(
        stopLossRate, 
        takeProfitRate, 
        summary, 
        acceptedOrdersCount, 
        filledOrdersCount, 
        cancelledOrdersCount
    ));
}


Job::~Job() {
    for (auto result : results) {
        delete result;
    }
}
