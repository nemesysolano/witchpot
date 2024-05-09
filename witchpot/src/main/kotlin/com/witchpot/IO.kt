package com.witchpot

import com.fasterxml.jackson.dataformat.csv.CsvMapper
import com.fasterxml.jackson.dataformat.csv.CsvParser
import com.fasterxml.jackson.dataformat.csv.CsvSchema
import com.witchpot.model.Symbol
import java.io.FileInputStream

object IO {
    fun loadSymbol(filePath: String): List<Symbol> {

        val inputStream = FileInputStream(filePath)
        val csvMapper = CsvMapper().apply {
            enable(CsvParser.Feature.TRIM_SPACES)
            enable(CsvParser.Feature.SKIP_EMPTY_LINES)
        }
        val schema = CsvSchema.builder().setUseHeader(true).setReorderColumns(true)
            .addColumn("Date")
            .addNumberColumn("High")
            .addNumberColumn("Low")
            .addNumberColumn("Close")
            .addColumn("Adj Close")
            .addNumberColumn("Volume")
            .addNumberColumn("Dividends")
            .addNumberColumn("Stock Splits")
            .apply { CandleCatalog.all.forEach { candleName -> this.addNumberColumn(candleName) } }
            .build()
        return csvMapper.readerFor(Symbol::class.java)
            .with(schema.withSkipFirstDataRow(true))
            .readValues<Symbol>(inputStream)
            .readAll()
            .map { symbol -> symbol.copy(ticker = filePath) }
    }

}