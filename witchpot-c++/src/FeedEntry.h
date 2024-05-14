#ifndef __FEEDENTRY_H__
#define __FEEDENTRY_H__

#include <string>
#include <sstream>
#include "Timestamp.h" 
namespace witchpot {
    class FeedEntry {
        protected:
            std::string symbol;
            witchpot::Timestamp timestamp;
            float open;
            float low;
            float high;
            float close;
            float adjusted_close;
            float volume;
        public:
            
            FeedEntry(const std::string & symbol, const std::string & line);
            FeedEntry(const std::string & symbol, const std::string && line) : FeedEntry(symbol, line) {}
            FeedEntry(const std::string && symbol, const std::string && line) : FeedEntry(symbol, line) {}
            inline const std::string & getSymbol() const {return symbol;}
            inline const Timestamp & getTimestamp() const {return timestamp;}
            inline float getOpen() const {return open;}
            inline float getLow() const {return low;}
            inline float getHigh() const {return high;}
            inline float getClose() const {return close;}
            inline float getAdjustedClose() const {return adjusted_close;}
            inline float getVolume() const {return volume;}
            std::ostream& operator<<(std::ostream &os);
    };

    
}
#endif