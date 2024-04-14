/*
 * Autor: Artur Kregiel
 * Grupa: WTP 15:15    (wtorek parzysty godz 15:15)
 * Temat: Laboratorium 3 - ZADANIA DO WYKONANIA
 * Data: 1.12.2022
 */

#define AUTHOR "Artur Kregiel"  // autor
#define GROUP "(WTP 15:15)"    // grupa

#define ROZMIAR 5

#include <iostream> // cout, cin, endl
#include <stdio.h>  // printf, getchar
#include <stdlib.h> // srand, rand
#include <time.h>   // time
#include <iomanip>  // fixed, setprecision

#ifdef _WIN32   // jesli system operacyjny to Windows

/*
* plik naglowkowy conio.h wystepuje najczesciej na urzadzeniach z systemem Windows
* i czesto nie znajduje sie w bibliotece kompilatora na systemach z rodziny UNIX czy Linux
* 
* https://en.wikipedia.org/wiki/Conio.h
*/

#include <conio.h>  // _getch

/*
* Visual Studio nie pozwala na uzycie funkcji getch, poniewaz uwaza ja za przestazala
* i zaleca wykorzystanie '_getch', ktora spelnia to samo zadanie
* 
* Komunikat bledu:
* 'getch': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _getch.
* 
* https://learn.microsoft.com/pl-pl/cpp/c-runtime-library/reference/getch-getwch?view=msvc-170
*/

#endif

// Zadanie 1

// Funkcja wypisujaca zawartosc tablicy
void printArray(const float tab[], const size_t rozmiar = ROZMIAR)
{
    printf("Tab = [  ");
    for (unsigned int i = 0; i < rozmiar; i++)
    {
        printf("%.1f  ", *(tab + i));
    }
    printf("]\n");

    std::cout << std::endl;
}


// Funkcja pozwalajaca na wczytanie z klawiatury wszystkich
// elementow tablicy
void fullfilArray(float tab[], const size_t rozmiar = ROZMIAR)
{
    std::cout << "Wczytaj kolejne elementy tablicy:" << std::endl;
    for (unsigned int i = 0; i < rozmiar; i++)
    {
        printf("Tab[%d] = ", i);
        std::cin >> *(tab + i);
    }

    std::cout << std::endl;
}

// Funkcja wypisujaca ile jest liczb dodatnich i ujemnych, ich sumy oraz srednie
void arrayValuesStats(const float tab[], const size_t rozmiar = ROZMIAR)
{
    // struktura przechowujaca informacje o danych
    // statystycznych na temat liczb dodatnich i ujemnych
    struct Summary
    {
        unsigned int Count;  // ile jest danych liczb
        float Sum;          // jaka jest ich suma
        float Average;     // jaka jest ich srednia
    };

    Summary PositiveNumbers = { 0, 0 }, NegativeNumbers = { 0, 0 };

    for (unsigned int i = 0; i < rozmiar; ++i)
    {
        PositiveNumbers.Count += *(tab + i) > 0 ? 1 : 0;
        PositiveNumbers.Sum += *(tab + i) > 0 ? *(tab + i) : 0;

        NegativeNumbers.Count += *(tab + i) < 0 ? 1 : 0;
        NegativeNumbers.Sum += *(tab + i) < 0 ? *(tab + i) : 0;
    }

    PositiveNumbers.Average = PositiveNumbers.Count ? PositiveNumbers.Sum / PositiveNumbers.Count : -1;
    NegativeNumbers.Average = NegativeNumbers.Count ? NegativeNumbers.Sum / NegativeNumbers.Count : -1;

    std::cout << "Podsumowanie:\n" << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Ile liczb dodatnich: " << PositiveNumbers.Count << std::endl;
    
    if (PositiveNumbers.Count > 0)
    {
        std::cout << "Suma liczb dodatnich: " << PositiveNumbers.Sum << std::endl;
        std::cout << "Wartosc srednia liczb dodatnich: " << PositiveNumbers.Average << std::endl;
    }

    std::cout << "\nIle liczb ujemnych: " << NegativeNumbers.Count << std::endl;
    
    if (NegativeNumbers.Count > 0)
    {
        std::cout << "Suma liczb ujemnych: " << NegativeNumbers.Sum << std::endl;
        std::cout << "Wartosc srednia liczb ujemnych: " << NegativeNumbers.Average << std::endl;
    }
        
    std::cout << std::endl;
}

