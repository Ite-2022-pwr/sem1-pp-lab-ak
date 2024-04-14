/*
 * Autor: Artur Kręgiel
 * Grupa: WT/P 15:15    (wtorek parzysty godz 15:15)
 * Temat: Laboratorium 0 - ZADANIA DO WYKONANIA
 * Data: 4.10.2022
 */

#define AUTHOR "Artur Kręgiel"
#define GROUP "(WT/P 15:15)"

#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

// ---> ZADANIE 1 <--- //

struct BusinessCard
{
    string FirstName;
    string LastName;
    string Address;
    string PhoneNumber;
    string Email;
};

// a)

void Zad1a()
{
    BusinessCard myCard = {
            "Artur",
            "Kręgiel",
            "Wittiga 6",
            "299-792-458",
            "user@website.pl"
    };

    cout << myCard.FirstName << " " << myCard.LastName << endl;
    cout << "Adres: " << myCard.Address << endl;
    cout << "Nr telefonu: " << myCard.PhoneNumber << endl;
    cout << "e-mail: " << myCard.Email << endl;

}

void Zad1b()
{
    BusinessCard otherCard = {
            "Jan",
            "Kowalski",
            "Wittiga 6",
            "299-792-458",
            "user@website.pl"
    };

    printf("%s %s\n", otherCard.FirstName.c_str(), otherCard.LastName.c_str());
    printf("Adres: %s\n", otherCard.Address.c_str());
    printf("Nr telefonu: %s\n", otherCard.PhoneNumber.c_str());
    printf("e-mail: %s\n", otherCard.Email.c_str());

}

// ---> ZADANIE 2 <--- //

void Zad2()
{
    int a, b, c;
    cout << "Podaj 3 liczby calkowite (a b c): ";
    cin >> a >> b >> c;

    cout << "Suma: " << a + b + c << endl;
    cout << "Iloczyn: " << a * b * c << endl;

    float avg = (a + b + c) / 3.0;
    cout << "Srednia: " << avg << endl;
}

// ---> ZADANIE 3 <--- //

void Zad3()
{
    double r;
    cout << "Podaj promien kola: ";
    cin >> r;

    cout << "Obwod: " << 2 * r * M_PI << endl;
    cout << "Pole: " << M_PI * r * r << endl;
}

// ---> MAIN <--- //

int main() {
    cout << "Autor: " << AUTHOR << " " << GROUP << endl;
    cout << "Zadanie 1" << endl;
    cout << "a)" << endl;
    Zad1a();
    cout << "b)" << endl;
    Zad1b();

    cout << "Zadanie 2" << endl;
    Zad2();

    cout << "Zadanie 3" << endl;
    Zad3();

    cout << endl;
    cout << "Type Enter to continue...";
    cin.ignore(100, '\n');
    cin.get();
    return 0;
}
