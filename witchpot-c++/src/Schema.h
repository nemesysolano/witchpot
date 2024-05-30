#ifndef STRATEGY_H
#define STRATEGY_H
#include "OrderBook.h"
#include "Timeseries.h"
#include "Omen.h"
namespace witchpot {
    class Schema { //aka Strategy
    public:
        virtual void apply(
            const Timeseries<FeedEntry> &,
            const std::map<std::string, std::unique_ptr<Omen>> & omens,
            Timestamp & current,
            OrderBook & orderBook
        );
        inline void operator () (
            const Timeseries<FeedEntry> & timeSeries,
            const std::map<std::string, std::unique_ptr<Omen>> & omens,
            Timestamp & current,
            OrderBook & orderBook
        ) { apply( timeSeries, omens, current, orderBook); }

        virtual ~Schema();
    };

    
};
// Your code here

#endif // STRATEGY_H