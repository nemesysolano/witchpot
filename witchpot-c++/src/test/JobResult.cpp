#include "JobResult.h"

std::ostream & witchpot::operator<<(std::ostream & os, const JobResult & result) {
    os << "(sl_rate=" << result.getStopLossRate();
    os << ", tp_rate=" << result.getTakeProfitRate();
    os << ", summary=" << result.getSummary();
    os << ", orders_count=" << result.getOrderEntriesCount();
    os << ", accepted_orders_count=" << result.getAcceptedOrdersCount();
    os << ", filled_orders_count=" << result.getFilledOrdersCount();
    os << ", cancelled_orders_count=" << result.getCancelledOrdersCount() << ')' << std::endl;
    return os;
}