#ifndef STOCKDATABASE_HPP
#define STOCKDATABASE_HPP
#include <string>
#include <vector>
#include <unordered_map>
#pragma once

/*
 * struct stockData is how a row looks like in the CSV, used for storing it in vector
*/
struct stockData {
    std::string ticker;
    double open;
    long double high;
    long double low;
    long double close;
    double volume;
    double dividends;
    double stockSplits;
};

/*
 * declaration of the new data type 'stockHash'
 *      key (string)               value (vector)
 *      input                      struct stockData
 * e.g. "2022-01-01": [StockRecord(AAPL), StockRecord(MSFT)] ---> this whole row is a hash map
*/
using stockHash = std::unordered_map<std::string, std::vector<stockData>>;

/*
 * stockDatabase is a class to save stock data and provides methods for accessing data in the 'mini DB' here
 *
 * stockHash is a newly declared type 'stockHash' which holds a row like one above, its variable name is dateIndex
 * It groups all stock records by date for fast lookup and efficient queries.
 *
 * size_t is an unsigned integer data type used for counts, variable name is lineCount obv
 * It just tells us how many records were loaded from CSV
 *
 * Methods:
 * loadCSV -
 * Reads and parses each line of the CSV.
 * Extracts the date and stock data.
 * Inserts each stock record into dateIndex under the correct date.
 * Increments lineCount for each line processed.
 *
 * averageClose -
 * Calculates the average closing price for a specific ticker (e.g. "AAPL").
 * Iterates through all records in dateIndex.
 * For each record with a matching ticker, adds its close price to a sum and counts it.
 * Returns the average
 *
 * countTicker -
 * Counts how many records exist for a given ticker in the loaded data.
 * Iterates through all records in dateIndex.
 * For each record with a matching ticker, increments a counter.
 * Returns the count.
 *
 * printStockData -
 * Prints all stock records for a specific date.
 * Looks up the date in dateIndex.
 * If found, prints all stock records for that date.
 * If not found, prints a message that there is no data for that date.
*/
class stockDatabase {
private:
    stockHash dateIndex;
    size_t lineCount = 0;
public:
    void loadCSV(const std::string& filename, size_t max_lines = 34646259);
    double averageClose(const std::string& ticker) const;
    size_t countTicker(const std::string& ticker) const;
    void printStockData(const std::string& date) const;
};

#endif //STOCKDATABASE_HPP