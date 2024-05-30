#include "RandomEntrySchema.h"
#include "omens/RandomEntryOmen.h"
#include <random>
using namespace witchpot;
using namespace std;

const string RandomEntrySchema_name("RandomEntrySchema");

const string & RandomEntrySchema::name() {
    return RandomEntrySchema_name;
}   

void RandomEntrySchema::apply(
    const Timeseries<FeedEntry> & timeSeries,
    const std::map<std::string, std::unique_ptr<Omen>> & omens,
    Timestamp & current,
    OrderBook & orderBook
) {
    if(
        omens.find(RandomEntryOmen::name()) != omens.end() && 
        timeSeries.contains(current) &&
        current < timeSeries.getEnd()
    ) {
        random_device rd;
        mt19937 gen(rd()); 
        auto symbol = (*(timeSeries.get(current)))->getSymbol();
        auto direction = (float)(*omens.at(RandomEntryOmen::name()));
        auto entry = *(timeSeries.get(current));

        uniform_real_distribution<float> priceDist(min(entry->getOpen(), entry->getClose()), max(entry->getOpen(), entry->getClose()));
        uniform_real_distribution<float> limitDist(0.05, 1);
        auto price = priceDist(gen);
        float stop;
        float limit;

        if(direction < 0) {
            stop = price * (1+limitDist(gen));
            limit = price * (1-limitDist(gen));

            orderBook.createSellOrder(
                current,
                symbol,
                price,
                stop,
                limit
            );
        } else if(direction > 0) {
            stop = price * (1-limitDist(gen));
            limit = price * (1+limitDist(gen));

            orderBook.createBuyOrder(
                current,
                symbol,
                price,
                stop,
                limit
            );
        }
        
    }
}