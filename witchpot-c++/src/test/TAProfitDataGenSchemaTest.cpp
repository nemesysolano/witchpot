#include "TAProfitDataGenSchemaTest.h"
#include <omp.h>
#include <filesystem>
#include <cassert>
#include "Driver.h"
#include "JobQueue.h"
#include "TACandleOmen.h"
#include <format>
#include <fstream>
#include <regex>
#include "Omen.h"
using namespace std;
using namespace witchpot;
void testTAProfitDataGenSchemaTest(witchpot::Job & entry) {
  if(entry.is_directory()) {
        return;
    }
    // Create a normalized_path string variable and set it to the normalized path of the entry

    std::string bare_path = entry.path();
    std::string normalized_path = std::regex_replace(bare_path, std::regex("bare"), "normalized");
    std::string result_path = std::regex_replace(normalized_path, std::regex("data/symbols"), "data/results");
    assert(filesystem::exists(normalized_path) && filesystem::is_regular_file(normalized_path));

    ofstream ros(result_path, ios::out | ios::trunc);        
    assert(ros.is_open() && ros.good());
    
    ifstream nis(normalized_path);
    ifstream is(bare_path);
    
    map<string,unique_ptr<Schema>> schemas;
    map<string,unique_ptr<Omen>> omens;

    schemas.insert(make_pair(TAProfitDataGenSchema::name(), make_unique<TAProfitDataGenSchema>()));    
    omens.insert(make_pair(TACandleOmen::name(), make_unique<TACandleOmen>(nis, normalized_path)));

    const TACandleOmen & taCandleOmen  = dynamic_cast<const TACandleOmen &>(*omens.at(TACandleOmen::name()));
    Timeseries<FeedEntry> timeSeries(is, bare_path);     

    assert(timeSeries.size() == taCandleOmen.getTimeSeries().size());
    auto timeSeriesStart = timeSeries.getStart();
    auto timeSeriesEnd = timeSeries.getEnd();        
    Driver driver(timeSeries, schemas, omens);
    
    auto orderBook = driver.getOrderBook();
    driver.run();            
    
    entry.createJobResult(0.0, 0.0, driver.getTransactionLog().getTransactionSummary(), 
        orderBook.acceptedOrdersCount(),
        orderBook.filledOrdersCount(),
        orderBook.cancelledOrdersCount()
    );
    
    ros << DIRECTION_LABEL  << ',' <<
        TAKE_PROFIT_LABEL << ',' << 
        STOP_LOSS_LABEL << ',' << 
        OPEN_LABEL << ',' << 
        HIGH_LABEL << ',' << 
        LOW_LABEL << ',' << 
        CLOSE_LABEL << ',' <<
        VOLUME_LABEL << ',' <<
        WEIGHT_LABEL << ',' << 
        RESULT_LABEL << endl;
        
    for(size_t index = 0; index < driver.getTransactionLog().size(); index ++){
        const Transaction & transaction = driver.getTransactionLog()[index];
        const OrderBookEntry & orderEntry = driver.getOrderBook()[transaction.getOrderEntryId()];
        const Timestamp & orderEntryTimeStamp = orderEntry.getMarketOrder().getTimestamp();
        const map<string, float> & additionalInfo = orderEntry.getAdditionalInfo();        
        const float result = transaction.getProfit() < 0 ? additionalInfo.at(STOP_LOSS_LABEL) : additionalInfo.at(TAKE_PROFIT_LABEL);
        const TACandles & taCandle = *taCandleOmen.getTimeSeries().get(orderEntryTimeStamp).value();        

        ros << (orderEntry.getMarketOrder().getSide() == OrderSide::BUY ? 1 : -1) << ','
            << additionalInfo.at(TAKE_PROFIT_LABEL) << ','
            << additionalInfo.at(STOP_LOSS_LABEL) << ',' 
            << taCandle.openPrice() << ','
            << taCandle.highPrice() << ','            
            << taCandle.lowPrice() << ','
            << taCandle.closePrice() << ','
            << taCandle.getVolume() << ','
            << additionalInfo.at(WEIGHT_LABEL) << ','
            << result << endl;

       
    }
    cout << result_path << endl;
    ros.flush();
    ros.close();
}

void addJobs(const string symbolPath, JobQueue & jobQueue) {
    char fullPath[256];
    assert(filesystem::exists(symbolPath) && filesystem::is_directory(symbolPath));    
    vector<string> folders = { // \.\./data/symbols/(train|validate|test)/(bare|normalized)
        "/train/bare/",
        "/validate/bare/",
        "/test/bare/",
    };

    size_t count = 0;
    for (const auto &entry : filesystem::directory_iterator(symbolPath)) {
        if(entry.is_directory() || entry.path().extension() != ".csv"){
            continue;
        }
        for(string &folder : folders){
            snprintf(fullPath, sizeof(fullPath), "%s%s%s", symbolPath.c_str(), folder.c_str(), entry.path().filename().string().c_str());
            if(filesystem::exists(fullPath) && filesystem::is_regular_file(fullPath)){
                jobQueue.add(fullPath);
            } else {
                cout << "File not found: " << fullPath << endl;
                throw std::runtime_error("crashed ");
            }            
        }

        if(count == 9)
            break;
        count++;
    }
}

void testTAProfitDataGenSchemaTest(const JobQueue & jobQueue, const size_t start, const size_t end) {
    auto procs = omp_get_num_procs()  -1 ;    
    #pragma omp parallel for shared(start, end, jobQueue) default(none) schedule(dynamic, 1) num_threads(procs)
    for (size_t i = start; i < end; i++) {
        testTAProfitDataGenSchemaTest(jobQueue[i]);
    }
}
void testTAProfitDataGenSchemaTest(const string& symbolPath) {
    
    JobQueue jobQueue;

    addJobs(symbolPath, jobQueue);
    
    const size_t size = jobQueue.size();
    assert (size > 0 && size % 3 == 0);
    
    testTAProfitDataGenSchemaTest(jobQueue, 0, size);
}