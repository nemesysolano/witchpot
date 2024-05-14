package com.witchpot.model.timeseries.indicators

import com.witchpot.model.TimeSeries

interface Indicator
{
    fun signal(): Map<String, Double>
}