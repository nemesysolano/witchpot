#include "JobQueue.h"
using namespace witchpot;
JobQueue::~JobQueue() {
    if(is_owner && entries != nullptr) {
        for (auto entry : *entries) {
            delete entry;
        }
        delete entries;
        entries = nullptr;
    
    }
}
