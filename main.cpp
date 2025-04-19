#include "stockDatabase.hpp"
#include <chrono>
#include <iostream>

int main() {
    stockDatabase db;

    auto start_load = std::chrono::high_resolution_clock::now();

    db.loadCSV("../all_stock_data.csv", 511382);

    auto end_load = std::chrono::high_resolution_clock::now();
    auto duration_load = std::chrono::duration_cast<std::chrono::milliseconds>(end_load - start_load).count();

    std::cout << "Vrijeme ucitavanja: " << duration_load << " ms." << std::endl;

    //Get all stock data for specific date
    std::string query_date;
    std::cout << "Unesi datum (YYYY-MM-DD): ";
    std::cin >> query_date;
    db.printStockData(query_date);

    //Calculate average closing price of a certain ticker
    std::string query_ticker;
    std::cout << "Unesi ticker dionice: ";
    std::cin >> query_ticker;

    auto start = std::chrono::high_resolution_clock::now();

    double avg = db.averageClose(query_ticker);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    //Count how many records exist for the entered ticker
    size_t count = db.countTicker(query_ticker);

    if (count > 0) {
        std::cout << "Prosjecna zavrsna cijena za " << query_ticker << " je " << avg
                  << " (" << count << " zapisa, izracunano u " << duration << " ms)" << std::endl;
    }
    return 0;
}
