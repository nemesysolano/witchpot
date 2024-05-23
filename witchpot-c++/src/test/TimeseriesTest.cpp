#include "Omen.h"
#include "Schema.h"
#include "witchpot.h"
#include <map>
#include <filesystem>
#include <fstream>
#include <cassert>
#include "OrderBook.h"
#include "Driver.h"
#include <iostream>
#include "test/TimeseriesTest.h"
#include <vector>
#include <thread>

using namespace std;
using namespace witchpot;

void timeSeriesForSymbol(string & path) {
    vector<string> files;
    ifstream is(path);
    Timeseries<FeedEntry> timeSeries(is, path);
    
    
    if (timeSeries.size() > 0)
    {
        auto end = timeSeries.getEnd();
        auto start = timeSeries.getStart();
        auto eof = timeSeries.getEof();
        auto current(start);
        assert(timeSeries.contains(start) && timeSeries.contains(end));
        size_t counter = 0;

        while (current != eof)
        {                
            assert(timeSeries.contains(current));
            timeSeries.goToNext(current);
        }
        assert(counter = timeSeries.size());
        assert(current == eof);

        cout << path << ' ' << timeSeries.size() << ' ' << timeSeries.getStart() << ' ' << timeSeries.getEnd() << ' ' << this_thread::get_id() << endl;
    }    
}

void timeSeriesForSymbol(filesystem::directory_entry entry) {
    if(!entry.is_directory()) {
        string path = entry.path().string();
        timeSeriesForSymbol(path);
    }
}

void timeSeriesTest() {
    std::vector<std::string> files;
    std::string path = "/Volumes/samsung-ex/workspaces/witchpot/data/symbols/";
    std::vector<std::thread> threads;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        threads.emplace_back([=] { timeSeriesForSymbol(entry); });
        timeSeriesForSymbol(entry);
    }
    
    for (auto &thread : threads) {
        thread.join();
    }
}




