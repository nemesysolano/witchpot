#include "Schema.h" 
#include "RandomEntryOmen.h"

using namespace witchpot;
void Schema::apply(
      const Timeseries<FeedEntry> &,
      const std::map<std::string, std::unique_ptr<Omen>> &,
      Timestamp &,
      OrderBook &

) {


}

Schema::~Schema() {}