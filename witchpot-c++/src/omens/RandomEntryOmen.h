#ifndef __RANDOM_ENTRY_OMEN_H__
#define __RANDOM_ENTRY_OMEN_H__
#include "Omen.h"
#include <vector>
#include <iostream>

namespace witchpot {    
    

    class RandomEntryOmen: public Omen {
        public:
            static const std::string & name();  
            RandomEntryOmen(): Omen(1, 5) { //weight, open, high, low, close
                this->result[0][0] = 0;
                this->result[0][1] = 0;
                this->result[0][2] = 0;
                this->result[0][3] = 0;
                this->result[0][4] = 0;                
            }

            virtual void calculate  (const Timeseries<FeedEntry> &, const Timestamp &);
    };
}
#endif