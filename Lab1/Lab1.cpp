/*
 * Autor: Artur Kręgiel
 * Grupa: WT/P 15:15    (wtorek parzysty godz 15:15)
 * Temat: Laboratorium 1 - ZADANIA DO WYKONANIA
 * Data: 22.10.2022
 */

#include <iostream>     // cout, cin, endl
#include <math.h>       // M_PI, sqrt
#include <string.h>     // strlen, memset
#include <stdio.h>      // printf, snprintf

#define AUTHOR "Artur Kregiel"  // autor
#define GROUP "(WT/P 15:15)"    // grupa

#define BUFFSIZE 256

using std::cout;
using std::cin;
using std::endl;

// ---> ZADANIE 1 <--- //

// oblicza delte
double CalcDelta(double a, double b, double c)
{
    double delta = b * b - 4 * a * c;
    return delta;
}

void zad1()
{
    // wspolczynniki wielomianu ax^2 + bx + c
    double a, b, c;

    cout << "Podaj wspolczynniki rownania kwadratowego: (a b c): ";

    cin >> a >> b >> c;

    if (a == 0)
    {
        cout << "Niepoprawne rownanie kwadratowe" << endl;
        return;
    }

    double delta = CalcDelta(a, b, c);

    cout << "Delta: " << delta << endl;

    if (delta < 0)
    {
        cout << "Brak pierwiastków rzeczywistych" << endl;
        return;
    }
    else if (delta == 0)
    {
        double x = (-b) / (2 * a);
        cout << "Pierwiastek podwójny: " << x << endl;
        return;
    }
    else
    {
        double x1, x2;
        x1 = (-b - sqrt(delta)) / (2 * a);
        x2 = (-b + sqrt(delta)) / (2 * a);

        cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
        return;
    }
}

// ---> ZADANIE 2 <--- //

// struktura do przechowywania daty
typedef struct
{
    int day;
    int month;
    int year;
} mydate_t;

// pobranie daty od uzytkowanika
void GetDateInput(mydate_t &date)
{
    cin >> date.day;
    cin >> date.month;
    cin >> date.year;
}

// sprawdzenie czy data jest poprawna
bool ValidateDate(mydate_t date)
{
    if (date.year < 1)
        return false;

    // numer miesiaca musi nalezec do przedzialu [1;12] (styczen-grudzien)
    if (date.month < 1 || date.month > 12)
        return false;

    // czy jest to rok przestepny
    bool isLeap = true;

    // jesli nie dzieli sie na 4
    if ((date.year % 4 != 0))
        isLeap = false; // nie jest przestepny

    if (date.year % 100 == 0 && date.year % 400 != 0)
        isLeap = false; // nie jest przestepny
    
    int maxDay; // maksymalna liczba dni w miesiacu

    // ustalenie maksymalnej liczby dni dla danego miesiaca
    switch (date.month)
    {
        // jesli miesiac to luty
        case 2:
            // sprawdzenie, czy rok jest przestepny
            maxDay = isLeap ? 29 : 28;
            break;

        // miesiace majace po 31 dni
        case 1:     // styczen
        case 3:     // marzec
        case 5:     // maj
        case 7:     // lipiec
        case 8:     // sierpien
        case 10:    // pazdziernik
        case 12:    // grudzien
            maxDay = 31;
            break;

        // pozostale miesiace maja po 30 dni
        default:
            maxDay = 30;
            break;
    }

    // jesli dzien nie miesci sie w dobrym przedziale
    if (date.day < 1 || date.day > maxDay)
        return false;

    // jesli nie zostal wczesniej zwrocony falsz,
    // to znaczy, ze data jest poprawna
    return true;
}

void zad2()
{
    cout << "ZADANIE 2" << endl;

    mydate_t date;  // data

    cout << "Wpisz date (dd mm yyyy): ";
    GetDateInput(date); // pobranie daty od uzytkownika
    bool isDateGood = ValidateDate(date);   // sprawdzenie poprawnosci daty

    cout << "Data " << date.day << "/";
    cout << date.month << "/" << date.year << " ";

    if (!isDateGood)
        cout << "nie ";

    cout << "jest poprawna." << endl;
}

// ---> ZADANIE 3 <--- //

// sprawdzenie czy z 3 odcinkow o podanych dlugosciach
// mozna utworzyc trojkat
bool IsTriangle(double a, double b, double c)
{
    // nierownosc trojkata
    return (a + b > c && b + c > a && a + c > b);
}

// wypisanie jakiego typu jest trojkat
void PrintTriangleType(double a, double b, double c)
{
    // wybieramy c jako najdluzszy odcinek
    if (a > b && a > c)
    {
        double temp = a;
        a = c;
        c = temp;
    }
    else if (b > a && b > c)
    {
        double temp = b;
        b = c;
        c = temp;
    }

    cout << "Ten trojkat jest ";

    // sprawdzenie rodzaju trojkata bazujac na twierdzeniu Pitagorasa
    double ab = a * a + b * b;  // a^2 + b^2
    if (ab == c * c)
        cout << "prostokatny";
    else if (ab > c * c)
        cout << "ostrokatny";
    else
        cout << "rozwartokatny";

    // znalezienie liczby par rownych odcinkow
    int n = 0;
    if (a == b)
        n++;
    if (b == c)
        n++;
    if (a == c)
        n++;

    if (n == 3)
        cout << " i rownoboczny";    // równoboczny
    else if (n == 1)    // istnieje tylko jedna para rownych bokow
        cout << " i rownoramienny";  // równoramienny

    cout << "." << endl;

}

