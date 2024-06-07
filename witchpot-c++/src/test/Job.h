#ifndef __RANDOM_ENTRY_SCHEMA_JOB_H__
#include "JobResult.h"
namespace witchpot {
        class Job {
        protected:
            std::filesystem::directory_entry source;
            std::vector<JobResult *> results;        
        public:
            Job(const std::string & source_): source(source_) {}
            Job(const std::string && source_): source(source_) {}            
            Job(const Job & other) = delete;
            Job(Job && other) = delete;
            Job & operator=(const Job & other) = delete;
            Job & operator=(Job && other) = delete;            
            virtual void createJobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary & summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            );
            
            virtual void createJobResult(
                float stopLossRate,
                float takeProfitRate,
                TransactionSummary && summary,
                int acceptedOrdersCount,
                int filledOrdersCount,
                int cancelledOrdersCount
            );

            inline size_t size() const {
                return results.size();
            }

            inline const JobResult & operator [](size_t index) {
                return *(results[index]);
            }

            inline bool is_directory() const {
                return source.is_directory();
            }

            inline const std::string path() const {
                return source.path().string();
            }
            virtual ~Job();
    };
}
#endif