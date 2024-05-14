#include "FeedEntry.h"
using namespace witchpot;
using namespace std;    
FeedEntry::FeedEntry(const std::string & symbol, const std::string & line) {
    std::istringstream iss(line);
    std::string token;
    
    // Parse the CSV line
    std::getline(iss, token, ','); // timestamp
    Timestamp timestamp(token);
    
    std::getline(iss, token, ','); // open
    float open = std::stof(token);
    
    std::getline(iss, token, ','); // low
    float low = std::stof(token);
    
    std::getline(iss, token, ','); // high
    float high = std::stof(token);
    
    std::getline(iss, token, ','); // close
    float close = std::stof(token);
    
    std::getline(iss, token, ','); // adjusted close
    float adjusted_close = std::stof(token);

    std::getline(iss, token, ','); // volume
    float volume = std::stof(token);

    // Set the member variables
    this->symbol = symbol;
    this->timestamp = timestamp;
    this->open = open;
    this->low = low;
    this->high = high;
    this->close = close;
    this->adjusted_close = adjusted_close;
    this->volume = volume;
}


 std::ostream& witchpot::FeedEntry::operator<<(std::ostream &os) {
    os << getSymbol() << ' ' << getTimestamp() << ' ' << getOpen() << ' ' << getLow() << ' ' << getHigh() << ' ' << getClose() << ' ' << getAdjustedClose() << " " << getVolume();
    return os;
}