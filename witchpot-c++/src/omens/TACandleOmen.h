#ifndef __TACANDLEOMEN_H__
#define __TACANDLEOMEN_H__
#include "Timeseries.h"
#include "Timestamp.h"  
#include <string>
#include <iostream>
#include "Omen.h"

namespace witchpot {
    class TACandles {
        protected:
            std::string symbol;
            Timestamp timeStamp;
            float cdl2Crows= 0; // CDL_2CROWS
            float cdl3BlackCrows= 0; // CDL_3BLACKCROWS
            float cdl3Inside= 0; // CDL_3INSIDE
            float cdl3LineStrike= 0; // CDL_3LINESTRIKE
            float cdl3Outside= 0; // CDL_3OUTSIDE
            float cdl3StarsInSouth= 0; // CDL_3STARSINSOUTH
            float cdl3WhiteSoldiers= 0; // CDL_3WHITESOLDIERS
            float cdlAbandonedBaby= 0; // CDL_ABANDONEDBABY
            float cdlAdvanceBlock= 0; // CDL_ADVANCEBLOCK
            float cdlBeltHold= 0; // CDL_BELTHOLD
            float cdlBreakaway= 0; // CDL_BREAKAWAY
            float cdlClosingMarubozu= 0; // CDL_CLOSINGMARUBOZU
            float cdlConcealBabySwall= 0; // CDL_CONCEALBABYSWALL
            float cdlCounterAttack= 0; // CDL_COUNTERATTACK
            float cdlDarkCloudCover= 0; // CDL_DARKCLOUDCOVER
            float cdlDoji10_0_1= 0; // CDL_DOJI_10_0.1
            float cdlDojiStar= 0; // CDL_DOJISTAR
            float cdlDragonflyDoji= 0; // CDL_DRAGONFLYDOJI
            float cdlEngulfing= 0; // CDL_ENGULFING
            float cdlEveningDojiStar= 0; // CDL_EVENINGDOJISTAR
            float cdlEveningStar= 0; // CDL_EVENINGSTAR
            float cdlGapSideSideWhite= 0; // CDL_GAPSIDESIDEWHITE
            float cdlGravestoneDoji= 0; // CDL_GRAVESTONEDOJI
            float cdlHammer= 0; // CDL_HAMMER
            float cdlHangingMan= 0; // CDL_HANGINGMAN
            float cdlHarami= 0; // CDL_HARAMI
            float cdlHaramiCross= 0; // CDL_HARAMICROSS
            float cdlHighWave= 0; // CDL_HIGHWAVE
            float cdlHikkake= 0; // CDL_HIKKAKE
            float cdlHikkakeMod= 0; // CDL_HIKKAKEMOD
            float cdlHomingPigeon= 0; // CDL_HOMINGPIGEON
            float cdlIdentical3Crows= 0; // CDL_IDENTICAL3CROWS
            float cdlInNeck= 0; // CDL_INNECK
            float cdlInside= 0; // CDL_INSIDE
            float cdlInvertedHammer= 0; // CDL_INVERTEDHAMMER
            float cdlKicking= 0; // CDL_KICKING
            float cdlKickingByLength= 0; // CDL_KICKINGBYLENGTH
            float cdlLadderBottom= 0; // CDL_LADDERBOTTOM
            float cdlLongLeggedDoji= 0; // CDL_LONGLEGGEDDOJI
            float cdlLongLine= 0; // CDL_LONGLINE
            float cdlMarubozu= 0; // CDL_MARUBOZU
            float cdlMatchingLow= 0; // CDL_MATCHINGLOW
            float cdlMatHold= 0; // CDL_MATHOLD
            float cdlMorningDojiStar= 0; // CDL_MORNINGDOJISTAR
            float cdlMorningStar= 0; // CDL_MORNINGSTAR
            float cdlOnNeck= 0; // CDL_ONNECK
            float cdlPiercing= 0; // CDL_PIERCING
            float cdlRickshawMan= 0; // CDL_RICKSHAWMAN
            float cdlRiseFall3Methods= 0; // CDL_RISEFALL3METHODS
            float cdlSeparatingLines= 0; // CDL_SEPARATINGLINES
            float cdlShootingStar= 0; // CDL_SHOOTINGSTAR
            float cdlShortLine= 0; // CDL_SHORTLINE
            float cdlSpinningTop= 0; // CDL_SPINNINGTOP
            float cdlStalledPattern= 0; // CDL_STALLEDPATTERN
            float cdlStickSandwich= 0; // CDL_STICKSANDWICH
            float cdlTakuri= 0; // CDL_TAKURI
            float cdlTasukiGap= 0; // CDL_TASUKIGAP
            float cdlThrusting= 0; // CDL_THRUSTING
            float cdlTristar= 0; // CDL_TRISTAR
            float cdlUnique3River= 0; // CDL_UNIQUE3RIVER
            float cdlUpsideGap2Crows= 0; // CDL_UPSIDEGAP2CROWS
            float cdlXSideGap3Methods= 0; // CDL_XSIDEGAP3METHODS
        public:
            TACandles() {}
            TACandles(const std::string & symbol, const std::string & line);
            inline const Timestamp & getTimestamp() const {return timeStamp;}
            inline const std::string & getSymbol() const {return symbol;}

    };

    class TACandleOmen: Omen {
        std::string symbol;
        Timeseries<TACandles> * timeSeries = nullptr;
        bool is_owner = true;
    public:
        TACandleOmen(std::istream & is, std::string & symbol);
        TACandleOmen(Timeseries<TACandles> * timeSeries);
        inline const Timeseries<TACandles> & getTimeSeries() const {
            return *timeSeries;
        }
        virtual ~TACandleOmen();
    };
}

#endif