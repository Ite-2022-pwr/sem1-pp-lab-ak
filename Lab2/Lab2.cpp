/*
 * Autor: Artur Kregiel
 * Grupa: WTP 15:15    (wtorek parzysty godz 15:15)
 * Temat: Laboratorium 2 - ZADANIA DO WYKONANIA
 * Data: 18.11.2022
 */

#include <iostream> // cout, cin, endl
#include <stdio.h>  // printf, snprintf
#include <stdlib.h> // rand
#include <time.h>   // time
#include <string.h> // strlen

#define AUTHOR "Artur Kregiel"  // autor
#define GROUP "(WTP 15:15)"    // grupa

// Zadanie 1
void zad1()
{
    std::cout << "ZADANIE 1" << std::endl;

    std::cout << "Program drukuje tabliczke mnozenia" << std::endl;
    unsigned int Rows, Columns; // liczba wierszy i kolumn tabliczki mnozenia
    std::cout << "Podaj liczbe wierszy: ";
    std::cin >> Rows;   // wczytaj liczbe wierszy
    std::cout << "Podaj liczbe kolumn: ";
    std::cin >> Columns;    // wczytaj liczbe kolumn
    std::cout << std::endl;
    
    char* buffer = new char[20];    // bufor przechowujacy reprezentacje tekstowa liczby
    snprintf(buffer, 20, "%d", Rows * Columns); // najwieksza wartosc jest najdluzsza

    // pobranie dlugosci liczby, ktora posluzy do ustawienia szerokosci kolumn
    const unsigned int CellWidth = strlen(buffer);

    delete[] buffer;    // usuniecie bufora
    

    // wypisz naglowki kolumn
    printf("%*c |", CellWidth, ' ');

    for (unsigned int c = 1; c <= Columns; ++c)
        printf("%*u ", CellWidth, c);
    printf("\n");

    for (unsigned int i = 0; i < (CellWidth + 1) * (Columns + 1); ++i)
        printf("-");
    printf("\n");

    // wypelnij tabliczke mnozenia
    for (unsigned int row = 1; row <= Rows; ++row)
    {
        printf("%*u |", CellWidth, row);

        for (unsigned int col = 1; col <= Columns; ++col)
            printf("%*u ", CellWidth, row * col);

        printf("\n");
    }

    std::cout << std::endl;
}

// Zadanie 2 dla ambitnych
void zad2()
{
    std::cout << "ZADANIE 2" << std::endl;

    std::cout << "Podaj duza liczbe dodatnia (w systemie dziesietnym): ";
    unsigned long Number;
    std::cin >> Number;

    std::cout << "Podaj podstawe systemu liczbowego w jakim ma zostac obliczona suma cyfr: ";
    unsigned short Base;    // numer podstawy systemu numerycznego
    std::cin >> Base;

    unsigned long DigitSum = 0; // suma cyfr liczby (w zadanym systemie pozycyjnym)

    while (Number > 0)
    {
        DigitSum += Number % Base;
        Number /= Base;
    }

    std::cout << "Suma cyfr liczby w systemie " << Base << ": " << DigitSum << std::endl;

    std::cout << std::endl;
}

// Zadanie 3
void zad3()
{
    std::cout << "ZADANIE 3" << std::endl;

    std::cout << "Podaj liczbe a = ";
    int a;
    std::cin >> a;

    std::cout << "Podaj liczbe b = ";
    int b;
    std::cin >> b;

    const int A = a, B = b; // aby nie utracic wartosci liczb a i b

    // NWD
    //for (int temp; b > 0; temp = a % b, a = b, b = temp);

    // algorytm Euklidesa
    while (b != 0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }

    std::cout << "NWD(a, b) = " << a << std::endl;

    // NWW
    //std::cout << "NWW(a, b) = " << (A * B) / a << std::endl;
    
    // wybieramy, aby liczba a byla wieksza od liczby b
    if (A < B)
    {
        a = B;
        b = A;
    }
    else
    {
        a = A;
        b = B;
    }

    int nww;    // Najwieksza Wspolna Wielokrotnosc
    for (nww = a; nww <= A * B; nww += a)
    {
        if (nww % b == 0)
            break;
    }

    std::cout << "NWW(a, b) = " << nww << std::endl;

    std::cout << std::endl;
}