// Mo¿liwe stany uporzadkowania tablicy
enum ArrayOrderState
{
    Disordered,         // 0
    DescendingOrder,    // 1
    AscendingOrder,     // 2
    NotDescendingOrder, // 3
    NotAscendingOrder,  // 4
    IdenticalElements   // 5
};

// Funkcja wypisujaca informacje o stanie uporzadkowania elementow tablicy
void getArrayOrderInfo(const float tab[], const size_t rozmiar = ROZMIAR)
{
    /*
    std::cout << "Disordered:\t" << Disordered << std::endl;
    std::cout << "DescedingOrder:\t" << DescendingOrder << std::endl;
    std::cout << "AscendingOrder:\t" << AscendingOrder << std::endl;
    std::cout << "NotDescendingOrder:\t" << NotDescendingOrder << std::endl;
    std::cout << "NotAscendingOrder:\t" << NotAscendingOrder << std::endl;
    std::cout << "IdenticalElements:\t" << IdenticalElements << std::endl;
    */

    bool possibleArrayStates[6] = { 1, 1, 1, 1, 1, 1 };

    for (int i = 1; i < rozmiar; ++i)
    {
        // czy elementy sa identyczne?
        if (*(tab + i - 1) != *(tab + i)) possibleArrayStates[IdenticalElements] = false;

        // czy elementy sa uporzadkowane rosnaco?
        if (*(tab + i - 1) >= *(tab + i)) possibleArrayStates[AscendingOrder] = false;

        // czy elementy sa uporzadkowane malejaco?
        if (*(tab + i - 1) <= *(tab + i)) possibleArrayStates[DescendingOrder] = false;

        // czy elementy sa uporzadkowane nierosnaco?
        if (*(tab + i - 1) < *(tab + i)) possibleArrayStates[NotAscendingOrder] = false;

        // czy elementy sa uporzadkowane niemalejaco?
        if (*(tab + i - 1) > *(tab + i)) possibleArrayStates[NotDescendingOrder] = false;
    }

    for (int i = 1; i < rozmiar; i++)
    {
        // jesli tablica jest w jakikolwiek sposob
        // uporzadkowana
        if (possibleArrayStates[i] == true)
        {
            possibleArrayStates[Disordered] = false;
            break;
        }
    }

    // wypisz rezultat
    if (possibleArrayStates[IdenticalElements])
        std::cout << "wszystkie elementy maja jednakowa wartosc" << std::endl;
    else if (possibleArrayStates[AscendingOrder])
        std::cout << "wszystkie elementy sa uporzadkowane rosnaco" << std::endl;
    else if (possibleArrayStates[DescendingOrder])
        std::cout << "wszystkie elementy sa uporzadkowane malejaco" << std::endl;
    else if (possibleArrayStates[NotAscendingOrder])
        std::cout << "wszystkie elementy sa uporzadkowane nierosnaco" << std::endl;
    else if (possibleArrayStates[NotDescendingOrder])
        std::cout << "wszystkie elementy sa uporzadkowane niemalejaco" << std::endl;
    else if (possibleArrayStates[Disordered])
        std::cout << "elementy tablicy nie sa uporzadkowane" << std::endl;

    std::cout << std::endl;
}

// Zadanie 2

// Funkcja wypelniajaca tablice pseudolosowymi wartosciami
// z zadanego zakresu
void randomizeArray(float tab[], const size_t rozmiar = ROZMIAR)
{
    srand(time(NULL));  // inicjalizacja generatora liczb pseudolosowych

    std::cout << "Podaj, z jakiego zakresu ([a;b], a <= b) losowac liczby:" << std::endl;
    std::cout << "a = ";
    int Low;    // poczatek zakresu
    std::cin >> Low;
    std::cout << "b = ";
    int High;   // koniec zakresu
    std::cin >> High;

    if (Low > High)
    {
        std::cout << "b powinno byc nie mniejsze niz a!" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < rozmiar; ++i)
    {
        float random = Low + (High - Low) * rand() / (double)RAND_MAX;
        *(tab + i) = random;
    }

    std::cout << std::endl;
}

// Zadanie 3

