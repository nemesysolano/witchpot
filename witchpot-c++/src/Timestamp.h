#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <iostream>
#include <string>
namespace witchpot {
    class Timestamp {
        private: 
            int year;
            int month;
            int day;
            int hour;
            int minute;
            int second;
             bool isLeapYear(int year) const {
                return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            }     

            void addDayToSelf(int days);      
        public:

        Timestamp(const Timestamp & timestamp): year(timestamp.year), month(timestamp.month), day(timestamp.day), hour(timestamp.hour), minute(timestamp.minute), second(timestamp.second) {}
        Timestamp(const Timestamp && timestamp): year(timestamp.year), month(timestamp.month), day(timestamp.day), hour(timestamp.hour), minute(timestamp.minute), second(timestamp.second) {}
        
        Timestamp(): year(0), month(0), day(0), hour(0), minute(0), second(0) {}
        Timestamp(int year, int month, int day, int hour, int minute, int second): year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}
        Timestamp(int year, int month, int day): year(year), month(month), day(day), hour(0), minute(0), second(0) {}
        Timestamp(const std::string & timestamp);
        Timestamp(const std::string && timestamp): Timestamp(timestamp) {};        
        inline int getYear() const { return year; }
        inline int getMonth() const { return month; }
        inline int getDay() const { return day; }
        inline int getHour() const { return hour; }
        inline int getMinute() const { return minute; }
        inline int getSecond() const { return second; }        
        Timestamp addDay(int days) const;
        inline Timestamp inc(int delta) const { return addDay(delta);}
        inline Timestamp & incSelf(int delta) { addDayToSelf(delta); return *this;}
        bool operator < (const Timestamp& other) const;
        bool operator == (const Timestamp& other) const;
        inline bool operator !=(const Timestamp& other) const {return !(*this == other);} 
        inline bool operator > (const Timestamp& other) const {return !(*this < other || *this == other);};
        inline Timestamp & operator = (const Timestamp & timestamp) {
            year = timestamp.year;
            month = timestamp.month;
            day = timestamp.day;
            hour = timestamp.hour;
            minute = timestamp.minute;
            second = timestamp.second;
            return *this;
        }
        inline Timestamp & operator = (const Timestamp && timestamp) {
            year = timestamp.year;
            month = timestamp.month;
            day = timestamp.day;
            hour = timestamp.hour;
            minute = timestamp.minute;  
            second = timestamp.second;
            return *this;
        }

        inline Timestamp operator ++ (int) { // Postfix increment operator.
            return inc(1);
        }

        inline Timestamp & operator ++ () { // Prefix decrement operator.
            return incSelf(1);
        }

        static Timestamp today();
        static Timestamp now();
    };

    std::ostream& operator<<(std::ostream &os, Timestamp const & timestamp);
   
}
#endif