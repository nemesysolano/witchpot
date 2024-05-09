package com.witchpot.model

import java.util.*

interface TimeSeries<T> {
    operator fun get(index: Int): T
    operator fun get(timeStamp: Date): Optional<T>
    fun current(): T
    fun currentTimestamp(): Date
    fun currentIndex(): Int
    fun size(): Int
    fun eof(): Boolean
    operator fun inc(): TimeSeries<T>
    fun first(): T
    fun last(): T
}