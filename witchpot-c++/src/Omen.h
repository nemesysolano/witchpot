#ifndef INDICATOR_H
#define INDICATOR_H
#include "Timeseries.h"
#include <vector>
#include <iostream>

// Your code here
namespace witchpot {
    class Omen {        // aka Indicator
        protected:
            std::vector<float> result;
        public:
            virtual size_t rowSize();
            virtual size_t colSize();
            virtual void calculate(const Timeseries<FeedEntry> & timeSeries, const Timestamp & current);
            virtual const std::vector<float> & getResult(size_t) const;
            virtual const std::vector<float> & getResult() const;
            virtual ~Omen() = default;
    };
}

#endif // INDICATOR_H