#ifndef __STOP_LOSS_TAKE_PROFIT_GENERATOR_SCHEMA_H__
#define __STOP_LOSS_TAKE_PROFIT_GENERATOR_SCHEMA_H__
#include "Schema.h"
#include "FeedEntry.h"
#include <iostream>
#include <random>
namespace witchpot {
    extern const std::string DIRECTION_LABEL;
    extern const std::string WEIGHT_LABEL;
    extern const std::string OPEN_LABEL;
    extern const std::string CLOSE_LABEL;
    extern const std::string HIGH_LABEL;
    extern const std::string LOW_LABEL;
    extern const std::string STOP_LOSS_LABEL;
    extern const std::string TAKE_PROFIT_LABEL;
    extern const std::string PRICE_LABEL;
    extern const std::string VOLUME_LABEL;
    extern const std::string RESULT_LABEL;
    extern const float DIRECTION_VALUE_SELL;
    extern const float DIRECTION_VALUE_BUY;

    class TAProfitDataGenSchema : public Schema {
        std::random_device * rd;
        std::mt19937 * gen; 

        public:
            TAProfitDataGenSchema();
            static const std::string & name();    
            virtual void apply(
                const Timeseries<FeedEntry> & timeSeries,
                const std::map<std::string, std::unique_ptr<Omen>> & omens,
                Timestamp & current,
                OrderBook & orderBook
            );
            virtual ~TAProfitDataGenSchema();

    };
}
#endif // __STOP_LOSS_TAKE_PROFIT_GENERATOR_SCHEMA_H__