#include "Timestamp.h"
#include <iomanip>
using namespace std;
using namespace witchpot;

static int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int leapYearDaysInMonth[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Timestamp::Timestamp(const std::string & timestamp) {
    // Define the expected format
    
    // Parse the timestamp string
    int year, month, day, hour, minute, second;
    auto result = sscanf(timestamp.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    
    
    // Check if the parsing was successful
    if (result == 6) {
        // Set the member variables
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    } else {
    // Handle invalid timestamp format
        this->year = -1;
        this->month = -1;
        this->day = -1;
        this->hour = -1;
        this->minute = -1;
        this->second = -1;
    }
}

Timestamp Timestamp::addDay(int days) const {
    Timestamp incremented(*this);
    incremented.addDayToSelf(days);
    return incremented;
}

void Timestamp::addDayToSelf(int days) {
    auto totalDays = day + days;
    auto currentYear = year;
    auto currentMonth = month;
    auto currentDay = totalDays;
    
    while (currentDay > daysInMonth[currentMonth - 1]) {
        if (currentMonth == 2 && isLeapYear(currentYear)) {
            currentDay -= leapYearDaysInMonth[currentMonth - 1];
        } else {
            currentDay -= daysInMonth[currentMonth - 1];
        }
        
        currentMonth++;
        if (currentMonth > 12) {
            currentMonth = 1;
            currentYear++;
        }
    }

    this->year = currentYear;
    this->month = currentMonth;
    this->day = currentDay;            
}

bool Timestamp::operator==(const Timestamp& other) const {
    return year == other.year && 
        month == other.month && 
        day == other.day &&
        hour == other.hour && 
        minute == other.minute && 
        second == other.second;
}

bool Timestamp::operator < (const Timestamp& other) const {
    if (year < other.year) {
        return true;
    } else if (year > other.year) {
        return false;
    } else {
        if (month < other.month) {
            return true;
        } else if (month > other.month) {
            return false;
        } else {
            if (day < other.day) {
                return true;
            } else if (day > other.day) {
                return false;
            } else {
                if (hour < other.hour) {
                    return true;
                } else if (hour > other.hour) {
                    return false;
                } else {
                    if (minute < other.minute) {
                        return true;
                    } else if (minute > other.minute) {
                        return false;
                    } else {
                        return second < other.second;
                    }
                }
            }
        }
    }
}

//
std::ostream& witchpot::operator<<(std::ostream &os, Timestamp const & timestamp) {
    os << timestamp.getYear() << '-' 
    << std::setfill('0') << std::setw(2) << timestamp.getMonth() << '-' 
    << std::setfill('0') << std::setw(2) << timestamp.getDay() << 'T' 
    << std::setfill('0') << std::setw(2) << timestamp.getHour() << ':' 
    << std::setfill('0') << std::setw(2) << timestamp.getMinute() << ':' 
    << std::setfill('0') << std::setw(2) << timestamp.getSecond();
    return os;
}

Timestamp Timestamp::today() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return witchpot::Timestamp(ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday, 0, 0, 0);
}

Timestamp Timestamp::now() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return witchpot::Timestamp(ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
}

witchpot::Timestamp extractDate(Timestamp & timestamp) {
    return Timestamp(timestamp.getYear(), timestamp.getMonth(), timestamp.getDay(), 0, 0, 0);
}

int Timestamp::daysDiff(const Timestamp & other) const {
    std::tm a = {0, 0, 0, day, month - 1, year - 1900, 0, 0, 0, 0, 0};
    std::tm b = {0, 0, 0, other.day, other.month - 1, other.year - 1900, 0, 0, 0, 0, 0};
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) ) {
        double difference = std::difftime(y, x) / (60 * 60 * 24);
        return std::abs(difference);
    }
    return -1;
}