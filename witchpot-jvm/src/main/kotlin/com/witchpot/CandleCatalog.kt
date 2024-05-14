package com.witchpot

import com.fasterxml.jackson.module.kotlin.jacksonObjectMapper
import com.fasterxml.jackson.module.kotlin.readValue

object CandleCatalog {
    val all = fetchAll()
    val allCsv = fetchCsv()
    private fun fetchAll(): Set<String> {
        val mapper =  jacksonObjectMapper ()
        val result: Set<String> = mapper.readValue<Set<String>>(this.javaClass.getResourceAsStream("/candleColumns.json")!! )
        return result
    }

    private fun fetchCsv(): Set<String> {
        val mapper =  jacksonObjectMapper ()
        val result: Set<String> = mapper.readValue<Set<String>>(this.javaClass.getResourceAsStream("/candleColumnsCsv.json")!! )
        return result
    }
}