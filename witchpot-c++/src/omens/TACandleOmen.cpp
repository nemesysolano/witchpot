#include "TACandleOmen.h"

using namespace witchpot;
using namespace std;
static const size_t CANDLES_LIST_SIZE = 62;

const size_t witchpot::TA_CANDLE_OMEN_COLUMNS = 5;
const size_t witchpot::TA_CANDLE_OMEN_WEIGHT = 0;
const size_t witchpot::TA_CANDLE_OMEN_OPEN = witchpot::TA_CANDLE_OMEN_WEIGHT + 1;
const size_t witchpot::TA_CANDLE_OMEN_LOW = witchpot::TA_CANDLE_OMEN_OPEN + 1;
const size_t witchpot::TA_CANDLE_OMEN_HIGH = witchpot::TA_CANDLE_OMEN_LOW + 1;
const size_t witchpot::TA_CANDLE_OMEN_CLOSE = witchpot::TA_CANDLE_OMEN_HIGH + 1;

const string TACandleOmen_name("TACandleOmen");

const string & TACandleOmen::name() {
    return TACandleOmen_name;
}


TACandleOmen::TACandleOmen(std::istream & is, std::string & symbol): Omen(1, TA_CANDLE_OMEN_COLUMNS), symbol(symbol) {
    this->timeSeries = new Timeseries<TACandles>(is, symbol);
};

void TACandleOmen::calculate(const Timeseries<FeedEntry> & timeSeries, const Timestamp & current) {   

    if(this->timeSeries->contains(current)) {
        size_t index = 0;
        auto candles = this->timeSeries->get(current).value();
        auto prices = timeSeries.get(current).value();
        this->result[0][index++] = candles->weight();
        this->result[0][index++] = prices->getOpen();
        this->result[0][index++] = prices->getLow();
        this->result[0][index++] = prices->getHigh();
        this->result[0][index++] = prices->getClose();
    }
}


