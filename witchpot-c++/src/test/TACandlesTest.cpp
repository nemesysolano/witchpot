
#include "TACandlesTest.h"
#include <cassert>
using namespace witchpot;
/* 
>>> sumPos = 1+3
>>> sumNeg - 2+4
>>> (sumPos - sumNeg) / (sumPos + sumNeg)
-0.2
*/
void taCandlesWeightTest() {
    const size_t CANDLES_LIST_SIZE = 4;
    float a = 1;
    float b = -2;
    float c = 3;
    float d = -4;
    float * * cdlPointers =  (float **)malloc(CANDLES_LIST_SIZE * sizeof(float *));
    cdlPointers[0] = &a;
    cdlPointers[1] = &b;
    cdlPointers[2] = &c;
    cdlPointers[3] = &d;

    int weight = (int)(TACandles::weight(cdlPointers, CANDLES_LIST_SIZE)*100);
    assert(weight == -20);
    free(cdlPointers);
}