// Zadanie 4
void zad4()
{
    std::cout << "ZADANIE 4" << std::endl;

    std::cout << "Podaj dokladnosc obliczen (epsilon): ";
    double eps; // dokladnosc obliczen (epsilon)
    std::cin >> eps;
    
    // Szereg 1
    double S1 = 0;  // suma szeregu S1

    double SequencePortion; // wyraz ciagu
    unsigned int k = 1;
    
    do
    {
        SequencePortion = 4.0 / (2.0 * k - 1.0);
        S1 += (k + 1) % 2 == 0 ? SequencePortion : -SequencePortion;
        k++;
    } while (SequencePortion > eps);

    std::cout << "S1 = " << S1 << std::endl;

    // Szereg 2
    k = 1;
    SequencePortion = 1.0;  // 1 / 0!

    double S2 = 1.0;    // suma szeregu S2

    do
    {
        SequencePortion /= (double)k;
        S2 += SequencePortion;
        k++;
    } while (SequencePortion > eps);

    std::cout << "S2 = " << S2 << std::endl;

    std::cout << std::endl;
}

// Zadanie 5
void zad5()
{
    std::cout << "ZADANIE 5" << std::endl;

    srand(time(NULL));  // inicjalizacja generatora liczb pseudolosowych

    std::cout << "Podaj, z jakiego zakresu ([a;b], a < b) losowac liczby:" << std::endl;
    std::cout << "a = ";
    int Low;    // poczatek zakresu
    std::cin >> Low;
    std::cout << "b = ";
    int High;   // koniec zakresu
    std::cin >> High;

    if (Low >= High)
    {
        std::cout << "b powinno byc wieksze niz a!" << std::endl;
        return;
    }

    std::cout << "Podaj ile liczb wylosowac: ";
    unsigned int n;
    std::cin >> n;

    // struktura przechowujaca informacje o danych
    // statystycznych na temat liczb dodatnich i ujemnych
    struct Summary
    {
        unsigned int Count; // ile jest danych liczb
        signed int Sum;     // jaka jest ich suma
        double Average;     // jaka jest ich srednia
    };

    Summary PositiveNumbers = { 0, 0 }, NegativeNumbers = { 0, 0 };

    for (unsigned int i = 0; i < n; ++i)
    {
        int random = rand() % (High - Low + 1) + Low;   // wylosowanie liczby losowej z przedzialu
        std::cout << i + 1 << "| losowa = " << random << std::endl;

        PositiveNumbers.Count += random > 0 ? 1 : 0;
        PositiveNumbers.Sum += random > 0 ? random : 0;

        NegativeNumbers.Count += random < 0 ? 1 : 0;
        NegativeNumbers.Sum += random < 0 ? random : 0;
    }

    PositiveNumbers.Average = PositiveNumbers.Count ? (double)PositiveNumbers.Sum / (double)PositiveNumbers.Count : -1;
    NegativeNumbers.Average = NegativeNumbers.Count ? (double)NegativeNumbers.Sum / (double)NegativeNumbers.Count : -1;

    std::cout << "Podsumowanie:" << std::endl;

    std::cout << "Ile liczb dodatnich: " << PositiveNumbers.Count << std::endl;
    if (PositiveNumbers.Count > 0)
        std::cout << "Wartosc srednia liczb dodatnich: " << PositiveNumbers.Average << std::endl;

    std::cout << "Ile liczb ujemnych: " << NegativeNumbers.Count << std::endl;
    if (NegativeNumbers.Count > 0)
        std::cout << "Wartosc srednia liczb ujemnych: " << NegativeNumbers.Average << std::endl;

    std::cout << std::endl;
}

int main()
{
    // obowiazkowy wydruk danych autora
    std::cout << "Autor: " << AUTHOR << ' ' << GROUP << std::endl << std::endl;

    int choice; // wybor opcji przez uzytkownika
    do
    {
        std::cout << "MENU:" << std::endl;

        std::cout << "\t0 - Wyjscie" << std::endl;
        std::cout << "\t1 - Uruchomienie zadania 1 (Tabliczka mnozenia)" << std::endl;
        std::cout << "\t2 - Uruchomienie zadania 2 (Suma cyfr liczby dla ambitnych)" << std::endl;
        std::cout << "\t3 - Uruchomienie zadania 3 (NWD i NWW)" << std::endl;
        std::cout << "\t4 - Uruchomienie zadania 4 (Szeregi)" << std::endl;
        std::cout << "\t5 - Uruchomienie zadania 5 (Liczby losowe)" << std::endl;
        std::cout << std::endl;

        std::cout << "Wybierz opcje: ";
        std::cin >> choice;

        switch (choice)
        {
        case 0:
            break;
        case 1:
            zad1();
            break;
        case 2:
            zad2();
            break;
        case 3:
            zad3();
            break;
        case 4:
            zad4();
            break;
        case 5:
            zad5();
            break;
        default:
            std::cout << "Nieznana opcja. Tylko numery od 0 do 5" << std::endl;
            break;
        }
    }
    while (choice != 0);

    return 0;
}

