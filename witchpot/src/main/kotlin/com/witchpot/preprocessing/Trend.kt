package com.witchpot.preprocessing
import com.fasterxml.jackson.core.JsonGenerator
import com.fasterxml.jackson.dataformat.csv.CsvMapper
import com.fasterxml.jackson.dataformat.csv.CsvParser
import com.fasterxml.jackson.dataformat.csv.CsvSchema
import com.witchpot.CandleCatalog
import com.witchpot.mappers.SymbolToLinearTrend
import com.witchpot.model.SymbolWithTrend
import com.witchpot.model.Symbol
import org.apache.commons.math.stat.regression.SimpleRegression
import org.mapstruct.factory.Mappers
import com.witchpot.IO.loadSymbol
import java.io.FileOutputStream
import java.nio.file.Files
import java.nio.file.Path
import java.nio.file.Paths
import java.util.stream.Collectors
import java.util.stream.IntStream
import kotlin.io.path.isDirectory
import kotlin.math.abs
import kotlin.reflect.KMutableProperty
import kotlin.reflect.full.declaredMemberProperties

object Trend {
    private val symbolToLinearTrendMapper: SymbolToLinearTrend = Mappers.getMapper(SymbolToLinearTrend::class.java)
    private val linearTrendDynamicPropertyMapper = fetchLinearTrendDynamicPropertyMapper()
    fun loadLinearTrend(symbolsFolder: String, period: Int) = fileList(symbolsFolder)
        .parallelStream()
        .filter() { path -> !path.isDirectory() }
        .map { path -> addTrends(loadSymbol(path.toFile().absolutePath), period) }
        .collect(Collectors.toList())
        .flatten()
        // fileList(symbolsFolder).take(1).map {  path -> addTrends(loadSymbol(path.toFile().absolutePath), period) }.flatten()

    fun saveLinearTrend(mergedFile: String, symbolWithTrendList: List<SymbolWithTrend>) {
        val csvMapper = CsvMapper().apply {
            enable(CsvParser.Feature.TRIM_SPACES)
            enable(CsvParser.Feature.SKIP_EMPTY_LINES)
            configure(JsonGenerator.Feature.IGNORE_UNKNOWN,true)
        }
        val csvSchema = CsvSchema.builder().setReorderColumns(true)
            .addColumn("Ticker")
            .addColumn("Date")
            .addNumberColumn("Period")
            .addNumberColumn("RSquaredHigh")
            .addNumberColumn("SlopeHigh")
            .addNumberColumn("SlopeStDevHigh")
            .addNumberColumn("RSquaredLow")
            .addNumberColumn("SlopeLow")
            .addNumberColumn("SlopeStDevLow")
            .addNumberColumn("TrendDirection")
            .addNumberColumn("Open")
            .addNumberColumn("High")
            .addNumberColumn("Low")
            .addNumberColumn("Close")
            .addNumberColumn( "Adj Close")
            .addNumberColumn("Volume")
            .addNumberColumn("Dividends")
            .apply { CandleCatalog.allCsv.forEach { candleName -> this.addNumberColumn(candleName) } }
            .build()

        FileOutputStream(mergedFile)
        .apply {
            csvMapper.writer().with(csvSchema.withHeader()).writeValues(this).writeAll(symbolWithTrendList)
            flush()
            close()
        }

    }
    private fun fileList(symbolsFolder: String): List<Path> = Files.list(Paths.get(symbolsFolder)).collect(Collectors.toList())

    private fun addTrends(symbols: List<Symbol>, period: Int): List<SymbolWithTrend> {

        return IntStream.range(0, symbols.size).mapToObj() { index -> addTrend(
            symbols,
            index,
            period
        ) }.collect(Collectors.toList())
    }

    private fun addTrend(symbols: List<Symbol>, index: Int, period: Int): SymbolWithTrend {
        val linearTrend = symbolToLinearTrendMapper.toLinearTrend(symbols[index])
        val lowRegression = SimpleRegression()
        val highRegression = SimpleRegression()
        val end = (index + period - 1).coerceAtMost(symbols.size) - 1
        var rSquaredHigh = 0.0
        var slopeHigh =  0.0
        var slopeStDevHigh =  0.0
        var rSquaredLow =  0.0
        var slopeLow =  0.0
        var slopeStDevLow =  0.0
        var trendDirection = 0
        var increment:Int = 0

        for(current in index..end) {
            lowRegression.addData(increment.toDouble(), symbols[current].low)
            highRegression.addData(increment.toDouble(), symbols[current].high)
            increment ++
        }

        rSquaredLow = lowRegression.rSquare
        slopeLow =  lowRegression.slope
        slopeStDevLow =  lowRegression.slopeStdErr
        rSquaredHigh = highRegression.rSquare
        slopeHigh =  highRegression.slope
        slopeStDevHigh = highRegression.slopeStdErr

        trendDirection = when{
            slopeLow > 0.0 && rSquaredLow > 0.5 -> 1
            slopeHigh < 0.0 && rSquaredHigh > 0.5 -> -1
            else -> 0
        }
        lowRegression.clear()
        highRegression.clear()


        val updatedLinearTrend = linearTrend.copy(
            ticker = linearTrend.ticker.substring(linearTrend.ticker.lastIndexOf('/') + 1).run { this.substring(0, this.lastIndexOf('.')) },
            period = period,
            rSquaredHigh = rSquaredHigh,
            slopeHigh = slopeHigh,
            slopeStDevHigh = slopeStDevHigh,
            rSquaredLow = rSquaredLow,
            slopeLow = slopeLow,
            slopeStDevLow = slopeStDevLow,
            trendDirection = trendDirection
        )

        for(declaredProperty in linearTrendDynamicPropertyMapper) {
            val propertyValue = abs((declaredProperty.getter.call(updatedLinearTrend) as Double).toLong())
            val candleValue = when(propertyValue) {
                0L -> 0
                else -> trendDirection
            }

            declaredProperty.setter.call(updatedLinearTrend, candleValue)
        }

        return updatedLinearTrend
    }

    private fun fetchLinearTrendDynamicPropertyMapper(): List<KMutableProperty<*>> {
        val clazz = SymbolWithTrend::class
        val declaredProperties = clazz.declaredMemberProperties

        return CandleCatalog.all
            .map { propertyName -> declaredProperties.find { property -> property.name == propertyName } }
            .map { property -> property as KMutableProperty<*> }
    }

}