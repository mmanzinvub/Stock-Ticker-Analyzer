#include "stockDatabase.hpp"
#include <iostream>
#include <chrono>

int main() {
    stockDatabase db;

    auto start_load = std::chrono::high_resolution_clock::now();

    // max 34646259
    db.loadCSV("../all_stock_data.csv", 34646259);

    auto end_load = std::chrono::high_resolution_clock::now();
    auto duration_load = std::chrono::duration_cast<std::chrono::milliseconds>(end_load - start_load).count();
    std::cout << "Vrijeme ucitavanja CSV-a: " << duration_load << " ms" << std::endl;

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
        std::cout << "7. Dohvati zavrsnu cijenu odredene dionice za odredeni datum\n";
        std::cout << "8. Ispisi sve datume i zavrsne cijene za ticker\n";
        std::cout << "9. Izračunaj ukupni volumen trgovanja za određenu dionicu kroz cijeli skup podataka\n";
        std::cout << "10. Provjera podataka za određeni datum i određenu dionicu\n";
        std::cout << "11. Dohvati cijene otvaranja i zatvaranja za određenu dionicu i datum u konstantnom vremenu\n";
        std::cout << "12. Pronađi iznos dividendi isplacenih za određenu dionicu na određeni datum\n";
        std::cout << "13. Pronađi 10 dionica s najvećim volumenom trgovanja na određeni datum\n";
        std::cout << "14. Dohvati 5 dionica s najnižim završnim cijenama kroz cijeli skup podataka\n";
        std::cout << "15. Održavaj popis 5 dionica s najvećim isplaćenim dividendama tijekom cijelog razdoblja skupa podataka\n";
        std::cout << "-1. Rucni unos u skup podataka\n";
        std::cout << "0. Izlaz\n";
        std::cout << "Unesi izbor: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string query_date;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> query_date;

                auto start = std::chrono::high_resolution_clock::now();

                db.printStockData(query_date);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                std::cout << "Vrijeme ucitavanja za opciju 1: " << duration << " ms" << std::endl;
                break;
            }
            case 2: {
                std::string query_ticker;
                std::cout << "Unesi ticker dionice: ";
                std::cin >> query_ticker;

                auto start = std::chrono::high_resolution_clock::now();

                double avg = db.averageClose(query_ticker);

                size_t count = db.countTicker(query_ticker);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                if (count > 0) {
                    std::cout << "Prosjecna zavrsna cijena za " << query_ticker << " je " << avg
                              << " (" << count << " zapisa)" << std::endl;
                }
                std::cout << "Vrijeme ucitavanja za opciju 2: " << duration << " ms" << std::endl;
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
                              << " je " << maxHigh << std::endl;
                } else {
                    std::cout << "Nema podataka za zadani ticker i raspon datuma\n";
                }
                std::cout << "Vrijeme ucitavanja za opciju 3: " << duration << " ms" << std::endl;
                break;
            }
            case 4: {
                auto start = std::chrono::high_resolution_clock::now();

                auto tickers = db.uniqueTickers();

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Jedinstveni tickeri (" << tickers.size() << ")" << std::endl;
                for (const auto& t : tickers) {
                    std::cout << t << "\n";
                }
                std::cout << "Vrijeme ucitavanja za opciju 4: " << duration << " ms" << std::endl;
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
                    std::cout << "Ticker " << query_ticker << " postoji u skupu podataka" << std::endl;
                } else {
                    std::cout << "Ticker " << query_ticker << " NE postoji u skupu podataka" << std::endl;
                }
                std::cout << "Vrijeme ucitavanja za opciju 5: " << duration << " ms" << std::endl;
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
                          << " je: " << broj_datuma << std::endl;
                std::cout << "Vrijeme ucitavanja za opciju 6: " << duration << " ms" << std::endl;
                break;
            }
            case 7: {
                std::string query_ticker;
                std::cout << "Unesi ticker koji zelis provjeriti: ";
                std::cin >> query_ticker;
                std::string query_date;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> query_date;

                auto start = std::chrono::high_resolution_clock::now();

                long double closePriceDate = db.getCloseForTickerOnDate(query_ticker, query_date);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                if (closePriceDate >= 0) {
                    std::cout << "Zavrsna cijena za " << query_ticker << " na " << query_date
                    << " je " << closePriceDate << std::endl;
                } else {
                    std::cout << "Nema podataka za zadani ticker i datum\n";
                }
                std::cout << "Vrijeme ucitavanja za opciju 7: " << duration << " ms" << std::endl;
                break;
            }
            case 8: {
                std::string query_ticker;
                std::cout << "Unesi ticker za koji zelis ispisati sve datume i zavrsne cijene: ";
                std::cin >> query_ticker;

                auto start = std::chrono::high_resolution_clock::now();

                db.printDateAndCloseForTicker(query_ticker);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Vrijeme ucitavanja za opciju 8: " << duration << " ms" << std::endl;
                break;
            }
            case 9: {
                std::string query_ticker;
                std::cout << "Unesi ticker za koji zelis izracunati ukupni volumen trgovanja: ";
                std::cin >> query_ticker;

                auto start = std::chrono::high_resolution_clock::now();

                long double totalVolume = db.totalVolumeForTicker(query_ticker);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Ukupni volumen trgovanja za " << query_ticker << " je: " << totalVolume << std::endl;
                std::cout << "Vrijeme ucitavanja za opciju 9: " << duration << " ms" << std::endl;
                break;
            }
            case 10: {
                std::string query_ticker, query_date;
                std::cout << "Unesi ticker: ";
                std::cin >> query_ticker;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> query_date;

                auto start = std::chrono::high_resolution_clock::now();

                if (db.existsRecord(query_ticker, query_date)) {
                    std::cout << "Podaci postoje za " << query_ticker << " na datum " << query_date << "." << std::endl;
                } else {
                    std::cout << "Nema podataka za " << query_ticker << " na datum " << query_date << "." << std::endl;
                }

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Vrijeme ucitavanja za opciju 10: " << duration << " ms" << std::endl;
                break;
            }
            case 11: {
                std::string ticker, date;
                std::cout << "Unesi ticker: ";
                std::cin >> ticker;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> date;

                auto start = std::chrono::high_resolution_clock::now();

                auto [open, close] = db.getOpenAndClose(ticker, date);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                if (open >= 0 && close >= 0) {
                    std::cout << "Cijena otvaranja za " << ticker << " na " << date << " je: " << open << std::endl;
                    std::cout << "Cijena zatvaranja za " << ticker << " na " << date << " je: " << close << std::endl;
                } else {
                    std::cout << "Nema podataka za ticker '" << ticker << "' na datum " << date << "." << std::endl;
                }
                std::cout << "Vrijeme ucitavanja za opciju 11: " << duration << " ms" << std::endl;
                break;
            }
            case 12: {
                std::string ticker, date;
                std::cout << "Unesi ticker: ";
                std::cin >> ticker;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> date;

                auto start = std::chrono::high_resolution_clock::now();

                long double dividend = db.dividendForTickerOnDate(ticker, date);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                if (dividend >= 0) {
                    std::cout << "Dividenda za " << ticker << " na datum " << date << " je: " << dividend << std::endl;
                } else {
                    std::cout << "Nema podataka o dividendi za taj ticker i datum." << std::endl;
                }
                std::cout << "Vrijeme ucitavanja za opciju 12: " << duration << " ms" << std::endl;
                break;
            }
            case 13: {
                std::string datum;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> datum;

                auto start = std::chrono::high_resolution_clock::now();

                db.top10ByVolume(datum);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Vrijeme ucitavanja za opciju 13: " << duration << " ms" << std::endl;
                break;
            }
            case 14: {
                auto start = std::chrono::high_resolution_clock::now();

                db.printLowestCloseStocks();

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Vrijeme ucitavanja za opciju 14: " << duration << " ms" << std::endl;
                break;
            }
            case 15: {
                auto start = std::chrono::high_resolution_clock::now();

                db.printTopDividendStocks();

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Vrijeme ucitavanja za opciju 15: " << duration << " ms" << std::endl;
                break;
            }
            case -1: {
                auto start = std::chrono::high_resolution_clock::now();

                db.manualInsertRecord();

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "Vrijeme ucitavanja za opciju -1: " << duration << " ms" << std::endl;
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