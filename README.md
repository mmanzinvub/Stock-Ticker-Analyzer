## CSV
https://www.kaggle.com/datasets/jakewright/9000-tickers-of-stock-market-data-full-history/data

## Zadaci i rezultati

### Ucitavanje CSV-a
``Vrijeme ucitavanja CSV-a: 77257 ms``

---

### 1. Prikazi sve dionice za uneseni datum

```
Unesi izbor: 1

Unesi datum (GGGG-MM-DD): 2024-11-04

Svi zapisi za datum 2024-11-04 (6174 zapisa):
ZKIN | Open: 0.505 | High: 0.54 | Low: 0.5002 | Close: 0.5292 | Volume: 8234 | Dividends: 0 | Stock Splits: 0
LDWY | Open: 3.45 | High: 3.45 | Low: 3.45 | Close: 3.45 | Volume: 455 | Dividends: 0 | Stock Splits: 0
PPBT | Open: 3.2 | High: 3.21 | Low: 3.08 | Close: 3.14 | Volume: 238784 | Dividends: 0 | Stock Splits: 0
TOL | Open: 148.74 | High: 150 | Low: 146.7 | Close: 149.72 | Volume: 61576 | Dividends: 0 | Stock Splits: 0
SERV | Open: 10.02 | High: 10.05 | Low: 9.25 | Close: 9.55 | Volume: 1.14436e+06 | Dividends: 0 | Stock Splits: 0
SNBR | Open: 12.8 | High: 13.28 | Low: 12.46 | Close: 13.27 | Volume: 20664 | Dividends: 0 | Stock Splits: 0
PD | Open: 18.22 | High: 18.48 | Low: 18.18 | Close: 18.256 | Volume: 27093 | Dividends: 0 | Stock Splits: 0
MMA | Open: 2.35 | High: 2.3999 | Low: 2.21 | Close: 2.295 | Volume: 7455 | Dividends: 0 | Stock Splits: 0
CGEM | Open: 15.72 | High: 15.72 | Low: 15.36 | Close: 15.36 | Volume: 8381 | Dividends: 0 | Stock Splits: 0
PAX | Open: 11.65 | High: 11.84 | Low: 11.625 | Close: 11.8 | Volume: 68866 | Dividends: 0 | Stock Splits: 0

Vrijeme ucitavanja za opciju 1: 60 ms
```

### 2. Izračunaj prosječnu završnu cijenu određene dionice u cijelom skupu podataka

```
Unesi izbor: 2

Unesi ticker dionice: AAPL

Prosjecna zavrsna cijena za AAPL je 23.0262 (11066 zapisa)

Vrijeme ucitavanja za opciju 2: 2192 ms
```


### 3. Pronađi najvišu cijenu za određenu dionicu u zadanom vremenskom razdoblju.

```
Unesi izbor: 3

Unesi ticker dionice: MSFT

Unesi pocetni datum (GGGG-MM-DD): 1986-03-13

Unesi zavrsni datum (GGGG-MM-DD): 2024-11-04

Najvisa cijena za MSFT od 1986-03-13 do 2024-11-04 je 468.35

Vrijeme ucitavanja za opciju 3: 1040 ms
```

### 4. Identificiraj sve jedinstvene oznake dionica u skupu podataka

```
Unesi izbor: 4

Jedinstveni tickeri (9315)
CHKEL
GRAMW
LGNZZ
INR
CHAR
GACW
CHNEY
ISMCF
IVHI
O-P
CSR-PC
AUDAQ
SMKUF
SWN
PRFT
SMKUY
BACA
LCW
RPHM
HMNF
GDL-PC
TELL
WHLRL
GECCM
TMDIF
GEHDY
RBCP


Vrijeme ucitavanja za opciju 4: 4858 ms
```

### 5. Provjeri postoji li određena oznaka dionice u skupu podataka

```
Unesi izbor: 5

Unesi ticker koji zelis provjeriti: IBM

Ticker IBM postoji u skupu podataka

Vrijeme ucitavanja za opciju 5: 0 ms
```

### 6. Izbroji broj datuma kada je barem jedna dionica imala završnu cijenu iznad određenog praga.

