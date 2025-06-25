#ifndef STOCKDATABASE_HPP
#define STOCKDATABASE_HPP
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#pragma once

extern const std::unordered_set<std::string> blacklist;

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

    std::unordered_map<std::string, stockData> fastIndex;
public:
    void loadCSV(const std::string& filename, size_t max_lines = 34646259);

    size_t countTicker(const std::string& ticker) const;

    // 1. Dohvati sve podatke o dionicama za određeni datum
    void printStockData(const std::string& date) const;

    // 2. Izračunaj prosječnu završnu cijenu određene dionice u cijelom skupu podataka
    double averageClose(const std::string& ticker) const;

    // 3. Pronađi najvišu cijenu za određenu dionicu u zadanom vremenskom razdoblju
    double maxHighInRange(const std::string& ticker, const std::string& startDate, const std::string& endDate) const;

    // 4. Identificiraj sve jedinstvene oznake dionica u skupu podataka
    std::unordered_set<std::string> uniqueTickers() const;

    // 5. Provjeri postoji li određena oznaka dionice u skupu podataka
    bool tickerExists(const std::string& ticker) const;

    // 6. Izbroji broj datuma kada je barem jedna dionica imala završnu cijenu iznad određenog praga
    size_t countDatesWithCloseAbove(long double threshold) const;

    // 7. Dohvati završnu cijenu određene dionice za određeni datum
    long double getCloseForTickerOnDate(const std::string& ticker, std::string& date) const;

    // 8. Prikaži sve datume i odgovarajuće završne cijene za određenu dionicu
    void printDateAndCloseForTicker(const std::string& ticker) const;

    // 9. Izračunaj ukupni volumen trgovanja za određenu dionicu kroz cijeli skup podataka
    long double totalVolumeForTicker(const std::string& ticker) const;

    // 10. Provjeri ima li podataka za određeni datum i određenu dionicu
    bool existsRecord(const std::string& ticker, const std::string& date) const;

    // 11. Dohvati cijene otvaranja i zatvaranja za određenu dionicu i datum u konstantnom vremenu.
    void buildOpenCloseIndex();
    std::pair<long double, long double> getOpenAndClose(const std::string& ticker, const std::string& date) const;

    // 12. Pronađi iznos dividendi isplacenih za određenu dionicu na određeni datum
    long double dividendForTickerOnDate(const std::string& ticker, const std::string& date) const;

    // 13. Pronađi 10 dionica s najvećim volumenom trgovanja na određeni datum
};

#endif //STOCKDATABASE_HPP