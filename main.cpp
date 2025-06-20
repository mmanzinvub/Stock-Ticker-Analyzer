#include "stockDatabase.hpp"
#include <iostream>
#include <chrono>

int main() {
    stockDatabase db;

    auto start_load = std::chrono::high_resolution_clock::now();

    db.loadCSV("../all_stock_data.csv", 34646259);

    auto end_load = std::chrono::high_resolution_clock::now();
    auto duration_load = std::chrono::duration_cast<std::chrono::milliseconds>(end_load - start_load).count();
    std::cout << "Vrijeme ucitavanja: " << duration_load << " ms." << std::endl;

    // Menu
    int choice;
    do {
        std::cout << "\n--- Izbornik ---\n";
        std::cout << "1. Prikazi sve dionice za uneseni datum\n";
        std::cout << "2. Izracunaj prosjecnu zavrsnu cijenu za ticker\n";
        std::cout << "3. Najvisa cijena za ticker u vremenskom rasponu\n";
        std::cout << "4. Pronadi sve jedinstvene oznake dionica\n";
        std::cout << "5. Pronadi odredenu dionicu\n";
        std::cout << "6. Broj datuma s barem jednom dionicom cija je close cijena iznad zadanog praga\n";
        std::cout << "0. Izlaz\n";
        std::cout << "Unesi izbor: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string query_date;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
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
                              << " (" << count << " zapisa) [" << duration << " ms]\n" << std::endl;
                }
                break;
            }
            case 3: {
                std::string query_ticker, start_date, end_date;
                std::cout << "Unesi ticker dionice: ";
                std::cin >> query_ticker;
                std::cout << "Unesi pocetni datum (GGGG-MM-DD): ";
                std::cin >> start_date;
                std::cout << "Unesi zavrsni datum (GGGG-MM-DD): ";
                std::cin >> end_date;

                auto start = std::chrono::high_resolution_clock::now();
                double maxHigh = db.maxHighInRange(query_ticker, start_date, end_date);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                if (maxHigh >= 0) {
                    std::cout << "Najvisa cijena za " << query_ticker << " od " << start_date << " do " << end_date
                              << " je " << maxHigh << " [" << duration << " ms]\n" << std::endl;
                } else {
                    std::cout << "Nema podataka za zadani ticker i raspon datuma\n";
                }
                break;
            }
            case 4: {
                auto start = std::chrono::high_resolution_clock::now();
                auto tickers = db.uniqueTickers();
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Jedinstveni tickeri (" << tickers.size() << ") [" << duration << " ms]\n" << std::endl;
                for (const auto& t : tickers) {
                    std::cout << t << "\n";
                }
                break;
            }
            case 5: {
                std::string query_ticker;
                std::cout << "Unesi ticker koji zelis provjeriti: ";
                std::cin >> query_ticker;
                auto start = std::chrono::high_resolution_clock::now();
                bool exists = db.tickerExists(query_ticker);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                if (exists) {
                    std::cout << "Ticker " << query_ticker << " postoji u skupu podataka [" << duration << " ms]\n" << std::endl;
                } else {
                    std::cout << "Ticker " << query_ticker << " NE postoji u skupu podataka [" << duration << " ms]\n" << std::endl;
                }
                break;
            }
            case 6: {
                long double prag;
                std::cout << "Unesi prag za zavrsnu cijenu (close): ";
                std::cin >> prag;

                auto start = std::chrono::high_resolution_clock::now();
                size_t broj_datuma = db.countDatesWithCloseAbove(prag);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Broj datuma s barem jednom dionicom cija je close cijena iznad " << prag
                          << " je: " << broj_datuma << " [" << duration << " ms]\n" << std::endl;
                break;
            }
            case 0:
                std::cout << "Izlaz iz programa\n";
                break;
            default:
                std::cout << "Ovaj izbor ne postoji. Pokusajte ponovo.\n";
        }
    } while (choice != 0);

    return 0;
}