void zad3()
{
    cout << "ZADANIE 3" << endl;

    double a, b, c;
    cout << "Podaj 3 dodatnie liczby (a b c): ";
    cin >> a >> b >> c;

    if (a <= 0 || b <= 0 || c <= 0)
    {
        cout << "BLAD: Liczby powinny byc dodatnie!" << endl;
        return;
    }

    cout << "Z odcinkow tej dlugosci ";

    bool isTriangle = IsTriangle(a, b, c);  // czy z podanych odcinkow mozna utworzyc trojkat?

    if (!isTriangle)    // jesli nie
        cout << "nie mozna utworzyc trojkata" << endl;
    else
        cout << "mozna utworzyc trojkat" << endl;

    if (!isTriangle)
        return;

    // jesli mozna utworzyc trojkat z podanych odcinkow,
    // wypisujemy jakiego rodzaju jest trojkat
    PrintTriangleType(a, b, c);
}

// ---> ZADANIE 4 <---

// pole trojkata
double CircleArea(double r)
{
    return M_PI * r * r;
}

// obwod trojkata
double CircleCircumference(double r)
{
    return 2 * M_PI * r;
}

// wypisuje pozioma linie okreslonej dlugosci
// skladajaca sie ze znakow "="
void PrintHorizontalLine(int length)
{
    int i;
    for (i = 0; i < length; i++)
        printf("=");
    printf("\n");
}

void zad4()
{
    cout << "ZADANIE 4" << endl;

    double minR, maxR;  // minimalny i maksymalny promien
    int rows;  // liczba wierszy

    cout << "Podaj minimalny promien: ";
    cin >> minR;
    cout << "Podaj maksymalny promien: ";
    cin >> maxR;
    cout << "Podaj liczbe wierszy: ";
    cin >> rows;
    cout << endl;

    if (minR > maxR || rows < 0 || minR <= 0 || maxR <= 0)
    {
        cout << "bledne dane" << endl;
        return;
    }

    // co ile beda sie zwiekszac wartosci promienia od minR do maxR
    double offset = (maxR - minR) / (rows - 1);

    int columnWidths[4];    // tablica zawierajaca szerokosci kolumn

    // tablica z naglowkami kolumn
    const char *headers[] = {"Lp.", "promien", "obwod kola", "pole kola"};

    // bufor
    char *buff = new char[BUFFSIZE];
    memset(buff, 0, BUFFSIZE);

    // obliczenie szerokosci pierwszej kolumny
    snprintf(buff, BUFFSIZE, "%d", rows);
    columnWidths[0] = strlen(buff) > strlen("Lp.") ? strlen(buff) : strlen("Lp.");
    memset(buff, 0, BUFFSIZE);

    // obliczenie szerokosci drugiej kolumny
    snprintf(buff, BUFFSIZE, "%.2f", maxR);
    columnWidths[1] = strlen(buff) > strlen("promien") ? strlen(buff) : strlen("promien");
    memset(buff, 0, BUFFSIZE);

    // obliczenie szerokosci trzeciej kolumny
    snprintf(buff, BUFFSIZE, "%.2f", CircleCircumference(maxR));
    columnWidths[2] = strlen(buff) > strlen("obwod kola") ? strlen(buff) : strlen("obwod kola");
    memset(buff, 0, BUFFSIZE);

    // obliczenie szerokosci czwartej kolumny
    snprintf(buff, BUFFSIZE, "%.2f", CircleArea(maxR));
    columnWidths[3] = strlen(buff) > strlen("pole kola") ? strlen(buff) : strlen("pole kola");

    delete [] buff;

    // obliczenie dlugosci jednego wiersza
    int rowLength = strlen("|  |  |  |  |") + columnWidths[0] + columnWidths[1];
    rowLength += columnWidths[2] + columnWidths[3];

    // wypisanie linii poziomej
    PrintHorizontalLine(rowLength);

    // wypisanie naglowkow tabeli
    printf(
        "| %*s | %*s | %*s | %*s |\n",
        columnWidths[0], headers[0],
        columnWidths[1], headers[1],
        columnWidths[2], headers[2],
        columnWidths[3], headers[3]
    );

    // wypisanie linii poziomej
    PrintHorizontalLine(rowLength);

    int i;
    double r = minR;

    // wypisanie kolejnych wierszy tabeli
    for (i = 1; i <= rows; i++)
    {
        printf(
                "| %*d | %*.2f | %*.2f | %*.2f |\n",
                columnWidths[0], i,
                columnWidths[1], r,
                columnWidths[2], CircleCircumference(r),
                columnWidths[3], CircleArea(r)
        );

        r += offset;
    }

    // wypisanie linii poziomej
    PrintHorizontalLine(rowLength);
}

int main()
{
    // obowiazkowy wydruk danych autora
    cout << "Author: " << AUTHOR << ' ' << GROUP << endl << endl;

    zad1(); // zadanie 1
    zad2(); // zadanie 2
    zad3(); // zadanie 3
    zad4(); // zadanie 4

    cout << "Type Enter to continue..." << endl;
    cin.ignore();
    cin.get();

    return 0;
}
