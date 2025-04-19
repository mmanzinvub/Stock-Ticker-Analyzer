#include "stockDatabase.hpp"
#include <iostream>
#include <chrono>

int main() {
    stockDatabase db;

    auto start_load = std::chrono::high_resolution_clock::now();

    db.loadCSV("../all_stock_data.csv", 34646259);

    auto end_load = std::chrono::high_resolution_clock::now();
    auto duration_load = std::chrono::duration_cast<std::chrono::milliseconds>(end_load - start_load).count();
    std::cout << "Vrijeme ucitavanja: " << duration_load << " ms." << std::endl;1

    // Menu
    int choice;
    do {
        std::cout << "\n--- Izbornik ---\n";
        std::cout << "1. Prikazi sve dionice za uneseni datum\n";
        std::cout << "2. Izracunaj prosjecnu zavrsnu cijenu za ticker\n";
        std::cout << "3. Izlaz\n";
        std::cout << "Unesi izbor: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string query_date;
                std::cout << "Unesi datum (YYYY-MM-DD): ";
                std::cin >> query_date;
                db.printStockData(query_date);
                break;
            }
            case 2: {
                std::string query_ticker;
                std::cout << "Unesi ticker dionice: ";
                std::cin >> query_ticker;

                auto start = std::chrono::high_resolution_clock::now();
                double avg = db.averageClose(query_ticker);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                size_t count = db.countTicker(query_ticker);

                if (count > 0) {
                    std::cout << "Prosjecna zavrsna cijena za " << query_ticker << " je " << avg
                              << " (" << count << " zapisa, izracunano u " << duration << " ms)" << std::endl;
                }
                break;
            }
            case 3:
                std::cout << "Izlaz iz programa.\n";
                break;
            default:
                std::cout << "Ovaj izbor ne postoji. Pokusajte ponovo.\n";
        }
    } while (choice != 3);

    return 0;
}
