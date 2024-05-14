package com.witchpot.model

import com.witchpot.IO
import com.witchpot.mappers.UtilDate
import com.witchpot.model.timeseries.SymbolTimeSeries
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

class SymbolTimeSeriesTest {
    private val symbols = IO.loadSymbol("src/test/resources/AAPL.csv")
    private var timeSeries = SymbolTimeSeries(symbols)

    @Test
    fun validateDateIndexing() {
        val size = symbols.size
        assertEquals(timeSeries.size(), symbols.size)
        assertEquals(size, symbols.count { symbol ->
            timeSeries[symbol.utilDate()].isPresent &&
            timeSeries[symbol.utilDate()].get().date == symbol.date
        })
    }

    @Test
    fun validateReverseIndexing() {
        assertEquals(symbols.last(), timeSeries.first())

        var count = 0
        while(!timeSeries.eof()) {

            val symbol1 = symbols[symbols.size - (count + 1)]
            val symbol2 = timeSeries[count]
            val symbol3 = timeSeries.current()
            assertEquals(timeSeries.currentIndex(), count)
            assertEquals(symbol1, symbol2)
//            assertEquals(symbol2, symbol3)
            timeSeries ++
            count ++
        }
    }
    private fun Symbol.utilDate() = UtilDate.fromSymbolDateString(date)
}