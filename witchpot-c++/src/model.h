#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <map>
#include "Timestamp.h"
#include "FeedEntry.h"
// Your code goes here
namespace witchpot {
     

    class FeedEntryMap {
        private:
            std::map<Timestamp, std::unique_ptr<FeedEntry>> entries;
            Timestamp start;
            Timestamp end;
            Timestamp eof;
        public:
            FeedEntryMap() {}
            FeedEntryMap(std::istream & is, const std::string & symbol) {
                std::string line;
                if(is.good()) {
                    Timestamp start (0, 0, 0);
                    Timestamp end (0, 0, 0);
                    Timestamp zero (0, 0, 0);

                    std::getline(is, line); // skip header
            
                    while (std::getline(is, line)) {
                        FeedEntry * entry = new FeedEntry(symbol, line);
                        Timestamp timestamp = entry->getTimestamp();
                        if(start == zero ) {
                            start = timestamp;
                            end = timestamp;
                        } else if(timestamp > end) {
                            end = timestamp;
                        }
                        this -> entries[timestamp] = std::unique_ptr<FeedEntry>(entry);

                    }
                    this->start = start;
                    this->end = end;
                    this->eof = end.inc(1);
                }
            }
            FeedEntryMap(std::istream & is, const std::string && symbol): FeedEntryMap(is, symbol) {}
            inline Timestamp getStart() const {return start;}
            inline Timestamp getEnd() const {return end;}
            inline size_t size() const {return entries.size();}
            inline Timestamp getEof() const { return eof; }
            Timestamp next(const Timestamp & timestamp) const;
            inline Timestamp next(const Timestamp && timestamp) const {return next(timestamp);}            
            inline bool contains(const Timestamp & timestamp) const {return entries.find(timestamp) != entries.end();}
    };

    std::ostream& operator<<(std::ostream &os, const FeedEntry& feedEntry);

    class Feed{
       protected:
            FeedEntryMap & feed_map;
            Timestamp current;
        public:
            Feed(FeedEntryMap & feed_map): feed_map(feed_map), current(feed_map.getStart()) {}
            Feed()=delete;    
            Feed(Feed const&)=delete;
            Feed(Feed &&)=delete;
            inline Timestamp getCurrent() const {return current;}
            inline Timestamp inc(int delta) {current = current.inc(delta); return current;}
    };

} // namespace witchpot

#endif // MODEL_H