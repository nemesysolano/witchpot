#include "Omen.h"
using namespace witchpot;
using namespace std;

size_t Omen::rowSize() {
    return 0;
}

size_t Omen::colSize() {
    return 0;
}

void Omen::calculate(const Timeseries<FeedEntry> & , const Timestamp & )  {
}

const std::vector<float> & Omen::getResult(size_t ) const {
    return this->result;
}

const std::vector<float> & Omen::getResult() const {
    return this->getResult(0);
}