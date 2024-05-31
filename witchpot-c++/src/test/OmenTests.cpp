#include "OmenTests.h"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include <TACandleOmen.h>
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

void testTACandleOmen(const vector<string> * pathsRef, size_t index) {
    const vector<string> & paths = *pathsRef;
    const string path = paths[index];
    ifstream indicator_stream(path);
    ifstream feed_stream(path);

    if(indicator_stream.is_open() && feed_stream.is_open()) {
        string symbol = path.substr(path.find_last_of('/') + 1);
        TACandleOmen omen(indicator_stream, symbol);
        Timeseries<FeedEntry> timeSeries(feed_stream, symbol);
        auto start = omen.getTimeSeries().getStart();
        auto end = omen.getTimeSeries().getEnd();
        auto eof = omen.getTimeSeries().getEof();
        assert(omen.getTimeSeries().get(start).value()->getSymbol() == symbol);
        assert(timeSeries.contains(start) && timeSeries.contains(end));
        assert(omen.getTimeSeries().size() == timeSeries.size());    
        
        while(start < eof) {
            assert(timeSeries.contains(start));
            omen.getTimeSeries().goToNext(start);
        }
        cout << "Symbol: " << symbol << " Start: " << start << " End: " << end << endl;
    }
    
}
void testTACandleOmen(std::string & path) { // "../data/symbols/
    auto files = std::filesystem::directory_iterator(path);  
    auto procs = omp_get_num_procs() - 1;
    vector<string> paths;   

    for (const auto &entry : files) {
        if(entry.is_regular_file() && entry.path().extension() == ".csv") {
            paths.push_back(entry.path().string());
        }
    }

    const vector<string> * pathsRef = &paths;
    const size_t size = paths.size();

    #pragma omp parallel for shared(size, pathsRef) default(none) schedule(dynamic, 1) num_threads(procs)
    for (size_t i = 0; i < size; i++) {
        testTACandleOmen(pathsRef, i);
    }

}