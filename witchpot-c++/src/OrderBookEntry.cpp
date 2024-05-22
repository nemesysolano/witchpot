#include "OrderBookEntry.h"
#include <sstream>
#include <random>
using namespace std;
using namespace witchpot;

static void scramble_string(string& text) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(text.begin(), text.end(), gen);
}

static string createOrderId(
    Timestamp & timestamp,
    std::string & symbol,
    float price,
    int quantity,
    float stop,
    float limit,    
    OrderSide side,
    OrderType type
) {
    stringstream ss;
    ss << timestamp << ',' << symbol << ',' << price << ',' << quantity << ',' << stop << ',' << limit << ',' << side << ',' << side << ',' << type;    
    string clerText = ss.str();
    scramble_string(clerText);
    return clerText;
}

OrderBookEntry::OrderBookEntry(std::string symbol,
    Timestamp & timestamp,
    float price,
    int quantity,
    float stop,
    float takeProfit,
    OrderSide side
) {
    this->order = new MarketOrder(         
        timestamp,
        createOrderId(timestamp, symbol, price, quantity, stop, takeProfit, side, OrderType::MARKET),
        symbol,
        price,
        quantity,
        side
    );
    
    this->limitOrder = new TakeProfitOrder(
        createOrderId(timestamp, symbol, price, quantity, stop, takeProfit, side, OrderType::TAKE_PROFIT),
        takeProfit,                
        *order
    );

    this->stopOrder = new StopOrder(
        createOrderId(timestamp, symbol, price, quantity, stop, takeProfit, side, OrderType::STOP),
        stop,                
        *order
    );
}

OrderBookEntry::~OrderBookEntry() {
    delete order;
    delete limitOrder;
    delete stopOrder;
}
 