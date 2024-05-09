package com.witchpot.model

import com.fasterxml.jackson.annotation.JsonProperty
import com.witchpot.Constants
import com.witchpot.mappers.UtilDate
import java.util.*

data class Symbol(
    val ticker: String,
    @field:JsonProperty("Date") val date: String, //  Date
    @field:JsonProperty("Open") val open: Double, //  Open
    @field:JsonProperty("High") val high: Double, //  High
    @field:JsonProperty("Low") val low: Double, //  Low
    @field:JsonProperty("Close") val close: Double, //  Close
    @field:JsonProperty("Adj Close") val adjClose: Double,// Adj Close
    @field:JsonProperty("Volume") val volume: Double, //  Volume
    @field:JsonProperty("Dividends") val dividends: Double, //  Dividends
    @field:JsonProperty("Stock Splits") val stockSplits: Double, //  Stock_Splits
    @field:JsonProperty("CDL_2CROWS") val cdl2Crows: Double, //  CDL_2CROWS
    @field:JsonProperty("CDL_3BLACKCROWS") val cdl3BlackCrows: Double, //  CDL_3BLACKCROWS
    @field:JsonProperty("CDL_3INSIDE") val cdl3Inside: Double, //  CDL_3INSIDE
    @field:JsonProperty("CDL_3LINESTRIKE") val cdl3LineStrike: Double, //  CDL_3LINESTRIKE
    @field:JsonProperty("CDL_3OUTSIDE") val cdl3Outside: Double, //  CDL_3OUTSIDE
    @field:JsonProperty("CDL_3STARSINSOUTH") val cdl3StarsInSouth: Double, //  CDL_3STARSINSOUTH
    @field:JsonProperty("CDL_3WHITESOLDIERS") val cdl3WhiteSoldiers: Double, //  CDL_3WHITESOLDIERS
    @field:JsonProperty("CDL_ABANDONEDBABY") val cdlAbandonedBaby: Double, //  CDL_ABANDONEDBABY
    @field:JsonProperty("CDL_ADVANCEBLOCK") val cdlAdvanceBlock: Double, //  CDL_ADVANCEBLOCK
    @field:JsonProperty("CDL_BELTHOLD") val cdlBeltHold: Double, //  CDL_BELTHOLD
    @field:JsonProperty("CDL_BREAKAWAY") val cdlBreakaway: Double, //  CDL_BREAKAWAY
    @field:JsonProperty("CDL_CLOSINGMARUBOZU") val cdlClosingMarubozu: Double, //  CDL_CLOSINGMARUBOZU
    @field:JsonProperty("CDL_CONCEALBABYSWALL") val cdlConcealBabySwall: Double, //  CDL_CONCEALBABYSWALL
    @field:JsonProperty("CDL_COUNTERATTACK") val cdlCounterAttack: Double, //  CDL_COUNTERATTACK
    @field:JsonProperty("CDL_DARKCLOUDCOVER") val cdlDarkCloudCover: Double, //  CDL_DARKCLOUDCOVER
    @field:JsonProperty("CDL_DOJI_10_0.1") val cdlDoji1001: Double, //  CDL_DOJI_10_0.1
    @field:JsonProperty("CDL_DOJISTAR") val cdlDojiStar: Double, //  CDL_DOJISTAR
    @field:JsonProperty("CDL_DRAGONFLYDOJI") val cdlDragonflyDoji: Double, //  CDL_DRAGONFLYDOJI
    @field:JsonProperty("CDL_ENGULFING") val cdlEngulfing: Double, //  CDL_ENGULFING
    @field:JsonProperty("CDL_EVENINGDOJISTAR") val cdlEveningDojiStar: Double, //  CDL_EVENINGDOJISTAR
    @field:JsonProperty("CDL_EVENINGSTAR") val cdlEveningStar: Double, //  CDL_EVENINGSTAR
    @field:JsonProperty("CDL_GAPSIDESIDEWHITE") val cdlGapSideSideWhite: Double, //  CDL_GAPSIDESIDEWHITE
    @field:JsonProperty("CDL_GRAVESTONEDOJI") val cdlGravestoneDoji: Double, //  CDL_GRAVESTONEDOJI
    @field:JsonProperty("CDL_HAMMER") val cdlHammer: Double, //  CDL_HAMMER
    @field:JsonProperty("CDL_HANGINGMAN") val cdlHangingMan: Double, //  CDL_HANGINGMAN
    @field:JsonProperty("CDL_HARAMI") val cdlHarami: Double, //  CDL_HARAMI
    @field:JsonProperty("CDL_HARAMICROSS") val cdlHaramiCross: Double, //  CDL_HARAMICROSS
    @field:JsonProperty("CDL_HIGHWAVE") val cdlHighWave: Double, //  CDL_HIGHWAVE
    @field:JsonProperty("CDL_HIKKAKE") val cdlHikkake: Double, //  CDL_HIKKAKE
    @field:JsonProperty("CDL_HIKKAKEMOD") val cdlHikkakeMod: Double, //  CDL_HIKKAKEMOD
    @field:JsonProperty("CDL_HOMINGPIGEON") val cdlHomingPigeon: Double, //  CDL_HOMINGPIGEON
    @field:JsonProperty("CDL_IDENTICAL3CROWS") val cdlIdentical3Crows: Double, //  CDL_IDENTICAL3CROWS
    @field:JsonProperty("CDL_INNECK") val cdlInNeck: Double, //  CDL_INNECK
    @field:JsonProperty("CDL_INSIDE") val cdlInside: Double, //  CDL_INSIDE
    @field:JsonProperty("CDL_INVERTEDHAMMER") val cdlInvertedHammer: Double, //  CDL_INVERTEDHAMMER
    @field:JsonProperty("CDL_KICKING") val cdlKicking: Double, //  CDL_KICKING
    @field:JsonProperty("CDL_KICKINGBYLENGTH") val cdlKickingByLength: Double, //  CDL_KICKINGBYLENGTH
    @field:JsonProperty("CDL_LADDERBOTTOM") val cdlLadderBottom: Double, //  CDL_LADDERBOTTOM
    @field:JsonProperty("CDL_LONGLEGGEDDOJI") val cdlLongLeggedDoji: Double, //  CDL_LONGLEGGEDDOJI
    @field:JsonProperty("CDL_LONGLINE") val cdlLongLine: Double, //  CDL_LONGLINE
    @field:JsonProperty("CDL_MARUBOZU") val cdlMarubozu: Double, //  CDL_MARUBOZU
    @field:JsonProperty("CDL_MATCHINGLOW") val cdlMatchingLow: Double, //  CDL_MATCHINGLOW
    @field:JsonProperty("CDL_MATHOLD") val cdlMatHold: Double, //  CDL_MATHOLD
    @field:JsonProperty("CDL_MORNINGDOJISTAR") val cdlMorningDojiStar: Double, //  CDL_MORNINGDOJISTAR
    @field:JsonProperty("CDL_MORNINGSTAR") val cdlMorningStar: Double, //  CDL_MORNINGSTAR
    @field:JsonProperty("CDL_ONNECK") val cdlOnNeck: Double, //  CDL_ONNECK
    @field:JsonProperty("CDL_PIERCING") val cdlPiercing: Double, //  CDL_PIERCING
    @field:JsonProperty("CDL_RICKSHAWMAN") val cdlRickshawMan: Double, //  CDL_RICKSHAWMAN
    @field:JsonProperty("CDL_RISEFALL3METHODS") val cdlRiseFall3Methods: Double, //  CDL_RISEFALL3METHODS
    @field:JsonProperty("CDL_SEPARATINGLINES") val cdlSeparatingLines: Double, //  CDL_SEPARATINGLINES
    @field:JsonProperty("CDL_SHOOTINGSTAR") val cdlShootingStar: Double, //  CDL_SHOOTINGSTAR
    @field:JsonProperty("CDL_SHORTLINE") val cdlShortLine: Double, //  CDL_SHORTLINE
    @field:JsonProperty("CDL_SPINNINGTOP") val cdlSpinningTop: Double, //  CDL_SPINNINGTOP
    @field:JsonProperty("CDL_STALLEDPATTERN") val cdlStalledPattern: Double, //  CDL_STALLEDPATTERN
    @field:JsonProperty("CDL_STICKSANDWICH") val cdlStickSandwich: Double, //  CDL_STICKSANDWICH
    @field:JsonProperty("CDL_TAKURI") val cdlTakuri: Double, //  CDL_TAKURI
    @field:JsonProperty("CDL_TASUKIGAP") val cdlTasukiGap: Double, //  CDL_TASUKIGAP
    @field:JsonProperty("CDL_THRUSTING") val cdlThrusting: Double, //  CDL_THRUSTING
    @field:JsonProperty("CDL_TRISTAR") val cdlTristar: Double, //  CDL_TRISTAR
    @field:JsonProperty("CDL_UNIQUE3RIVER") val cdlUnique3River: Double, //  CDL_UNIQUE3RIVER
    @field:JsonProperty("CDL_UPSIDEGAP2CROWS") val cdlUpsideGap2Crows: Double, //  CDL_UPSIDEGAP2CROWS
    @field:JsonProperty("CDL_XSIDEGAP3METHODS") val cdlXsideGap3Methods: Double // CDL_XSIDEGAP3METHODS
) {
    constructor(): this(
        Constants.EmptyString,
        Date().toGMTString(),
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
        0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
        0.0
    )


}
