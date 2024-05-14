#include "indicator.h"
#include "strategy.h"
#include "model.h"
#include "witchpot.h"
#include "Timeseries.h"
#include <map>
#include <filesystem>
#include <fstream>
#include <cassert>
#include "OrderBook.h"

using namespace std;
using namespace witchpot;

void timeSeriesTest() {
        vector<string> files;
    string path = "/Volumes/samsung-ex/workspaces/witchpot/data/symbols/";

    for (const auto &entry : filesystem::directory_iterator(path))
    {
        ifstream is(entry.path().string());
        if (entry.is_directory())
            continue;
        Timeseries<FeedEntry> timeSeries(is, entry.path().string());
        cout << entry.path().string() << ' ' << timeSeries.size() << ' ' << timeSeries.getStart() << ' ' << timeSeries.getEnd() << ' ';

        if (timeSeries.size() > 0)
        {
            auto end = timeSeries.getEnd();
            auto start = timeSeries.getStart();
            auto eof = timeSeries.getEof();
            auto current = start;
            assert(timeSeries.contains(start) && timeSeries.contains(end));
            size_t counter = 0;
            cout << current;
            while (current != eof)
            {
                counter++;
                assert(timeSeries.contains(current));
                current = timeSeries.next(current);
            }
            assert(counter = timeSeries.size());
            assert(current == eof);
        }

        cout << endl;
    }
}

void orderBookTest() {
    OrderBook orderBook;
    auto createBuyOrderResult = orderBook.createBuyOrder("AAPL", 100.0, 100, 0.0, 0.0);
    auto createSellOrderResult = orderBook.createSellOrder("AAPL", 100.0, 100, 0.0, 0.0);    
    assert(createBuyOrderResult->status == OrderStatus::ACCEPTED);
    assert(createSellOrderResult->status == OrderStatus::ACCEPTED);
}
int main()
{
    timeSeriesTest();
    orderBookTest();
    return 0;
}