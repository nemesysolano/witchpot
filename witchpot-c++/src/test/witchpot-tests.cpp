#include "witchpot-tests.h"
using namespace std;

int main() {        
    // string trainBarePath = "../data/symbols/train/bare";
    // string trainNormalizedPath = "../data/symbols/train/normalized";
    string symbolsPath = "../data/symbols";

    // timeSeriesTest(trainBarePath);
    // transactionsAllBuyWinnersTest();
    // transactionsAllSellWinnersTest();
    // transactionsBuyAndSellWinTest();
    // transactionsBuyWinButSellLose();
    // transactionsBuyLoseButSellWin();
    // testRandomEntryOmen();
    // testRandomEntrySchema(trainBarePath);
    // taCandlesWeightTest();
    // testTACandleOmen(trainBarePath);
    testTAProfitDataGenSchemaTest(symbolsPath);
    return 0;
}