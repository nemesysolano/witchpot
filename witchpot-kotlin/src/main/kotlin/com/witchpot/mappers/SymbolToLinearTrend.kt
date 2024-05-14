package com.witchpot.mappers



import com.witchpot.model.Symbol
import com.witchpot.model.SymbolWithTrend
import org.mapstruct.Mapper
import org.mapstruct.Mapping

@Mapper
interface SymbolToLinearTrend {
     @Mapping(target = "rSquaredHigh", constant = "0")
     @Mapping(target = "slopeHigh", constant = "0")
     @Mapping(target = "slopeStDevHigh", constant = "0")
     @Mapping(target = "rSquaredLow", constant = "0")
     @Mapping(target = "slopeLow", constant = "0")
     @Mapping(target = "slopeStDevLow", constant = "0")
     @Mapping(target = "period", constant = "0")
     @Mapping(target = "trendDirection", constant = "0")
    fun toSymbolWithTrend(symbol: Symbol): SymbolWithTrend
}