#ifndef __TRANSACTIONLOGTEST_H__
#define __TRANSACTIONLOGTEST_H__
#include "Omen.h"
#include "Schema.h"
#include "witchpot.h"
#include <map>
#include <filesystem>
#include <fstream>
#include <cassert>
#include "OrderBook.h"
#include "Driver.h"
#include <iostream>

void transactionsAllBuyWinnersTest();
void transactionsAllSellWinnersTest();
void transactionsBuyAndSellWinTest();
void transactionsBuyWinButSellLose();
void transactionsBuyLoseButSellWin();
#endif