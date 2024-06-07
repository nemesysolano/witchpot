#ifndef INDICATOR_H
#define INDICATOR_H
#include "Timeseries.h"
#include <vector>
#include <iostream>

// Your code here
namespace witchpot {
    class Omen {        // aka Indicator
        protected:
            std::vector<std::vector<float>> result;
        public:
            inline Omen(size_t rows, size_t columns) {
                this->result = std::vector<std::vector<float>>(rows, std::vector<float>(columns, 0));
            }
            virtual size_t rowSize() const;
            virtual size_t colSize() const;
            virtual void calculate(const Timeseries<FeedEntry> & timeSeries, const Timestamp & current);
            virtual float at(size_t row, size_t column) const;
            virtual float at(size_t column) const;
            inline operator float () const {
                return this->result[0][0];
            }
            virtual ~Omen() = default;
    };
}

#endif // INDICATOR_H