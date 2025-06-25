#include "stockDatabase.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

// CSV ticker blacklist
const std::unordered_set<std::string> blacklist = {
    "PTPIF", "BMNR", "IDEX",
    "SNWR", "NDEKF", "MSSV",
    "TMGI", "TETAB", "SMFNF",
    "PPERF", "FANUF", "NPPXF"
};

// CSV parsing
void stockDatabase::loadCSV(const std::string& filename, size_t max_lines) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Datoteka se ne moze otvoriti!" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    size_t count = 0;
    while (std::getline(file, line) && count < max_lines) {
        std::stringstream ss(line);
        stockData data;
        std::string date, item;

        std::getline(ss, date, ',');
        std::getline(ss, data.ticker, ',');

        if (blacklist.count(data.ticker)) {
            continue;
        }

        std::getline(ss, item, ',');
        data.open = item.empty() ? 0.0 : std::stod(item);

        std::getline(ss, item, ',');
        data.high = item.empty() ? 0.0 : std::stold(item);

        std::getline(ss, item, ',');
        data.low = item.empty() ? 0.0 : std::stold(item);

        std::getline(ss, item, ',');
        data.close = item.empty() ? 0.0 : std::stold(item);

        std::getline(ss, item, ',');
        data.volume = item.empty() ? 0.0 : std::stod(item);

        std::getline(ss, item, ',');
        data.dividends = item.empty() ? 0.0 : std::stod(item);

        std::getline(ss, item, ',');
        data.stockSplits = item.empty() ? 0.0 : std::stod(item);

        dateIndex[date].push_back(data);
        ++count;
    }
    lineCount = count;
    std::cout << "Ucitano " << lineCount << " linija." << std::endl;
}

// Metoda broji koliko se puta odredeni ticker pojavljuje u skupu podataka
size_t stockDatabase::countTicker(const std::string& ticker) const {
    size_t count = 0;
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            if (data.ticker == ticker) ++count;
        }
    }
    return count;
}

// 1. Dohvati sve podatke o dionicama za određeni datum.
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

// 2. Izračunaj prosječnu završnu cijenu određene dionice u cijelom skupu podataka
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

// 3. Pronađi najvišu cijenu za određenu dionicu u zadanom vremenskom razdoblju.
double stockDatabase::maxHighInRange(const std::string& ticker, const std::string& startDate, const std::string& endDate) const {
    long double maxHigh = -1.0;
    for (const auto& [date, vector] : dateIndex) {
        if (date >= startDate && date <= endDate) {
            for (const auto& data : vector) {
                if (data.ticker == ticker && data.high > maxHigh) {
                    maxHigh = data.high;
                }
            }
        }
    }
    return static_cast<double>(maxHigh);
}

// 4. Identificiraj sve jedinstvene oznake dionica u skupu podataka
std::unordered_set<std::string> stockDatabase::uniqueTickers() const {
    std::unordered_set<std::string> tickers;
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            tickers.insert(data.ticker);
        }
    }
    return tickers;
}

// 5. Provjeri postoji li određena oznaka dionice u skupu podataka
bool stockDatabase::tickerExists(const std::string& ticker) const {
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            if (data.ticker == ticker) {
                return true;
            }
        }
    }
    return false;
}

// 6. Izbroji broj datuma kada je barem jedna dionica imala završnu cijenu iznad određenog praga
size_t stockDatabase::countDatesWithCloseAbove(long double threshold) const {
    size_t count = 0;
    for (const auto& [date, vector] : dateIndex) {
        bool found = false;
        for (const auto& data : vector) {
            if (data.close > threshold) {
                found = true;
                break;
            }
        }
        if (found) ++count;
    }
    return count;
}

// 7. Dohvati završnu cijenu određene dionice za određeni datum
long double stockDatabase::getCloseForTickerOnDate(const std::string& ticker, std::string& date) const {
    auto it = dateIndex.find(date);
    if (it == dateIndex.end()) {
        return -1.0;
    }

    for (const auto& data : it->second) {
        if (data.ticker == ticker) {
            return data.close;
        }
    }
    return -1.0;
}

// 8. Prikaži sve datume i odgovarajuće završne cijene za određenu dionicu
void stockDatabase::printDateAndCloseForTicker(const std::string& ticker) const {
    bool found = false;
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            if (data.ticker == ticker) {
                std::cout << date << " : " << data.close << std::endl;
                found = true;
            }
        }
    }
    if (found == false) {
        std::cout << "Nema podataka za ticker: " << ticker << std::endl;
    }
}

// 9. Izračunaj ukupni volumen trgovanja za određenu dionicu kroz cijeli skup podataka
long double stockDatabase::totalVolumeForTicker(const std::string& ticker) const {
    long double totalVolume = 0.0;
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            if (data.ticker == ticker) {
                totalVolume += data.volume;
            }
        }
    }
    return totalVolume;
}

// 10. Provjeri ima li podataka za određeni datum i određenu dionicu
bool stockDatabase::existsRecord(const std::string& ticker, const std::string& date) const {
    auto it = dateIndex.find(date);
    if (it == dateIndex.end()) {
        return false;
    }
    for (const auto& data : it->second) {
        if (data.ticker == ticker) {
            return true;
        }
    }
    return false;
}

// 11. Dohvati cijene otvaranja i zatvaranja za određenu dionicu i datum u konstantnom vremenu
void stockDatabase::buildOpenCloseIndex() {
    fastIndex.clear();
    for (const auto& [date, vector] : dateIndex) {
        for (const auto& data : vector) {
            std::string key = date + "|" + data.ticker;
            fastIndex[key] = data;
        }
    }
}

std::pair<long double, long double> stockDatabase::getOpenAndClose(const std::string& ticker, const std::string& date) const {
    std::string key = date + "|" + ticker;
    auto it = fastIndex.find(key);
    if (it != fastIndex.end()) {
        return {it->second.open, it->second.close};
    } else {
        return {-1.0, -1.0};
    }
}

// 12. Pronađi iznos dividendi isplacenih za određenu dionicu na određeni datum
long double stockDatabase::dividendForTickerOnDate(const std::string& ticker, const std::string& date) const {
    auto it = dateIndex.find(date);
    if (it == dateIndex.end()) {
        return -1.0;
    }
    for (const auto& data : it->second) {
        if (data.ticker == ticker) {
            return data.dividends;
        }
    }
    return -1.0;
}

// 13. Pronađi 10 dionica s najvećim volumenom trgovanja na određeni datum
