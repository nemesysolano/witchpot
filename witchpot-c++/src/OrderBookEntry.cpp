#include "OrderBookEntry.h"
#include <sstream>
#include <random>
#include "Memory.h"
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
) : order(
        timestamp,
        createOrderId(timestamp, symbol, price, quantity, stop, takeProfit, side, OrderType::MARKET),
        symbol,
        price,
        quantity,
        side  
    ),
    limitOrder(
        createOrderId(timestamp, symbol, price, quantity, stop, takeProfit, side, OrderType::TAKE_PROFIT),
        takeProfit,                
        order
    ),
    stopOrder(
        createOrderId(timestamp, symbol, price, quantity, stop, takeProfit, side, OrderType::STOP),
        stop,                
        order
    ) 
 {
    
}

OrderBookEntry::~OrderBookEntry() {
    
}
 