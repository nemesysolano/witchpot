package com.witchpot.preprocessing

import com.witchpot.mappers.UtilDate
import com.witchpot.model.Symbol
import com.witchpot.preprocessing.Trend
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import java.util.*

class TrendTest {
    @Test
    fun loadLinearTrendTest() {
        val symbolsFolder = System.getProperty("symbols.folder").toString()
        val mergedFolder = System.getProperty("merged.folder").toString()
        val symbols = Trend.loadLinearTrend(symbolsFolder, 6)

        assertTrue(symbols[0].ticker.isNotBlank())
        assertTrue(symbols[0].period > 0)

        Trend.saveLinearTrend("$mergedFolder/market_trends.csv", symbols)
    }

    private fun Symbol.utilDate(): Date = UtilDate.fromSymbolDateString(this.date)
}