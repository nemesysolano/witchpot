#ifndef __FEEDENTRY_MAP_H__
#define __FEEDENTRY_MAP_H__
#include <string>
#include "Timestamp.h"
#include "FeedEntry.h"
#include <sstream>

#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <map>

// Your code goes here
namespace witchpot {
    template <typename T> class Timeseries {
        private:
            std::map<witchpot::Timestamp , std::unique_ptr<T>> entries;
            witchpot::Timestamp  start;
            witchpot::Timestamp  end;
            witchpot::Timestamp  eof;
        public:
            Timeseries() {}
            Timeseries(std::istream & is, const std::string & symbol) {
                std::string line;
                if(is.good()) {
                    witchpot::Timestamp  start (0, 0, 0);
                    witchpot::Timestamp  end (0, 0, 0);
                    witchpot::Timestamp  zero (0, 0, 0);

                    std::getline(is, line); // skip header

                    while (std::getline(is, line)) {
                        T * entry = new T(symbol, line);
                        witchpot::Timestamp  timestamp = entry->getTimestamp();
                        if(start == zero ) {
                            start = timestamp;
                            end = timestamp;
                        } else if(timestamp > end) {
                            end = timestamp;
                        }
                        this -> entries[timestamp] = std::unique_ptr<T>(entry);

                    }
                    this->start = start;
                    this->end = end;
                    this->eof = end.inc(1);
                }
            }
            inline witchpot::Timestamp  getStart() const {return start;}
            inline witchpot::Timestamp  getEnd() const {return end;}
            inline size_t size() const {return entries.size();}
            inline witchpot::Timestamp  getEof() const { return eof; }
            Timestamp next(const Timestamp & timestamp) const {
                if(timestamp < start) {
                    return start;
                } else if(timestamp > end) {
                    return timestamp.inc(1);
                }

                auto next = timestamp.inc(1);
                
                while(next < eof && !contains(next)) {                     
                    ++next;
                }
                return next;
            }
            inline T next(const witchpot::Timestamp  && timestamp) const {return next(timestamp);}            
            inline bool contains(const witchpot::Timestamp  & timestamp) const {return entries.find(timestamp) != entries.end();}

            Timestamp extractDate(Timestamp & timestamp);
            inline Timestamp extractDate(Timestamp && timestamp) { return extractDate(timestamp); }

    };


} // namespace witchpot


#endif