#include "TAProfitDataGenSchema.h"
#include "TACandleOmen.h"
#include <random>
#include <iostream>

using namespace witchpot;
using namespace std;
const string TAProfitDataGenSchema_name("RandomEntrySchema");
const string witchpot::DIRECTION_LABEL("direction");
const string witchpot::WEIGHT_LABEL("weight");
const string witchpot::OPEN_LABEL("open");
const string witchpot::CLOSE_LABEL("close");
const string witchpot::HIGH_LABEL("high");
const string witchpot::LOW_LABEL("low");
const string witchpot::STOP_LOSS_LABEL("stop_loss");
const string witchpot::TAKE_PROFIT_LABEL("take_profit");
const string witchpot::PRICE_LABEL("price");
const string witchpot::RESULT_LABEL("result");
const string witchpot::VOLUME_LABEL("volume");
const float witchpot::DIRECTION_VALUE_SELL = -1;
const float witchpot::DIRECTION_VALUE_BUY = 1;

const std::string & TAProfitDataGenSchema::name() {
    return TAProfitDataGenSchema_name;
}

TAProfitDataGenSchema::TAProfitDataGenSchema(): rd(new random_device()), gen(new mt19937((*rd)())) {
}

void TAProfitDataGenSchema::apply(
    const Timeseries<FeedEntry> & timeSeries,
    const std::map<std::string, std::unique_ptr<Omen>> & omens,
    Timestamp & current,
    OrderBook & orderBook
) {
    auto tomorrow = timeSeries.next(current);

    if(
        omens.find(TACandleOmen::name()) != omens.end() && 
        timeSeries.contains(tomorrow)
    ) { 
        TACandleOmen & omen = dynamic_cast<TACandleOmen &>(*omens.at(TACandleOmen::name()));       
        auto symbol = (*(timeSeries.get(tomorrow)))->getSymbol();        
        auto entry = *(timeSeries.get(tomorrow));
        int weight = omen;
        uniform_real_distribution<float> priceDist(min(entry->getOpen(), entry->getClose()), max(entry->getOpen(), entry->getClose()));        
        uniform_real_distribution<float> limitDist(0.01, 1);
        auto price = priceDist(*gen);    

        float stop_rate = limitDist(*gen);
        float stop;
        float limit_rate = limitDist(*gen);
        float limit;

        if(((int)abs(weight * 100)) > 0) {
            stop =  price * (1 + stop_rate);
            limit = price * (1 - limit_rate);
            orderBook.createSellOrder(
                tomorrow,
                symbol,
                price,
                1,
                stop,
                limit,
                {
                    {STOP_LOSS_LABEL, stop_rate * -1},
                    {TAKE_PROFIT_LABEL, limit_rate},
                    {WEIGHT_LABEL, weight}
                }
            );

            stop = price  * (1 - stop_rate);
            limit = price * (1 + limit_rate);
            orderBook.createBuyOrder(
                tomorrow,
                symbol,
                price,
                1,
                stop,
                limit,
                {
                    {STOP_LOSS_LABEL, stop_rate * -1},
                    {TAKE_PROFIT_LABEL, limit_rate},
                    {WEIGHT_LABEL, weight}       
                }
            );               
        } 

    }
}

TAProfitDataGenSchema::~TAProfitDataGenSchema() {
    Schema::~Schema();
    delete gen;
    delete rd;
}