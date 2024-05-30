#include "OmenTests.h"
#include <cassert>
using namespace std;
using namespace witchpot;

void testRandomEntryOmen() {
    Timeseries <FeedEntry> timeSeries;
    RandomEntryOmen omen;
    vector<float> values;
    Timestamp timestamp = Timestamp::now();
    int negative_count = 0;
    int postive_count = 0;
    for(int i = 0; i < 100; i++) {
        omen.calculate(timeSeries, timestamp);
        values.push_back((float)omen);
        if(values.back() < 0) {
            negative_count++;
        } else {
            postive_count++;
        }

        if(negative_count > 0 && postive_count > 0) {
            break;
        }
    }

    cout << "Negative count: " << negative_count << ',' << "Positive count: " << postive_count << endl;
    assert(negative_count > 0);
    assert(postive_count > 0);
}
