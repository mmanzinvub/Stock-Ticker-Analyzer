#include "stockDatabase.hpp"
#include <iostream>
#include <unistd.h>

int main() {
    stockDatabase db;

    db.loadCSV("../all_stock_data.csv", 34646259);

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

                double avg = db.averageClose(query_ticker);

                size_t count = db.countTicker(query_ticker);

                if (count > 0) {
                    std::cout << "Prosjecna zavrsna cijena za " << query_ticker << " je " << avg
                              << " (" << count << " zapisa)" << std::endl;
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

                double maxHigh = db.maxHighInRange(query_ticker, start_date, end_date);

                if (maxHigh >= 0) {
                    std::cout << "Najvisa cijena za " << query_ticker << " od " << start_date << " do " << end_date
                              << " je " << maxHigh << std::endl;
                } else {
                    std::cout << "Nema podataka za zadani ticker i raspon datuma\n";
                }
                break;
            }
            case 4: {
                auto tickers = db.uniqueTickers();

                std::cout << "Jedinstveni tickeri (" << tickers.size() << ")" << std::endl;
                for (const auto& t : tickers) {
                    std::cout << t << "\n";
                }
                break;
            }
            case 5: {
                std::string query_ticker;
                std::cout << "Unesi ticker koji zelis provjeriti: ";
                std::cin >> query_ticker;

                bool exists = db.tickerExists(query_ticker);

                if (exists) {
                    std::cout << "Ticker " << query_ticker << " postoji u skupu podataka" << std::endl;
                } else {
                    std::cout << "Ticker " << query_ticker << " NE postoji u skupu podataka" << std::endl;
                }
                break;
            }
            case 6: {
                long double prag;
                std::cout << "Unesi prag za zavrsnu cijenu (close): ";
                std::cin >> prag;

                size_t broj_datuma = db.countDatesWithCloseAbove(prag);

                std::cout << "Broj datuma s barem jednom dionicom cija je close cijena iznad " << prag
                          << " je: " << broj_datuma << std::endl;
                break;
            }
            case 7: {
                std::string query_ticker;
                std::cout << "Unesi ticker koji zelis provjeriti: ";
                std::cin >> query_ticker;
                std::string query_date;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> query_date;

                long double closePriceDate = db.getCloseForTickerOnDate(query_ticker, query_date);

                if (closePriceDate >= 0) {
                    std::cout << "Zavrsna cijena za " << query_ticker << " na " << query_date
                    << " je " << closePriceDate << std::endl;
                } else {
                    std::cout << "Nema podataka za zadani ticker i datum\n";
                }
                break;
            }
            case 8: {
                std::string query_ticker;
                std::cout << "Unesi ticker za koji zelis ispisati sve datume i zavrsne cijene: ";
                std::cin >> query_ticker;

                db.printDateAndCloseForTicker(query_ticker);

                break;
            }
            case 9: {
                std::string query_ticker;
                std::cout << "Unesi ticker za koji zelis izracunati ukupni volumen trgovanja: ";
                std::cin >> query_ticker;

                long double totalVolume = db.totalVolumeForTicker(query_ticker);

                std::cout << "Ukupni volumen trgovanja za " << query_ticker << " je: " << totalVolume << std::endl;
                break;
            }
            case 10: {
                std::string query_ticker, query_date;
                std::cout << "Unesi ticker: ";
                std::cin >> query_ticker;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> query_date;

                if (db.existsRecord(query_ticker, query_date)) {
                    std::cout << "Podaci postoje za " << query_ticker << " na datum " << query_date << "." << std::endl;
                } else {
                    std::cout << "Nema podataka za " << query_ticker << " na datum " << query_date << "." << std::endl;
                }
                break;
            }
            case 11: {
                std::string ticker, date;
                std::cout << "Unesi ticker: ";
                std::cin >> ticker;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> date;

                auto [open, close] = db.getOpenAndClose(ticker, date);
                if (open >= 0 && close >= 0) {
                    std::cout << "Open: " << open << ", Close: " << close << std::endl;
                } else {
                    std::cout << "Nema podatka za taj ticker i datum." << std::endl;
                }
                break;
            }
            case 12: {
                std::string ticker, date;
                std::cout << "Unesi ticker: ";
                std::cin >> ticker;
                std::cout << "Unesi datum (GGGG-MM-DD): ";
                std::cin >> date;

                long double dividend = db.dividendForTickerOnDate(ticker, date);
                if (dividend >= 0) {
                    std::cout << "Dividenda za " << ticker << " na datum " << date << " je: " << dividend << std::endl;
                } else {
                    std::cout << "Nema podataka o dividendi za taj ticker i datum." << std::endl;
                }
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