TACandleOmen::~TACandleOmen() {
    if(is_owner) {
        delete timeSeries;
    }
 }

 TACandles::TACandles(const std::string & symbol, const std::string & line):symbol(symbol) {
    // Date,Open,High,Low,Close,Adj Close,Volume,Dividends,Stock Splits,CDL_2CROWS,CDL_3BLACKCROWS,CDL_3INSIDE,CDL_3LINESTRIKE,CDL_3OUTSIDE,CDL_3STARSINSOUTH,CDL_3WHITESOLDIERS,CDL_ABANDONEDBABY,CDL_ADVANCEBLOCK,CDL_BELTHOLD,CDL_BREAKAWAY,CDL_CLOSINGMARUBOZU,CDL_CONCEALBABYSWALL,CDL_COUNTERATTACK,CDL_DARKCLOUDCOVER,CDL_DOJI_10_0.1,CDL_DOJISTAR,CDL_DRAGONFLYDOJI,CDL_ENGULFING,CDL_EVENINGDOJISTAR,CDL_EVENINGSTAR,CDL_GAPSIDESIDEWHITE,CDL_GRAVESTONEDOJI,CDL_HAMMER,CDL_HANGINGMAN,CDL_HARAMI,CDL_HARAMICROSS,CDL_HIGHWAVE,CDL_HIKKAKE,CDL_HIKKAKEMOD,CDL_HOMINGPIGEON,CDL_IDENTICAL3CROWS,CDL_INNECK,CDL_INSIDE,CDL_INVERTEDHAMMER,CDL_KICKING,CDL_KICKINGBYLENGTH,CDL_LADDERBOTTOM,CDL_LONGLEGGEDDOJI,CDL_LONGLINE,CDL_MARUBOZU,CDL_MATCHINGLOW,CDL_MATHOLD,CDL_MORNINGDOJISTAR,CDL_MORNINGSTAR,CDL_ONNECK,CDL_PIERCING,CDL_RICKSHAWMAN,CDL_RISEFALL3METHODS,CDL_SEPARATINGLINES,CDL_SHOOTINGSTAR,CDL_SHORTLINE,CDL_SPINNINGTOP,CDL_STALLEDPATTERN,CDL_STICKSANDWICH,CDL_TAKURI,CDL_TASUKIGAP,CDL_THRUSTING,CDL_TRISTAR,CDL_UNIQUE3RIVER,CDL_UPSIDEGAP2CROWS,CDL_XSIDEGAP3METHODS
    std::istringstream iss(line);
    std::string token;

    //`Date`
    std::getline(iss, token, ','); // timestamp
    Timestamp timestamp(token);    
    this->timeStamp = timestamp;
    
    //`Open`, `High`, `Low`, `Close`, `Adj Close`, `Volume`, `Dividends`, `Stock Splits`
    std::getline(iss, token, ',');
    if(token.length() > 0) 
        this->open = std::stof(token);
    token.clear();

    std::getline(iss, token, ',');
    if(token.length() > 0) 
        this->high = std::stof(token);
    token.clear();

    std::getline(iss, token, ',');
    if(token.length() > 0) 
        this->low = std::stof(token);
    token.clear();

    std::getline(iss, token, ',');
    if(token.length() > 0) 
        this->close = std::stof(token);
    token.clear();

    std::getline(iss, token, ',');
    if(token.length() > 0) 
        this->adjClose = std::stof(token);
    token.clear();

    std::getline(iss, token, ',');
    if(token.length() > 0) 
        this->volume = std::stof(token);
    token.clear();

    std::getline(iss, token, ',');
    token.clear();
    if(token.length() > 0) 
        this->dividends = std::stof(token);
    token.clear();

    std::getline(iss, token, ',');
    if(token.length() > 0) 
        this->stockSplits = std::stof(token);
    token.clear();


    //`CDL_*`
    this->cdlPointers = (float **)malloc(CANDLES_LIST_SIZE * sizeof(float *));
    for(size_t i = 0; i < CANDLES_LIST_SIZE; i++) {
        std::getline(iss, token, ',');
        float value = std::stof(token);

        switch(i) {
            case 0: this->cdlPointers[i] = &cdl2Crows; cdl2Crows = value; break; // CDL_2CROWS
            case 1: this->cdlPointers[i] = &cdl3BlackCrows; cdl3BlackCrows = value; break; // CDL_3BLACKCROWS
            case 2: this->cdlPointers[i] = &cdl3Inside; cdl3Inside = value; break; // CDL_3INSIDE
            case 3: this->cdlPointers[i] = &cdl3LineStrike; cdl3LineStrike = value; break; // CDL_3LINESTRIKE
            case 4: this->cdlPointers[i] = &cdl3Outside; cdl3Outside = value; break; // CDL_3OUTSIDE
            case 5: this->cdlPointers[i] = &cdl3StarsInSouth; cdl3StarsInSouth = value; break; // CDL_3STARSINSOUTH
            case 6: this->cdlPointers[i] = &cdl3WhiteSoldiers; cdl3WhiteSoldiers = value; break; // CDL_3WHITESOLDIERS
            case 7: this->cdlPointers[i] = &cdlAbandonedBaby; cdlAbandonedBaby = value; break; // CDL_ABANDONEDBABY
            case 8: this->cdlPointers[i] = &cdlAdvanceBlock; cdlAdvanceBlock = value; break; // CDL_ADVANCEBLOCK
            case 9: this->cdlPointers[i] = &cdlBeltHold; cdlBeltHold = value; break; // CDL_BELTHOLD
            case 10: this->cdlPointers[i] = &cdlBreakaway; cdlBreakaway = value; break; // CDL_BREAKAWAY
            case 11: this->cdlPointers[i] = &cdlClosingMarubozu; cdlClosingMarubozu = value; break; // CDL_CLOSINGMARUBOZU
            case 12: this->cdlPointers[i] = &cdlConcealBabySwall; cdlConcealBabySwall = value; break; // CDL_CONCEALBABYSWALL
            case 13: this->cdlPointers[i] = &cdlCounterAttack; cdlCounterAttack = value; break; // CDL_COUNTERATTACK
            case 14: this->cdlPointers[i] = &cdlDarkCloudCover; cdlDarkCloudCover = value; break; // CDL_DARKCLOUDCOVER
            case 15: this->cdlPointers[i] = &cdlDoji10_0_1; cdlDoji10_0_1 = value; break; // CDL_DOJI_10_0.1
            case 16: this->cdlPointers[i] = &cdlDojiStar; cdlDojiStar = value; break; // CDL_DOJISTAR
            case 17: this->cdlPointers[i] = &cdlDragonflyDoji; cdlDragonflyDoji = value; break; // CDL_DRAGONFLYDOJI
            case 18: this->cdlPointers[i] = &cdlEngulfing; cdlEngulfing = value; break; // CDL_ENGULFING
            case 19: this->cdlPointers[i] = &cdlEveningDojiStar; cdlEveningDojiStar = value; break; // CDL_EVENINGDOJISTAR
            case 20: this->cdlPointers[i] = &cdlEveningStar; cdlEveningStar = value; break; // CDL_EVENINGSTAR
            case 21: this->cdlPointers[i] = &cdlGapSideSideWhite; cdlGapSideSideWhite = value; break; // CDL_GAPSIDESIDEWHITE
            case 22: this->cdlPointers[i] = &cdlGravestoneDoji; cdlGravestoneDoji = value; break; // CDL_GRAVESTONEDOJI
            case 23: this->cdlPointers[i] = &cdlHammer; cdlHammer = value; break; // CDL_HAMMER
            case 24: this->cdlPointers[i] = &cdlHangingMan; cdlHangingMan = value; break; // CDL_HANGINGMAN
            case 25: this->cdlPointers[i] = &cdlHarami; cdlHarami = value; break; // CDL_HARAMI
            case 26: this->cdlPointers[i] = &cdlHaramiCross; cdlHaramiCross = value; break; // CDL_HARAMICROSS
            case 27: this->cdlPointers[i] = &cdlHighWave; cdlHighWave = value; break; // CDL_HIGHWAVE
            case 28: this->cdlPointers[i] = &cdlHikkake; cdlHikkake = value; break; // CDL_HIKKAKE
            case 29: this->cdlPointers[i] = &cdlHikkakeMod; cdlHikkakeMod = value; break; // CDL_HIKKAKEMOD
            case 30: this->cdlPointers[i] = &cdlHomingPigeon; cdlHomingPigeon = value; break; // CDL_HOMINGPIGEON
            case 31: this->cdlPointers[i] = &cdlIdentical3Crows; cdlIdentical3Crows = value; break; // CDL_IDENTICAL3CROWS
            case 32: this->cdlPointers[i] = &cdlInNeck; cdlInNeck = value; break; // CDL_INNECK
            case 33: this->cdlPointers[i] = &cdlInside; cdlInside = value; break; // CDL_INSIDE
            case 34: this->cdlPointers[i] = &cdlInvertedHammer; cdlInvertedHammer = value; break; // CDL_INVERTEDHAMMER
            case 35: this->cdlPointers[i] = &cdlKicking; cdlKicking = value; break; // CDL_KICKING
            case 36: this->cdlPointers[i] = &cdlKickingByLength; cdlKickingByLength = value; break; // CDL_KICKINGBYLENGTH
            case 37: this->cdlPointers[i] = &cdlLadderBottom; cdlLadderBottom = value; break; // CDL_LADDERBOTTOM
            case 38: this->cdlPointers[i] = &cdlLongLeggedDoji; cdlLongLeggedDoji = value; break; // CDL_LONGLEGGEDDOJI
            case 39: this->cdlPointers[i] = &cdlLongLine; cdlLongLine = value; break; // CDL_LONGLINE
            case 40: this->cdlPointers[i] = &cdlMarubozu; cdlMarubozu = value; break; // CDL_MARUBOZU
            case 41: this->cdlPointers[i] = &cdlMatchingLow; cdlMatchingLow = value; break; // CDL_MATCHINGLOW
            case 42: this->cdlPointers[i] = &cdlMatHold; cdlMatHold = value; break; // CDL_MATHOLD
            case 43: this->cdlPointers[i] = &cdlMorningDojiStar; cdlMorningDojiStar = value; break; // CDL_MORNINGDOJISTAR
            case 44: this->cdlPointers[i] = &cdlMorningStar; cdlMorningStar = value; break; // CDL_MORNINGSTAR
            case 45: this->cdlPointers[i] = &cdlOnNeck; cdlOnNeck = value; break; // CDL_ONNECK
            case 46: this->cdlPointers[i] = &cdlPiercing; cdlPiercing = value; break; // CDL_PIERCING
            case 47: this->cdlPointers[i] = &cdlRickshawMan; cdlRickshawMan = value; break; // CDL_RICKSHAWMAN
            case 48: this->cdlPointers[i] = &cdlRiseFall3Methods; cdlRiseFall3Methods = value; break; // CDL_RISEFALL3METHODS
            case 49: this->cdlPointers[i] = &cdlSeparatingLines; cdlSeparatingLines = value; break; // CDL_SEPARATINGLINES
            case 50: this->cdlPointers[i] = &cdlShootingStar; cdlShootingStar = value; break; // CDL_SHOOTINGSTAR
            case 51: this->cdlPointers[i] = &cdlShortLine; cdlShortLine = value; break; // CDL_SHORTLINE
            case 52: this->cdlPointers[i] = &cdlSpinningTop; cdlSpinningTop = value; break; // CDL_SPINNINGTOP
            case 53: this->cdlPointers[i] = &cdlStalledPattern; cdlStalledPattern = value; break; // CDL_STALLEDPATTERN
            case 54: this->cdlPointers[i] = &cdlStickSandwich; cdlStickSandwich = value; break; // CDL_STICKSANDWICH
            case 55: this->cdlPointers[i] = &cdlTakuri; cdlTakuri = value; break; // CDL_TAKURI
            case 56: this->cdlPointers[i] = &cdlTasukiGap; cdlTasukiGap = value; break; // CDL_TASUKIGAP
            case 57: this->cdlPointers[i] = &cdlThrusting; cdlThrusting = value; break; // CDL_THRUSTING
            case 58: this->cdlPointers[i] = &cdlTristar; cdlTristar = value; break; // CDL_TRISTAR
            case 59: this->cdlPointers[i] = &cdlUnique3River; cdlUnique3River = value; break; // CDL_UNIQUE3RIVER
            case 60: this->cdlPointers[i] = &cdlUpsideGap2Crows; cdlUpsideGap2Crows = value; break; // CDL_UPSIDEGAP2CROWS
            case 61: this->cdlPointers[i] = &cdlXSideGap3Methods; cdlXSideGap3Methods = value; break; // CDL_XSIDEGAP3METHODS
        }
    }
    
 }

 TACandles::~TACandles() {
    free(cdlPointers);
 }

 float TACandles::weight() const{
    return weight(cdlPointers, CANDLES_LIST_SIZE);
 }

 float TACandles::weight(float * * cdlPointers, size_t size) {
   // sum all cdlPointer values which are negative
    int negSum = 0, posSum = 0;

    for(size_t i = 0; i < size; i++) {
        float lambda = abs(*cdlPointers[i]);
        if(!isnan(lambda) && lambda > 1) {
            if(*cdlPointers[i] < 0) {
                negSum ++;
            } else {
                posSum ++;
            }

        }
    }    

    return (posSum + negSum) > 0 ? (float)(posSum - negSum) / ((float)(posSum + negSum) / 2) : 0;
 }