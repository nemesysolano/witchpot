package com.witchpot.model.timeseries.indicators

import com.witchpot.CandleCatalog
import com.witchpot.model.Symbol
import com.witchpot.model.timeseries.SymbolTimeSeries

import kotlin.reflect.KMutableProperty
import kotlin.reflect.full.declaredMemberProperties

class CandleIndicator  (
    private val symbolTimeSeries: SymbolTimeSeries,
    private val candleTrendSummary: Map<String, Pair<Double, Double>>
): Indicator{
    override fun signal(): Map<String, Double> {
        val symbol = symbolTimeSeries.current()

        val strengthPair = candlePropertyMappers
            .filter { property -> property.call(symbol) as Double > 0.0 }
            .fold(
                arrayOf<Double>(0.0, 0.0)
            ) {
                pairSum, property ->
                pairSum[0] += candleTrendSummary[property.name]!!.first // Bearish
                pairSum[1] += candleTrendSummary[property.name]!!.second // Bullish
                pairSum
            }

        return mapOf(
            Pair(BEARISH_STRENGTH, strengthPair[0]),
            Pair(BULLISH_STRENGTH, strengthPair[1])
        )
    }



    companion object {
        const val BEARISH_STRENGTH= "Bearish Strength"
        const val BULLISH_STRENGTH = "Bullish Strength"
        val candlePropertyMappers = fetchCandlePropertyMappers()

        private fun fetchCandlePropertyMappers(): List<KMutableProperty<*>> {
            val clazz = Symbol::class
            val declaredProperties = clazz.declaredMemberProperties

            return CandleCatalog.all
                .map { propertyName -> declaredProperties.find { property -> property.name == propertyName } }
                .map { property -> property as KMutableProperty<*> }
        }
    }
}