#include "witchpot-tests.h"
using namespace std;

int main() {        
    string path = "../data/symbols/";
    // timeSeriesTest(path);
    // transactionsAllBuyWinnersTest();
    // transactionsAllSellWinnersTest();
    // transactionsBuyAndSellWinTest();
    transactionsBuyWinButSellLose();
    transactionsBuyLoseButSellWin();
    return 0;
}