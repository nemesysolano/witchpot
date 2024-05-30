#include "omens/RandomEntryOmen.h"
#include <random>

using namespace witchpot;
using namespace std;

const string RandomEntryOmen_name("RandomEntryOmen");

const string & RandomEntryOmen::name() {
    return RandomEntryOmen_name;
}

void RandomEntryOmen::calculate  (const Timeseries<FeedEntry> &, const Timestamp &) {    
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    normal_distribution<> dis(0, 1.0);

    double random_number = dis(gen);
    this->result[0][0] = random_number < 0 ? -1 : 1;
}
