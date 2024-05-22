#include "Order.h"
#include <string>
using namespace std;
using namespace witchpot;

std::ostream & MarketOrder::operator<<(std::ostream & os) {
    os << "MarketOrder(" << orderId << ',' << price << ',' << symbol << ',' << quantity << ',' << side << ',' << type << ')';
    return os;
}

std::ostream & TakeProfitOrder::operator<<(std::ostream & os) {
    os << "TakeProfitOrder(" << orderId << ',' << price << ',' << symbol << ',' << quantity << ',' << side << ',' << type << ',' << parentOrderId << ')';
    return os;
}

std::ostream & StopOrder::operator<<(std::ostream & os) {
    os << "StopOrder(" << orderId << ',' << price << ',' << symbol << ',' << quantity << ',' << side << ',' << type << ',' << parentOrderId << ')';
    return os;
}
