package com.witchpot.model.timeseries

import com.witchpot.mappers.UtilDate
import com.witchpot.model.Symbol
import java.util.*

 // 1962-01-02 00:00:00-05:00
class SymbolTimeSeries (private val symbols: List<Symbol>) : ListTimeSeries<Symbol>(symbols) {
    private val indexedSymbols = symbols.fold(mutableMapOf<Date, Symbol>()) { folded, current ->
        folded[UtilDate.fromSymbolDateString(current.date)] = current
        folded
    }.toMap()

    override fun get(timeStamp: Date): Optional<Symbol> = Optional.ofNullable(indexedSymbols[timeStamp])
    override fun currentTimestamp() = UtilDate.fromSymbolDateString(get(0).date)

     override fun inc(): SymbolTimeSeries {
        if(this.eof()) {
            throw ArrayIndexOutOfBoundsException()
        }
        currentSymbolIndex --
        return this
    }
 }