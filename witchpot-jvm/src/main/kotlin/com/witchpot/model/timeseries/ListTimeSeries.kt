package com.witchpot.model.timeseries

import com.witchpot.model.TimeSeries

abstract class ListTimeSeries<T> (private val symbols: List<T>): TimeSeries<T>
{
    protected var currentSymbolIndex = 0
    override fun get(index: Int): T = symbols[symbols.size -( index + 1)]
    override fun current(): T = symbols[currentSymbolIndex]
    override fun currentIndex() = currentSymbolIndex
    override fun size() = symbols.size
    override fun eof(): Boolean = currentSymbolIndex == -1
    override fun first(): T = symbols[symbols.size-1]
    override fun last(): T = symbols[0]
}