// Sortowanie szybkie
void quicksort(float tab[], int left, int right)
{
    int i = left;   // lewy kraniec przedzialu
    int j = right;  // prawy kraniec przedzialu
    float pivot = tab[(left + right) / 2];  // os, punkt odniesienia dla sortowania
    do
    {
        while (tab[i] < pivot) i++; // znajdz liczbe wieksza od osi z lewej strony

        while (tab[j] > pivot) j--; // znajdz liczbe mniejsza od osi z prawej strony

        if (i <= j)
        {
            // zamien liczby miejscami
            float temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    // dziel i zwyciezaj
    if (left < j)
    {
        quicksort(tab, left, j);
    }
    if (right > i)
    {
        quicksort(tab, i, right);
    }
}

// Zadanie 4
void zad4()
{
    std::cout << "ZADANIE 4" << std::endl;

    const unsigned int ALPHABET_LENGTH = 26;
    const char ESCAPE_CHAR = 27; // kod ASCII dla klawisza Esc

    // tablica zliczajajaca czestotliwosc wystepowania liter w tekscie
    unsigned int lettersCount[ALPHABET_LENGTH] = { 0 };

    int characterCount = 0; // licznik wczytanych znakow

    std::cout << "Wpisuj litery: ";

    char character;

    // dopoki nie nacisnieto znaku o kodzie ASCII rownym BREAK_CHAR
#ifdef _WIN32   // jesli system operacyjny to Windows
    while ((character = _getch()) != ESCAPE_CHAR)
#else   // w przeciwnym wypadku
    while ((character = getchar()) != ESCAPE_CHAR)
#endif
    {
#ifdef _WIN32   // jesli system operacyjny to Windows
        if (character == '\r') printf("\n");
        printf("%c", character);    // funkcja _getch zwraca znak "bez echa", czyli go nie wypisuje
#endif
        characterCount++;
        if ('A' <= character && character <= 'Z')   lettersCount[character - 'A']++;
        else if ('a' <= character && character <= 'z')  lettersCount[character - 'a']++;
    }

    printf("\n\nWczytano lacznie %d znakow, w tym:\n\n", characterCount);

    for (unsigned int letter = 0; letter < ALPHABET_LENGTH; letter++)
    {
        printf("litera %c ", letter + 'A');
        for (unsigned int i = 0; i < lettersCount[letter]; i++)  printf("#");
        if (lettersCount[letter]) printf(" %d", lettersCount[letter]);
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    // obowiazkowy wydruk danych autora
    std::cout << "Autor: " << AUTHOR << ' ' << GROUP << std::endl << std::endl;

    float tab[ROZMIAR] = { 0 };

    int choice; // wybor opcji przez uzytkownika
    do
    {
        std::cout << "MENU:" << std::endl;

        std::cout << "\t0 - Wyjscie" << std::endl;
        std::cout << "\t1 - Wypisz tablice [zadanie 1]" << std::endl;
        std::cout << "\t2 - Wypelnij tablice recznie [zadanie 1]" << std::endl;
        std::cout << "\t3 - Wyswietl statystyki dotyczace wartosci tablicy [zadanie 1]" << std::endl;
        std::cout << "\t4 - Sprawdz stan uporzadkowania tablicy [zadanie 1]" << std::endl;
        std::cout << "\t5 - wypelnij tablice wartosciami losowymi [zadanie 2]" << std::endl;
        std::cout << "\t6 - posortuj tablice rosnaco [zadanie 3]" << std::endl;
        std::cout << "\t7 - Uruchomienie zadania 4 (statystyki liter w tekscie) [zadanie 4]" << std::endl;
        std::cout << std::endl;

        std::cout << "Wybierz opcje: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice)
        {
        case 0:
            break;
        case 1:
            printArray(tab);
            break;
        case 2:
            fullfilArray(tab);
            break;
        case 3:
            arrayValuesStats(tab);
            break;
        case 4:
            getArrayOrderInfo(tab);
            break;
        case 5:
            randomizeArray(tab);
            break;
        case 6:
            quicksort(tab, 0, ROZMIAR - 1);
            std::cout << "Posortowano\n" << std::endl;
            break;
        case 7:
            zad4();
            break;
        default:
            std::cout << "Nieznana opcja. Tylko numery od 0 do 7\n" << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
