/*
 * Autor: Artur Kregiel
 * Grupa: WTP 15:15    (wtorek parzysty godz 15:15)
 * Temat: Laboratorium 4 - zadanie 1b
 * Data: 14.12.2022
 */

#define AUTHOR "Artur Kregiel"  // autor
#define GROUP "(WTP 15:15)"    // grupa

#include <iostream>

/*****************************************************************/
/********************* Prototypy funkcji *************************/
/*****************************************************************/

 // Reprezentacja liczby rozwiazan rownania
enum EquationSolutionsNumber
{
    None,        // rownanie jest sprzeczne (0)
    One,        // jedno rozwiazanie (1)
    Infinity   // nieskonczenie wiele rozwiazan (2)
};


// Funkcja wczytujaca wspolczynniki rownania
// ax + by = c
void CzytajRownanie(float* a, float* b, float* c);


// Funkcja wypisujaca rozwiazanie ukladu rownan
void WypiszRozwiazanie(EquationSolutionsNumber N, float x, float y);

/*
    Funkcja obliczajaca wyznacznik macierzy 2x2:

    | p1    p2 |
    | p3    p4 |

*/
float ObliczWyznacznik(float p1, float p2, float p3, float p4);

// Funkcja obliczajaca rozwiazanie ukladu rownan
EquationSolutionsNumber ObliczRozwiazanie(float a1, float b1, float c1,
    float a2, float b2, float c2, float* x, float* y);

/*****************************************************************/
/************************* Interfejs *****************************/
/*****************************************************************/

int main()
{
    // obowiazkowy wydruk danych autora
    std::cout << "Autor: " << AUTHOR << ' ' << GROUP << std::endl << std::endl;

    float a1, b1, c1;           // wspolczynniki pierwszego rownania
    float a2, b2, c2;           // wspolczynniki drugiego rownania
    float x, y;                 // rozwiazania rownania
    EquationSolutionsNumber N;  // liczba rozwiazan rownania

    CzytajRownanie(&a1, &b1, &c1);
    CzytajRownanie(&a2, &b2, &c2);

    N = ObliczRozwiazanie(a1, b1, c1, a2, b2, c2, &x, &y);

    WypiszRozwiazanie(N, x, y);

    std::cin.ignore();
    std::cin.get();

    return 0;
}

/*****************************************************************/
/********************* Definicje funkcji *************************/
/*****************************************************************/

void CzytajRownanie(float* a, float* b, float* c)
{
    std::cout << "Podaj wspolczynniki rownania a*x + b1*y = c:" << std::endl;
    std::cout << "a = ";
    std::cin >> *a;
    std::cout << "b = ";
    std::cin >> *b;
    std::cout << "c = ";
    std::cin >> *c;
}

void WypiszRozwiazanie(EquationSolutionsNumber N, float x, float y)
{
    switch (N)
    {
    case None:
        std::cout << "Uklad rownan jest sprzeczny i nie ma rozwiazan" << std::endl;
        break;
    case One:
        std::cout << "x = " << x << ", y = " << y << std::endl;
        break;
    case Infinity:
        std::cout << "Uklad rownan ma nieskonczenie wiele rozwiazan" << std::endl;
        break;
    default:
        break;
    }
}

float ObliczWyznacznik(float p1, float p2, float p3, float p4)
{
    return p1 * p4 - p2 * p3;
}

EquationSolutionsNumber ObliczRozwiazanie(float a1, float b1, float c1,
    float a2, float b2, float c2, float* x, float* y)
{
    float W, Wx, Wy;    // wyznaczniki

    W = ObliczWyznacznik(a1, b1, a2, b2);
    Wx = ObliczWyznacznik(c1, b1, c2, b2);
    Wy = ObliczWyznacznik(a1, c1, a2, c2);

    if (W)  // uklad oznaczony
    {
        *x = Wx / W;
        *y = Wy / W;
        return One;
    }
    else if (Wx || Wy)  // uklad sprzeczny
    {
        return None;
    }
    else if (!Wx && !Wy)    // uklad nieoznaczony
    {
        return Infinity;
    }
}
