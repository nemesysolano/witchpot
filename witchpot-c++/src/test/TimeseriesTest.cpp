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
#include <omp.h>


using namespace std;
using namespace witchpot;

void timeSeriesForSymbol(string & path) {
    vector<string> files;
    ifstream is(path);
    Timeseries<FeedEntry> timeSeries(is, path);
      
    
    if (timeSeries.size() > 0)
    {
        auto finish = timeSeries.getEnd();
        auto start = timeSeries.getStart();
        auto eof = timeSeries.getEof();
        auto current(start);
        assert(timeSeries.contains(start) && timeSeries.contains(finish));
        auto begin = TimeseriesIterator<FeedEntry>::begin(timeSeries);
        auto end = TimeseriesIterator<FeedEntry>::end(timeSeries);

        // Convert into a foreach loop
        for (;begin != end; ++begin)
        {                
            assert(timeSeries.contains(current));
            timeSeries.goToNext(current);
        }

        auto daysDiffRange = eof.daysDiff(start);
        auto daysDiffCurrent = current.daysDiff(start);
        auto daysDiffIterator = begin.get().daysDiff(start);

        cout  << path <<  endl;    
        assert(daysDiffCurrent == daysDiffRange);
        assert(daysDiffRange == daysDiffIterator);
        
        assert(current == eof);

        
    }    
}

void timeSeriesForSymbol(
        const vector<filesystem::directory_entry> & entries,        
        size_t index
    ) 
{
    auto & entry = entries[index];
    if(!entry.is_directory()) {
        string path = entry.path().string();
        timeSeriesForSymbol(path);
    }
}

void timeSeriesTest(const string & path) {
    vector<filesystem::directory_entry> entries;    
    assert(filesystem::exists(path) && filesystem::is_directory(path));
    omp_set_num_threads(4);

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        entries.push_back(entry);
    }

    const size_t size = entries.size();

    #pragma omp parallel for    
    for (size_t i = 0; i < size; i++) {
        timeSeriesForSymbol(entries, i);
    }
    
}




