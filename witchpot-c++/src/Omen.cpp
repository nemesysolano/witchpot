#include "Omen.h"
using namespace witchpot;
using namespace std;

size_t Omen::rowSize() const {
    return result.size();
}

size_t Omen::colSize() const {
    return result[0].size();
}

void Omen::calculate(const Timeseries<FeedEntry> & , const Timestamp & )  {
}

float Omen::at(size_t row, size_t column) const {
    return this->result[row][column];
}

float Omen::at(size_t column) const {
    return at(0, column);
}