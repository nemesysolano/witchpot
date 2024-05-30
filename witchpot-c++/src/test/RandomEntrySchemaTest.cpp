#include "RandomEntrySchemaTest.h"
#include "RandomEntryOmen.h"
#include <filesystem>
#include <thread>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ranges>
#include <execution>
#include <omp.h>
#include <cassert>
#include "Driver.h"
using namespace std;
using namespace witchpot;

void testRandomEntrySchemaForSymbol(witchpot::RandomEntrySchemaJob & entry) 
{
    if(entry.is_directory()) {
        return;
    }

    
    map<string,unique_ptr<Schema>> schemas;
    map<string,unique_ptr<Omen>> omens;
    schemas.insert(make_pair(RandomEntrySchema::name(), make_unique<RandomEntrySchema>()));            
    omens.insert(make_pair(RandomEntryOmen::name(), make_unique<RandomEntryOmen>()));

    ifstream is(entry.path());
    Timeseries<FeedEntry> timeSeries(is, entry.path());      
    Driver driver(timeSeries, schemas, omens);
    auto orderBook = driver.getOrderBook();

    driver.run();            
    entry.createRandomEntrySchemaJobResult(0.0, 0.0, driver.getTransactionLog().getTransactionSummary(), 
        orderBook.acceptedOrdersCount(),
        orderBook.filledOrdersCount(),
        orderBook.cancelledOrdersCount()
    );
    const RandomEntrySchemaJobResult & result = entry[0];
    cout << entry.path() << ':' << result << endl;        
    assert(
        ((int)timeSeries.size()) > orderBook.acceptedOrdersCount() + orderBook.filledOrdersCount() + orderBook.cancelledOrdersCount()
    );
}

void testRandomEntrySchema(const string & path) { // https://www.openmp.org/wp-content/uploads/OpenMP3.1-CCard.pdf
    auto procs = omp_get_num_procs() - 1;
    RandomEntrySchemaJobQueue randomEntrySchemaJobQueue;
    assert(filesystem::exists(path) && filesystem::is_directory(path));

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        randomEntrySchemaJobQueue.add(entry.path().string());   
    }

    const size_t size = randomEntrySchemaJobQueue.size();

    #pragma omp parallel for shared(size, randomEntrySchemaJobQueue) default(none) schedule(dynamic, 1) num_threads(procs)
    for (size_t i = 0; i < size; i++) {
        testRandomEntrySchemaForSymbol(randomEntrySchemaJobQueue[i]);

    }

}

RandomEntrySchemaJob::~RandomEntrySchemaJob() {
    for (auto result : results) {
        delete result;
    }
}

std::ostream & witchpot::operator<<(std::ostream & os, const RandomEntrySchemaJobResult & result) {
    os << "(sl_rate=" << result.getStopLossRate();
    os << ", tp_rate=" << result.getTakeProfitRate();
    os << ", summary=" << result.getSummary();
    os << ", orders_count=" << result.getOrderEntriesCount();
    os << ", accepted_orders_count=" << result.getAcceptedOrdersCount();
    os << ", filled_orders_count=" << result.getFilledOrdersCount();
    os << ", cancelled_orders_count=" << result.getCancelledOrdersCount() << ')' << std::endl;
    return os;
}