#ifndef __RANDOM_ENTRY_SCHEMA_JOB_QUEUE_H__
#define __RANDOM_ENTRY_SCHEMA_JOB_QUEUE_H__
#include "Job.h"

namespace witchpot {
    class JobQueue {
        private:
            std::vector<Job *> * entries;
            bool is_owner;
        public:
            inline JobQueue(): entries(new std::vector<Job *>), is_owner(true) {}
            inline JobQueue(const JobQueue & other): entries(other.entries), is_owner(false) {}
            JobQueue(JobQueue && other) = delete;
            JobQueue & operator=(const JobQueue & other) {
                entries = other.entries;
                is_owner = false;
                return *this;
            }
            JobQueue & operator=(JobQueue && other) = delete;            
            inline void add(const std::string & path) {
                Job * entry = new Job(path);
                entries->push_back(entry);
            }
            inline void add(const std::string && path) {
                Job * entry = new Job(path);
                entries->push_back(entry);
            }
            inline size_t size() const {
                return entries->size();
            }
            inline Job & operator[] (size_t index) const{
                return *((*entries)[index]);
            }
            virtual ~JobQueue();
    };
}
#endif