#ifndef STOCKDATABASE_HPP
#define STOCKDATABASE_HPP
#include <string>
#include <vector>
#include <unordered_map>
#pragma once

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

using stockHash = std::unordered_map<std::string, std::vector<stockData>>;

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