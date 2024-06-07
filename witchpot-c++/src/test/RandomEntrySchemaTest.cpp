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

void testRandomEntrySchemaForSymbol(witchpot::Job & entry) 
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
    
    entry.createJobResult(0.0, 0.0, driver.getTransactionLog().getTransactionSummary(), 
        orderBook.acceptedOrdersCount(),
        orderBook.filledOrdersCount(),
        orderBook.cancelledOrdersCount()
    );
    const JobResult & result = entry[0];
    cout << entry.path() << ':' << result << endl;        
    assert(
        ((int)timeSeries.size()) > orderBook.acceptedOrdersCount() + orderBook.filledOrdersCount() + orderBook.cancelledOrdersCount()
    );
}


void testRandomEntrySchema(const string & path) { // https://www.openmp.org/wp-content/uploads/OpenMP3.1-CCard.pdf
    auto procs = omp_get_num_procs() - 1;
    JobQueue jobQueue;
    assert(filesystem::exists(path) && filesystem::is_directory(path));

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if(entry.is_directory() || entry.path().extension() != ".csv"){
            continue;
        }
        jobQueue.add(entry.path().string());           
    }

    const size_t size = jobQueue.size();

    #pragma omp parallel for shared(size, jobQueue) default(none) schedule(dynamic, 1) num_threads(procs)
    for (size_t i = 0; i < size; i++) {
        testRandomEntrySchemaForSymbol(jobQueue[i]);

    }

}

