#ifndef __RANDOM_ENTRY_SCHEMA_TEST_H__
#define __RANDOM_ENTRY_SCHEMA_TEST_H__
#include "schemas/RandomEntrySchema.h"
#include "TransactionLog.h"
#include <string>
#include <vector>
#include <filesystem>
namespace witchpot {
    class RandomEntrySchemaJobResult {
        private:
            float stopLossRate;
            float takeProfitRate;
            TransactionSummary summary;            
            int orderEntriesCount;
            int acceptedOrdersCount;
            int filledOrdersCount;
            int cancelledOrdersCount;

        public:
            inline RandomEntrySchemaJobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary & summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            ) : stopLossRate(stopLossRate), 
                takeProfitRate(takeProfitRate), 
                summary(summary), 
                acceptedOrdersCount(acceptedOrdersCount), 
                filledOrdersCount(filledOrdersCount), 
                cancelledOrdersCount(cancelledOrdersCount) {}   

            inline RandomEntrySchemaJobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary && summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            ) : stopLossRate(stopLossRate), 
                takeProfitRate(takeProfitRate), 
                summary(std::move(summary)), 
                acceptedOrdersCount(acceptedOrdersCount), 
                filledOrdersCount(filledOrdersCount), 
                cancelledOrdersCount(cancelledOrdersCount) {}
            inline float getStopLossRate() const {
                return stopLossRate;
            }
            inline float getTakeProfitRate() const {
                return takeProfitRate;
            }
            inline const TransactionSummary & getSummary() const {
                return summary;
            }
            inline int getOrderEntriesCount() const {
                return orderEntriesCount;
            }
            inline int getAcceptedOrdersCount() const {
                return acceptedOrdersCount;
            }
            inline int getFilledOrdersCount() const {
                return filledOrdersCount;
            }
            inline int getCancelledOrdersCount() const {
                return cancelledOrdersCount;
            }

    };
    std::ostream & operator<<(std::ostream & os, const RandomEntrySchemaJobResult & result);

    class RandomEntrySchemaJob {
        private:
            std::filesystem::directory_entry entry;
            std::vector<RandomEntrySchemaJobResult *> results;        
            std::string path_;
        public:
            RandomEntrySchemaJob(const std::string & entry): entry(entry), path_(entry) {}
            RandomEntrySchemaJob(const std::string && entry): entry(entry), path_(entry) {}            
            RandomEntrySchemaJob(const RandomEntrySchemaJob & other) = delete;
            RandomEntrySchemaJob(RandomEntrySchemaJob && other) = delete;
            RandomEntrySchemaJob & operator=(const RandomEntrySchemaJob & other) = delete;
            RandomEntrySchemaJob & operator=(RandomEntrySchemaJob && other) = delete;            
            inline void createRandomEntrySchemaJobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary & summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            ) {
                results.push_back(new RandomEntrySchemaJobResult(
                    stopLossRate, 
                    takeProfitRate, 
                    summary, 
                    acceptedOrdersCount, 
                    filledOrdersCount, 
                    cancelledOrdersCount
                ));
            }
            
            void createRandomEntrySchemaJobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary && summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            ) {
                results.push_back(new RandomEntrySchemaJobResult(
                    stopLossRate, 
                    takeProfitRate, 
                    std::move(summary), 
                    acceptedOrdersCount, 
                    filledOrdersCount, 
                    cancelledOrdersCount
                ));
            }

            inline size_t size() const {
                return results.size();
            }

            inline const RandomEntrySchemaJobResult & operator [](size_t index) {
                return *(results[index]);
            }

            inline bool is_directory() const {
                return entry.is_directory();
            }

            inline const std::string path() const {
                return path_;
            }
            ~RandomEntrySchemaJob();
    };

    class RandomEntrySchemaJobQueue {
        private:
            std::vector<RandomEntrySchemaJob *> * entries;
            bool is_owner;
        public:
            inline RandomEntrySchemaJobQueue(): entries(new std::vector<RandomEntrySchemaJob *>), is_owner(true) {}
            inline RandomEntrySchemaJobQueue(const RandomEntrySchemaJobQueue & other): entries(other.entries), is_owner(false) {}
            RandomEntrySchemaJobQueue(RandomEntrySchemaJobQueue && other) = delete;
            RandomEntrySchemaJobQueue & operator=(const RandomEntrySchemaJobQueue & other) {
                entries = other.entries;
                is_owner = false;
                return *this;
            }
            RandomEntrySchemaJobQueue & operator=(RandomEntrySchemaJobQueue && other) = delete;            
            inline void add(const std::string & path) {
                RandomEntrySchemaJob * entry = new RandomEntrySchemaJob(path);
                entries->push_back(entry);
            }
            inline void add(const std::string && path) {
                RandomEntrySchemaJob * entry = new RandomEntrySchemaJob(path);
                entries->push_back(entry);
            }
            inline size_t size() const {
                return entries->size();
            }
            inline RandomEntrySchemaJob & operator[] (size_t index) const{
                return *((*entries)[index]);
            }
            ~RandomEntrySchemaJobQueue() {
                if(is_owner && entries != nullptr) {
                    for (auto entry : *entries) {
                        delete entry;
                    }
                    delete entries;
                    entries = nullptr;
                
                }
            }
    };
}

void testRandomEntrySchema(const std::string & path);

#endif