#include "TACandleOmen.h"

using namespace witchpot;
using namespace std;

TACandleOmen::TACandleOmen(std::istream & is, std::string & symbol): Omen(1, 1), symbol(symbol) {
    this->timeSeries = new Timeseries<TACandles>(is, symbol);

};

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
    //Skip `Open`, `High`, `Low`, `Close`, `Adj Close`, `Volume`, `Dividends`, `Stock Splits` columns and read the rest into the `TACandles` object
    for(int i = 1; i < 9; i++) {
        std::getline(iss, token, ',');
    }
    // read all CDL_ columns
    for(int i = 0; i < 63; i++) {
        std::getline(iss, token, ',');
        float value = std::stof(token);

        switch(i) {
            case 0: cdl2Crows = value; break; // CDL_2CROWS
            case 1: cdl3BlackCrows = value; break; // CDL_3BLACKCROWS
            case 2: cdl3Inside = value; break; // CDL_3INSIDE
            case 3: cdl3LineStrike = value; break; // CDL_3LINESTRIKE
            case 4: cdl3Outside = value; break; // CDL_3OUTSIDE
            case 5: cdl3StarsInSouth = value; break; // CDL_3STARSINSOUTH
            case 6: cdl3WhiteSoldiers = value; break; // CDL_3WHITESOLDIERS
            case 7: cdlAbandonedBaby = value; break; // CDL_ABANDONEDBABY
            case 8: cdlAdvanceBlock = value; break; // CDL_ADVANCEBLOCK
            case 9: cdlBeltHold = value; break; // CDL_BELTHOLD
            case 10: cdlBreakaway = value; break; // CDL_BREAKAWAY
            case 11: cdlClosingMarubozu = value; break; // CDL_CLOSINGMARUBOZU
            case 12: cdlConcealBabySwall = value; break; // CDL_CONCEALBABYSWALL
            case 13: cdlCounterAttack = value; break; // CDL_COUNTERATTACK
            case 14: cdlDarkCloudCover = value; break; // CDL_DARKCLOUDCOVER
            case 15: cdlDoji10_0_1 = value; break; // CDL_DOJI_10_0.1
            case 16: cdlDojiStar = value; break; // CDL_DOJISTAR
            case 17: cdlDragonflyDoji = value; break; // CDL_DRAGONFLYDOJI
            case 18: cdlEngulfing = value; break; // CDL_ENGULFING
            case 19: cdlEveningDojiStar = value; break; // CDL_EVENINGDOJISTAR
            case 20: cdlEveningStar = value; break; // CDL_EVENINGSTAR
            case 21: cdlGapSideSideWhite = value; break; // CDL_GAPSIDESIDEWHITE
            case 22: cdlGravestoneDoji = value; break; // CDL_GRAVESTONEDOJI
            case 23: cdlHammer = value; break; // CDL_HAMMER
            case 24: cdlHangingMan = value; break; // CDL_HANGINGMAN
            case 25: cdlHarami = value; break; // CDL_HARAMI
            case 26: cdlHaramiCross = value; break; // CDL_HARAMICROSS
            case 27: cdlHighWave = value; break; // CDL_HIGHWAVE
            case 28: cdlHikkake = value; break; // CDL_HIKKAKE
            case 29: cdlHikkakeMod = value; break; // CDL_HIKKAKEMOD
            case 30: cdlHomingPigeon = value; break; // CDL_HOMINGPIGEON
            case 31: cdlIdentical3Crows = value; break; // CDL_IDENTICAL3CROWS
            case 32: cdlInNeck = value; break; // CDL_INNECK
            case 33: cdlInside = value; break; // CDL_INSIDE
            case 34: cdlInvertedHammer = value; break; // CDL_INVERTEDHAMMER
            case 35: cdlKicking = value; break; // CDL_KICKING
            case 36: cdlKickingByLength = value; break; // CDL_KICKINGBYLENGTH
            case 37: cdlLadderBottom = value; break; // CDL_LADDERBOTTOM
            case 38: cdlLongLeggedDoji = value; break; // CDL_LONGLEGGEDDOJI
            case 39: cdlLongLine = value; break; // CDL_LONGLINE
            case 40: cdlMarubozu = value; break; // CDL_MARUBOZU
            case 41: cdlMatchingLow = value; break; // CDL_MATCHINGLOW
            case 42: cdlMatHold = value; break; // CDL_MATHOLD
            case 43: cdlMorningDojiStar = value; break; // CDL_MORNINGDOJISTAR
            case 44: cdlMorningStar = value; break; // CDL_MORNINGSTAR
            case 45: cdlOnNeck = value; break; // CDL_ONNECK
            case 46: cdlPiercing = value; break; // CDL_PIERCING
            case 47: cdlRickshawMan = value; break; // CDL_RICKSHAWMAN
            case 48: cdlRiseFall3Methods = value; break; // CDL_RISEFALL3METHODS
            case 49: cdlSeparatingLines = value; break; // CDL_SEPARATINGLINES
            case 50: cdlShootingStar = value; break; // CDL_SHOOTINGSTAR
            case 51: cdlShortLine = value; break; // CDL_SHORTLINE
            case 52: cdlSpinningTop = value; break; // CDL_SPINNINGTOP
            case 53: cdlStalledPattern = value; break; // CDL_STALLEDPATTERN
            case 54: cdlStickSandwich = value; break; // CDL_STICKSANDWICH
            case 55: cdlTakuri = value; break; // CDL_TAKURI
            case 56: cdlTasukiGap = value; break; // CDL_TASUKIGAP
            case 57: cdlThrusting = value; break; // CDL_THRUSTING
            case 58: cdlTristar = value; break; // CDL_TRISTAR
            case 59: cdlUnique3River = value; break; // CDL_UNIQUE3RIVER
            case 60: cdlUpsideGap2Crows = value; break; // CDL_UPSIDEGAP2CROWS
            case 61: cdlXSideGap3Methods = value; break; // CDL_XSIDEGAP3METHODS
        }
    }
 }