```
Unesi izbor: 6

Unesi prag za zavrsnu cijenu (close): 500

Broj datuma s barem jednom dionicom cija je close cijena iznad 500 je: 11265

Vrijeme ucitavanja za opciju 6: 14 ms
```

### 7. Dohvati završnu cijenu određene dionice za određeni datum

```
Unesi izbor: 7

Unesi ticker koji zelis provjeriti: MSFT

Unesi datum (GGGG-MM-DD): 2024-06-06

Zavrsna cijena za MSFT na 2024-06-06 je 424.52

Vrijeme ucitavanja za opciju 7: 0 ms
```

### 8. Prikaži sve datume i odgovarajuće završne cijene za određenu dionicu.

```
Unesi izbor: 8

Unesi ticker za koji zelis ispisati sve datume i zavrsne cijene: AAPL
2024-11-04 : 220.78
2024-10-31 : 225.91
2024-10-25 : 231.41
2024-10-24 : 230.57
2024-10-23 : 230.76
2024-10-21 : 236.48
2024-10-17 : 232.15
2024-10-16 : 231.78
2024-10-10 : 229.04
2024-10-08 : 225.77
2024-09-30 : 233
2024-09-20 : 228.2
2024-09-19 : 228.87
2024-09-11 : 222.66
2024-09-10 : 220.11
2024-09-09 : 220.91
2024-09-06 : 220.82
2024-09-05 : 222.38
itd.
```

### 9. Izračunaj ukupni volumen trgovanja za određenu dionicu kroz cijeli skup podataka

```
Unesi izbor: 9
Unesi ticker za koji zelis izracunati ukupni volumen trgovanja: AAPL
Ukupni volumen trgovanja za AAPL je: 3.50166e+12
Vrijeme ucitavanja za opciju 9: 1095 ms
```

### 10. Provjeri ima li podataka za određeni datum i određenu dionicu.

```
Unesi izbor: 10
Unesi ticker: TSLA
Unesi datum (GGGG-MM-DD): 2024-11-04
Podaci postoje za TSLA na datum 2024-11-04.
Vrijeme ucitavanja za opciju 10: 0 ms
```

### 11. Dohvati cijene otvaranja i zatvaranja za određenu dionicu i datum u konstantnom vremenu.

```
Unesi izbor: 11
Unesi ticker: AAPL
Unesi datum (GGGG-MM-DD): 2024-10-10
Cijena otvaranja za AAPL na 2024-10-10 je: 227.78
Cijena zatvaranja za AAPL na 2024-10-10 je: 229.04
Vrijeme ucitavanja za opciju 11: 0 ms
```

### 12. Pronađi iznos dividendi isplacenih za određenu dionicu na određeni datum.

```
Unesi izbor: 12
Unesi ticker: TOPS
Unesi datum (GGGG-MM-DD): 2006-04-12
Dividenda za TOPS na datum 2006-04-12 je: 1000
Vrijeme ucitavanja za opciju 12: 0 ms
```

### 13. Pronađi 10 dionica s najvećim volumenom trgovanja na određeni datum.

```
Unesi izbor: 13
Unesi datum (GGGG-MM-DD): 2024-11-04
Top 10 dionica po volumenu na datum 2024-11-04:
ELAB : 7.92282e+07
CTM : 4.54062e+07
ADN : 3.82813e+07
ASII : 3.64494e+07
NVDA : 2.7591e+07
NUWE : 2.51879e+07
GSAT : 2.16014e+07
DJT : 2.07187e+07
STAF : 2.02874e+07
SMCI : 1.81587e+07
Vrijeme ucitavanja za opciju 13: 10 ms
```

### 14. Dohvati 5 dionica s najnižim završnim cijenama kroz cijeli skup podataka.

```
Unesi izbor: 14
PTPIF : -8.21004e+25
NPPXF : -4.29042e+19
TETAB : -1.91784e+12
FANUF : -5.12811e+09
PPERF : -8.12967e+07
Vrijeme ucitavanja za opciju 14: 45138 ms
```

### 15. Održavaj popis 5 dionica s najvećim isplaćenim dividendama tijekom cijelog razdoblja skupa podataka.

```
Unesi izbor: 15
PSHG : 13185.4
OSCUF : 9064.88
TOPS : 8000
NTTDF : 6213.5
GLAE : 5600
Vrijeme ucitavanja za opciju 15: 3862 ms
```
