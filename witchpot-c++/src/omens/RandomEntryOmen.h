#ifndef __RANDOM_ENTRY_OMEN_H__
#define __RANDOM_ENTRY_OMEN_H__
#include "Omen.h"
#include <vector>
#include <iostream>

namespace witchpot {    
    

    class RandomEntryOmen: public Omen {
        public:
            static const std::string & name();  
            RandomEntryOmen(): Omen(1, 1) {
                this->result[0][0] = 0;                
            }

            virtual void calculate  (const Timeseries<FeedEntry> &, const Timestamp &);
    };
}
#endif