#include "stockDatabase.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

void stockDatabase::loadCSV(const std::string& filename, size_t max_lines) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Datoteka se ne može otvoriti!" << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // preskoči header

    size_t count = 0;
    while (std::getline(file, line) && count < max_lines) {
        std::stringstream ss(line);
        stockData data;
        std::string date, item;

        std::getline(ss, date, ',');
        std::getline(ss, data.ticker, ',');
        std::getline(ss, item, ','); data.open = item.empty() ? 0.0 : std::stod(item);
        std::getline(ss, item, ','); data.high = item.empty() ? 0.0 : std::stold(item);
        std::getline(ss, item, ','); data.low = item.empty() ? 0.0 : std::stold(item);
        std::getline(ss, item, ','); data.close = item.empty() ? 0.0 : std::stold(item);
        std::getline(ss, item, ','); data.volume = item.empty() ? 0.0 : std::stod(item);
        std::getline(ss, item, ','); data.dividends = item.empty() ? 0.0 : std::stod(item);
        std::getline(ss, item, ','); data.stockSplits = item.empty() ? 0.0 : std::stod(item);

        dateIndex[date].push_back(data);
        ++count;
    }
    lineCount = count;
    std::cout << "Ucitano " << lineCount << " linija." << std::endl;
}

double stockDatabase::averageClose(const std::string& ticker) const {
    long double sum = 0.0;
    size_t count = 0;
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            if (data.ticker == ticker) {
                sum += data.close;
                ++count;
            }
        }
    }
    if (count == 0) {
        std::cerr << "Nema zapisa za ticker: " << ticker << std::endl;
        return 0.0;
    }
    return static_cast<double>(sum / static_cast<long double>(count));
}

size_t stockDatabase::countTicker(const std::string& ticker) const {
    size_t count = 0;
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            if (data.ticker == ticker) ++count;
        }
    }
    return count;
}

void stockDatabase::printStockData(const std::string& date) const {
    auto it = dateIndex.find(date);
    if (it == dateIndex.end()) {
        std::cout << "Nema zapisa za datum: " << date << std::endl;
        return;
    }
    std::cout << "Svi zapisi za datum " << date << " (" << it->second.size() << " zapisa):\n";
    for (const auto& data : it->second) {
        std::cout << data.ticker
            << " | Open: " << data.open
            << " | High: " << data.high
            << " | Low: " << data.low
            << " | Close: " << data.close
            << " | Volume: " << data.volume
            << " | Dividends: " << data.dividends
            << " | Stock Splits: " << data.stockSplits
            << std::endl;
    }
}
