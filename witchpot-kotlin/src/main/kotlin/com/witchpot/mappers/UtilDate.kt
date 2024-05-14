package com.witchpot.mappers

import java.text.SimpleDateFormat
import java.util.*

object UtilDate {
    private val symbolStringDateFormat = SimpleDateFormat("yyyy-MM-dd HH:mm:ssX")
    fun fromSymbolDateString(symbolDateString: String) : Date = symbolStringDateFormat.parse(symbolDateString)
}