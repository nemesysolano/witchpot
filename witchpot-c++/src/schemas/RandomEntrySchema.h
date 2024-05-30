#ifndef __RANDOM_ENTRY_SCHEMA_H__
#define __RANDOM_ENTRY_SCHEMA_H__
#include "Schema.h"
#include "Driver.h"


namespace witchpot {
    class RandomEntrySchema : public Schema {

        public:
            static const std::string & name();    
            virtual void apply(
                const Timeseries<FeedEntry> & timeSeries,
                const std::map<std::string, std::unique_ptr<Omen>> & omens,
                Timestamp & current,
                OrderBook & orderBook
            );
    };


}

#endif