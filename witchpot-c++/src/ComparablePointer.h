#ifndef __COMPARABLEPOINTER_H__
#define __COMPARABLEPOINTER_H__
#include <memory>

namespace witchpot {
    template <typename T> class ComparablePointer: public std::unique_ptr<T> {
        public:
            ComparablePointer(T * ptr): std::unique_ptr<T>(ptr) {};
            ComparablePointer(): std::unique_ptr<T>() {};
            ComparablePointer(const ComparablePointer<T> & other): std::unique_ptr<T>(other) {};
            ComparablePointer(const ComparablePointer<T> && other): std::unique_ptr<T>(other) {};           
            ComparablePointer<T> & operator = (const ComparablePointer<T> & other) = delete;
            ComparablePointer<T> & operator = (const ComparablePointer<T> && other) = delete;

            // < Operator
            bool operator < (const ComparablePointer<T> & other) const {
                return *this < *other;
            }

            bool operator < (const T & other) const {
                return *this < other;
            }

            // > Operator
            bool operator > (const ComparablePointer<T> & other) const {
                return *this > *other;
            }

            bool operator > (const T & other) const {
                return *this > other;
            }         

            // == Operator
            bool operator == (const ComparablePointer<T> & other) const {
                return *this == *other;
            }

            bool operator == (const T & other) const {
                return *this == other;
            }   

            // != Operator
            bool operator != (const ComparablePointer<T> & other) const {
                return *this != *other;
            }

            bool operator != (const T & other) const {
                return *this != other;
            }
    };
}
#endif