package com.witchpot.model

import com.fasterxml.jackson.annotation.JsonProperty

data class SymbolWithTrend(
    @field:JsonProperty("Ticker") var ticker: String, // Ticker
    @field:JsonProperty("Date") var date: String, //  Date
    @field:JsonProperty("Period") var period: Int, //  Period
    @field:JsonProperty("RSquaredHigh") var rSquaredHigh: Double, //  RSquaredHigh
    @field:JsonProperty("SlopeHigh") var slopeHigh: Double, //  SlopeHigh
    @field:JsonProperty("SlopeStDevHigh") var slopeStDevHigh: Double, //  SlopeStDevHigh
    @field:JsonProperty("RSquaredLow") var rSquaredLow: Double, //  RSquaredLow
    @field:JsonProperty("SlopeLow") var slopeLow: Double, //  SlopeLow
    @field:JsonProperty("SlopeStDevLow") var slopeStDevLow: Double, //  SlopeStDevLow
    @field:JsonProperty("TrendDirection") val trendDirection: Int,//  TrendDirection
    @field:JsonProperty("Open") var open: Double, //  Open
    @field:JsonProperty("High") var high: Double, //  High
    @field:JsonProperty("Low") var low: Double, //  Low
    @field:JsonProperty("Close") var close: Double, //  Close
    @field:JsonProperty("Volume") var volume: Double, //  Volume
    @field:JsonProperty("Dividends") var dividends: Double, //  Dividends
    @field:JsonProperty("Stock Splits") var stockSplits: Double, //  Stock_Splits
    @field:JsonProperty("CDL_2CROWS") var cdl2Crows: Double, //  CDL_2CROWS
    @field:JsonProperty("CDL_3BLACKCROWS") var cdl3BlackCrows: Double, //  CDL_3BLACKCROWS
    @field:JsonProperty("CDL_3INSIDE") var cdl3Inside: Double, //  CDL_3INSIDE
    @field:JsonProperty("CDL_3LINESTRIKE") var cdl3LineStrike: Double, //  CDL_3LINESTRIKE
    @field:JsonProperty("CDL_3OUTSIDE") var cdl3Outside: Double, //  CDL_3OUTSIDE
    @field:JsonProperty("CDL_3STARSINSOUTH") var cdl3StarsInSouth: Double, //  CDL_3STARSINSOUTH
    @field:JsonProperty("CDL_3WHITESOLDIERS") var cdl3WhiteSoldiers: Double, //  CDL_3WHITESOLDIERS
    @field:JsonProperty("CDL_ABANDONEDBABY") var cdlAbandonedBaby: Double, //  CDL_ABANDONEDBABY
    @field:JsonProperty("CDL_ADVANCEBLOCK") var cdlAdvanceBlock: Double, //  CDL_ADVANCEBLOCK
    @field:JsonProperty("CDL_BELTHOLD") var cdlBeltHold: Double, //  CDL_BELTHOLD
    @field:JsonProperty("CDL_BREAKAWAY") var cdlBreakaway: Double, //  CDL_BREAKAWAY
    @field:JsonProperty("CDL_CLOSINGMARUBOZU") var cdlClosingMarubozu: Double, //  CDL_CLOSINGMARUBOZU
    @field:JsonProperty("CDL_CONCEALBABYSWALL") var cdlConcealBabySwall: Double, //  CDL_CONCEALBABYSWALL
    @field:JsonProperty("CDL_COUNTERATTACK") var cdlCounterAttack: Double, //  CDL_COUNTERATTACK
    @field:JsonProperty("CDL_DARKCLOUDCOVER") var cdlDarkCloudCover: Double, //  CDL_DARKCLOUDCOVER
    @field:JsonProperty("CDL_DOJI_10_0.1") var cdlDoji1001: Double, //  CDL_DOJI_10_0.1
    @field:JsonProperty("CDL_DOJISTAR") var cdlDojiStar: Double, //  CDL_DOJISTAR
    @field:JsonProperty("CDL_DRAGONFLYDOJI") var cdlDragonflyDoji: Double, //  CDL_DRAGONFLYDOJI
    @field:JsonProperty("CDL_ENGULFING") var cdlEngulfing: Double, //  CDL_ENGULFING
    @field:JsonProperty("CDL_EVENINGDOJISTAR") var cdlEveningDojiStar: Double, //  CDL_EVENINGDOJISTAR
    @field:JsonProperty("CDL_EVENINGSTAR") var cdlEveningStar: Double, //  CDL_EVENINGSTAR
    @field:JsonProperty("CDL_GAPSIDESIDEWHITE") var cdlGapSideSideWhite: Double, //  CDL_GAPSIDESIDEWHITE
    @field:JsonProperty("CDL_GRAVESTONEDOJI") var cdlGravestoneDoji: Double, //  CDL_GRAVESTONEDOJI
    @field:JsonProperty("CDL_HAMMER") var cdlHammer: Double, //  CDL_HAMMER
    @field:JsonProperty("CDL_HANGINGMAN") var cdlHangingMan: Double, //  CDL_HANGINGMAN
    @field:JsonProperty("CDL_HARAMI") var cdlHarami: Double, //  CDL_HARAMI
    @field:JsonProperty("CDL_HARAMICROSS") var cdlHaramiCross: Double, //  CDL_HARAMICROSS
    @field:JsonProperty("CDL_HIGHWAVE") var cdlHighWave: Double, //  CDL_HIGHWAVE
    @field:JsonProperty("CDL_HIKKAKE") var cdlHikkake: Double, //  CDL_HIKKAKE
    @field:JsonProperty("CDL_HIKKAKEMOD") var cdlHikkakeMod: Double, //  CDL_HIKKAKEMOD
    @field:JsonProperty("CDL_HOMINGPIGEON") var cdlHomingPigeon: Double, //  CDL_HOMINGPIGEON
    @field:JsonProperty("CDL_IDENTICAL3CROWS") var cdlIdentical3Crows: Double, //  CDL_IDENTICAL3CROWS
    @field:JsonProperty("CDL_INNECK") var cdlInNeck: Double, //  CDL_INNECK
    @field:JsonProperty("CDL_INSIDE") var cdlInside: Double, //  CDL_INSIDE
    @field:JsonProperty("CDL_INVERTEDHAMMER") var cdlInvertedHammer: Double, //  CDL_INVERTEDHAMMER
    @field:JsonProperty("CDL_KICKING") var cdlKicking: Double, //  CDL_KICKING
    @field:JsonProperty("CDL_KICKINGBYLENGTH") var cdlKickingByLength: Double, //  CDL_KICKINGBYLENGTH
    @field:JsonProperty("CDL_LADDERBOTTOM") var cdlLadderBottom: Double, //  CDL_LADDERBOTTOM
    @field:JsonProperty("CDL_LONGLEGGEDDOJI") var cdlLongLeggedDoji: Double, //  CDL_LONGLEGGEDDOJI
    @field:JsonProperty("CDL_LONGLINE") var cdlLongLine: Double, //  CDL_LONGLINE
    @field:JsonProperty("CDL_MARUBOZU") var cdlMarubozu: Double, //  CDL_MARUBOZU
    @field:JsonProperty("CDL_MATCHINGLOW") var cdlMatchingLow: Double, //  CDL_MATCHINGLOW
    @field:JsonProperty("CDL_MATHOLD") var cdlMatHold: Double, //  CDL_MATHOLD
    @field:JsonProperty("CDL_MORNINGDOJISTAR") var cdlMorningDojiStar: Double, //  CDL_MORNINGDOJISTAR
    @field:JsonProperty("CDL_MORNINGSTAR") var cdlMorningStar: Double, //  CDL_MORNINGSTAR
    @field:JsonProperty("CDL_ONNECK") var cdlOnNeck: Double, //  CDL_ONNECK
    @field:JsonProperty("CDL_PIERCING") var cdlPiercing: Double, //  CDL_PIERCING
    @field:JsonProperty("CDL_RICKSHAWMAN") var cdlRickshawMan: Double, //  CDL_RICKSHAWMAN
    @field:JsonProperty("CDL_RISEFALL3METHODS") var cdlRiseFall3Methods: Double, //  CDL_RISEFALL3METHODS
    @field:JsonProperty("CDL_SEPARATINGLINES") var cdlSeparatingLines: Double, //  CDL_SEPARATINGLINES
    @field:JsonProperty("CDL_SHOOTINGSTAR") var cdlShootingStar: Double, //  CDL_SHOOTINGSTAR
    @field:JsonProperty("CDL_SHORTLINE") var cdlShortLine: Double, //  CDL_SHORTLINE
    @field:JsonProperty("CDL_SPINNINGTOP") var cdlSpinningTop: Double, //  CDL_SPINNINGTOP
    @field:JsonProperty("CDL_STALLEDPATTERN") var cdlStalledPattern: Double, //  CDL_STALLEDPATTERN
    @field:JsonProperty("CDL_STICKSANDWICH") var cdlStickSandwich: Double, //  CDL_STICKSANDWICH
    @field:JsonProperty("CDL_TAKURI") var cdlTakuri: Double, //  CDL_TAKURI
    @field:JsonProperty("CDL_TASUKIGAP") var cdlTasukiGap: Double, //  CDL_TASUKIGAP
    @field:JsonProperty("CDL_THRUSTING") var cdlThrusting: Double, //  CDL_THRUSTING
    @field:JsonProperty("CDL_TRISTAR") var cdlTristar: Double, //  CDL_TRISTAR
    @field:JsonProperty("CDL_UNIQUE3RIVER") var cdlUnique3River: Double, //  CDL_UNIQUE3RIVER
    @field:JsonProperty("CDL_UPSIDEGAP2CROWS") var cdlUpsideGap2Crows: Double, //  CDL_UPSIDEGAP2CROWS
    @field:JsonProperty("CDL_XSIDEGAP3METHODS") var cdlXsideGap3Methods: Double // CDL_XSIDEGAP3METHODS
)