/*
 * Autor: Artur Kregiel
 * Grupa: WTP 15:15    (wtorek parzysty godz 15:15)
 * Temat: Laboratorium 4 - zadania 2, 3 i 4
 * Data: 22.12.2022
 */

#define AUTHOR "Artur Kregiel"  // autor
#define GROUP "(WTP 15:15)"    // grupa

#include <iostream>
#include <stdio.h>
#include <string.h>

// Zadanie 2

// rozmiar bufora tekstu
#define BUFSIZE 128

// Funkcja usuwajaca cyfry z ciagu znakow (cstring)
// przyjmuje lancuch, z ktorego ma usunac cyfry
// i zwraca liczbe usunietych cyfr
int removeDigits(char* str);

// Funkcja uruchamiajaca zadanie drugie
void zad2();

// Zadanie 3

// Funkcja usuwajaca komentarze z ciagu znakow (cstring)
// przyjmuje lancuch, z ktorego ma usunac cyfry
// i zwraca adres poczatku zmodyfikowanego lancucha
char* removeComments(char* str);

void zad3();

// Zadanie 4

// zdeklarowanie typu oznaczajacego bajt
typedef unsigned char byte_t;

// Funkcja sprawdzajaca jaka obowiazuje kolejnosc bajtow na urzadzeniu:
// little-endian albo big-endian
void checkEndianness();

// zmienne globalne
long longGlobal = 654321;
short shortGlobal = 321;
int intGlobal = 4321;
double doubleGlobal = 4321.198765;
char charGlobal = 'B';
float floatGlobal = 654.321;

// unie przechowuja dane w swoich polach
// pod tym samym adresem w pamieci
union
{
    int value;
    byte_t bytearray[sizeof(int)];
} intUnion;

union
{
    short value;
    byte_t bytearray[sizeof(short)];
} shortUnion;

union
{
    long value;
    byte_t bytearray[sizeof(long)];
} longUnion;

union
{
    float value;
    byte_t bytearray[sizeof(float)];
} floatUnion;

union
{
    double value;
    byte_t bytearray[sizeof(double)];
} doubleUnion;

void printGlobalVariablesMemoryInfo();

void printLocalVariablesMemoryInfo(int& intLocal, char& charLocal, float& floatLocal, short& shortLocal, long& longLocal, double& doubleLocal);

// Funkcja odpowiadajaca za wypisywanie informacji
// na temat pamieci: adresów i rozmiarow zmiennych
// lokalnych i globalnych
void zad4(int argc, char* argv[], char* envp[]);

/*****************************************************************/
/************************* Interfejs *****************************/
/*****************************************************************/

int main(int argc, char* argv[], char* envp[])
{
    // obowiazkowy wydruk danych autora
    std::cout << "Autor: " << AUTHOR << ' ' << GROUP << std::endl << std::endl;
    
    int choice;
    do
    {
        printf("\nMENU:\n\n");
        printf("\t1. Koniec\n");
        printf("\t2. Zadanie 2 - usuwanie cyfr\n");
        printf("\t3. Zadanie 3 - usuwanie komentarzy\n");
        printf("\t4. Zadanie 4 (dla ambitnych) - informacje o pamieci\n");
        printf("\nTwoj wybor: ");
        scanf("%d", &choice);
        getchar();  // pozbycie sie pozostawionego w STDIN znaku nowej linii
        printf("\n");

        switch (choice)
        {
        case 1:
            break;
        case 2:
            zad2();
            break;
        case 3:
            zad3();
            break;
        case 4:
            zad4(argc, argv, envp);
            break;
        default:
            printf("[!!] Bledna opcja (%d), tylko cyfry od 1 do 4!\n", choice);
            break;
        }
    } while (choice != 1);

    return 0;
}

/*****************************************************************/
/********************* Definicje funkcji *************************/
/*****************************************************************/

int removeDigits(char* str)
{
    int deletedDigits = 0;

    // skopiuj do bufora znaki ktore nie sa cyframi
    int idx = 0;    // miejsce w ktore nalezy wstawic znak niebedacy cyfra
    for (int i = 0; *(str + i) != '\0'; i++)
    {
        if ('0' > *(str + i) || *(str + i) > '9')
        {
            *(str + idx) = *(str + i);
            idx++;
        }
        else
        {
            deletedDigits++;
        }
    }

    str[idx] = '\0';

    return deletedDigits;
}

void zad2()
{
    char str[BUFSIZE] = { 0 };

    printf("Napisz cos: ");
    fgets(str, BUFSIZE, stdin);
    printf("Usuwanie cyfr... ");
    int n = removeDigits(str);
    printf("OK\n");
    printf("Usunieto %d cyfr\n", n);
    printf("zmieniony napis: %s\n", str);
}

// Zadanie 3

char* removeComments(char* str)
{
    bool isComment = false;
    int idx = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isComment)
        {
            if (str[i] == '*' && str[i + 1] == '/')
            {
                isComment = false;
                i++;
            }
        }
        else
        {
            if (str[i] == '/' && str[i + 1] == '/')
            {
                str[i] = '\0';
                break;
            }
            else if (str[i] == '/' && str[i + 1] == '*')
            {
                isComment = true;
            }
            else
            {
                str[idx] = str[i];
                idx++;
            }
        }
    }

    str[idx] = '\0';

    return str;
}

void zad3()
{
    //char str[] = "abcd/* 9w 0293//5 253*/ efghijk/* wwe94wt0 */ // ufoueb ouwbtiubgurbgur";
    char str[BUFSIZE] = { 0 };
    printf("Napisz cos: ");
    fgets(str, BUFSIZE, stdin);
    //printf("Oryginalny lancuch: %s\n", str);
    char* str2 = removeComments(str);
    printf("Zmodyfikowany lancuch: %s\n", str2);
}

// Zadanie 4

void checkEndianness()
{
    union
    {
        unsigned int number;
        byte_t bytearray[sizeof(int)];
    } endianChecker;

    endianChecker.number = 0x01020304;

    if (endianChecker.bytearray[0] == 1 && endianChecker.bytearray[1] == 2)
    {
        printf("Big-endian (najbardziej znaczacy bajt jako pierwszy)\n");
    }
    else if (endianChecker.bytearray[0] == 4 && endianChecker.bytearray[1] == 3)
    {
        printf("Little-endian (najmniej znaczacy bajt jako pierwszy)\n");
    }
}

void printGlobalVariablesMemoryInfo()
{
    printf("\n[+] Zmienne globalne:\n");

    printf("1. Zmienna longGlobal: Adres:%p, Wartosc:%ld (hex: %lx), Rozmiar:%u, Bajty: ", &longGlobal, longGlobal, longGlobal, sizeof(longGlobal));

    longUnion.value = longGlobal;
    for (int i = 0; i < sizeof(long); ++i)
        printf("0x%02X ", longUnion.bytearray[i]);
    printf("\n");

    printf("2. Zmienna shortLocal: Adres:%p, Wartosc:%d (hex: %x), Rozmiar: %u, Bajty: ", &shortGlobal, shortGlobal, shortGlobal, sizeof(shortGlobal));

    shortUnion.value = shortGlobal;
    for (int i = 0; i < sizeof(short); ++i)
        printf("0x%02X ", shortUnion.bytearray[i]);
    printf("\n");

    printf("3. Zmienna intGlobal: Adres:%p, Wartosc:%d (hex: %x), Rozmiar:%u, Bajty: ", &intGlobal, intGlobal, intGlobal, sizeof(intGlobal));

    intUnion.value = intGlobal;
    for (int i = 0; i < sizeof(int); ++i)
        printf("0x%02X ", intUnion.bytearray[i]);
    printf("\n");

    printf("4. Zmienna doubleglobal: Adres:%p, Wartosc:%g, Rozmiar:%u, Bajty: ", &doubleGlobal, doubleGlobal, sizeof(doubleGlobal));

    doubleUnion.value = doubleGlobal;
    for (int i = 0; i < sizeof(double); ++i)
        printf("0x%02X ", doubleUnion.bytearray[i]);
    printf("\n");

    printf("5. Zmienna charGlobal: Adres:%p, Watosc:%c (hex: %x), Rozmiar %u, Bajty: 0x%02X\n", &charGlobal, charGlobal, charGlobal, sizeof(charGlobal), charGlobal);

    printf("6. Zmienna floatGlobal: Adres:%p, Wartosc:%.2f, Rozmiar:%u, Bajty: ", &floatGlobal, floatGlobal, sizeof(floatGlobal));

    floatUnion.value = floatGlobal;
    for (int i = 0; i < sizeof(float); ++i)
        printf("0x%02X ", floatUnion.bytearray[i]);
    printf("\n");
}

void printLocalVariablesMemoryInfo(int& intLocal, char& charLocal, float& floatLocal, short& shortLocal, long& longLocal, double& doubleLocal)
{
    printf("[+] Zmienne lokalne:\n");

    printf("1. Zmienna intLocal: Adres:%p, Wartosc:%d (hex: %x), Rozmiar: %u, Bajty: ", &intLocal, intLocal, intLocal, sizeof(intLocal));

    intUnion.value = intLocal;
    for (int i = 0; i < sizeof(int); ++i)
        printf("0x%02X ", intUnion.bytearray[i]);
    printf("\n");

    printf("2. Zmienna charLocal: Adres:%p, Watosc:%c (hex: %x), Rozmiar: %u, Bajty: 0x%02X\n", &charLocal, charLocal, charLocal, sizeof(charLocal), charLocal);

    printf("3. Zmienna floatLocal: Adres:%p, Wartosc:%.2f, Rozmiar: %u, Bajty: ", &floatLocal, floatLocal, sizeof(floatLocal));

    floatUnion.value = floatLocal;
    for (int i = 0; i < sizeof(float); ++i)
        printf("0x%02X ", floatUnion.bytearray[i]);
    printf("\n");

    printf("4. Zmienna shortLocal: Adres:%p, Wartosc:%d (hex: %x), Rozmiar: %u, Bajty: ", &shortLocal, shortLocal, shortLocal, sizeof(shortLocal));

    shortUnion.value = shortLocal;
    for (int i = 0; i < sizeof(short); ++i)
        printf("0x%02X ", shortUnion.bytearray[i]);
    printf("\n");

    printf("5. Zmienna longLocal: Adres:%p, Wartosc:%ld (hex: %lx), Rozmiar:%u, Bajty: ", &longLocal, longLocal, longLocal, sizeof(longLocal));

    longUnion.value = longLocal;
    for (int i = 0; i < sizeof(long); ++i)
        printf("0x%02X ", longUnion.bytearray[i]);
    printf("\n");

    printf("6. Zmienna doubleLocal: Adres:%p, Wartosc:%g, Rozmiar:%u, Bajty: ", &doubleLocal, doubleLocal, sizeof(doubleLocal));

    doubleUnion.value = doubleLocal;
    for (int i = 0; i < sizeof(double); ++i)
        printf("0x%02X ", doubleUnion.bytearray[i]);
    printf("\n");
}

void zad4(int argc, char* argv[], char* envp[])
{
    // zmienne lokalne  (na stosie)
    int intLocal = 12345;
    char charLocal = 'A';
    float floatLocal = 123.456;
    short shortLocal = 123;
    long longLocal = 1234567;
    double doubleLocal = 1234.567891;

    // wydruki

    printf("[+] Kolejnosc bajtow: ");
    checkEndianness();
    printf("\n");
    
    //printf("&intLocal: %p\n", &intLocal);
    //printf("&intLocal + 1: %p\n", (char*)&intLocal + 1);
    //printf("*(&intLocal + 1): %x\n", *((char*)&intLocal + 1));
    //printf("&charLocal: %p\n", &charLocal);

    // Zmienne lokalne

    printLocalVariablesMemoryInfo(intLocal, charLocal, floatLocal, shortLocal, longLocal, doubleLocal);

    // Zmienne globalne

    printGlobalVariablesMemoryInfo();

    // modyfikowanie za pomoca wskaznikow

    int* intPointer;
    short* shortPointer;
    char* charPointer;
    float* floatPointer;
    long* longPointer;
    double* doublePointer;

    printf("\n[*] Modyfikowanie wartosci zmiennych lokalnych za pomoca wskaznikow...\n");

    intPointer = &intLocal;
    *intPointer += 10;

    shortPointer = &shortLocal;
    *shortPointer += 10;

    charPointer = &charLocal;
    *charPointer += 10;

    floatPointer = &floatLocal;
    *floatPointer += 10;

    longPointer = &longLocal;
    *longPointer += 10;

    doublePointer = &doubleLocal;;
    *doublePointer += 10;

    printf("\n[*] Modyfikowanie wartosci zmiennych globalnych za pomoca wskaznikow...\n\n");

    intPointer = &intGlobal;
    *intPointer += 10;

    shortPointer = &shortGlobal;
    *shortPointer += 10;

    charPointer = &charGlobal;
    *charPointer += 10;

    floatPointer = &floatGlobal;
    *floatPointer += 10;

    longPointer = &longGlobal;
    *longPointer += 10;

    doublePointer = &doubleGlobal;
    *doublePointer += 10;

    printLocalVariablesMemoryInfo(intLocal, charLocal, floatLocal, shortLocal, longLocal, doubleLocal);

    printGlobalVariablesMemoryInfo();

    // modyfikowanie za pomoca adresu z dodana liczba
    // zwiekszanie wszystkich bajtow kazdej zmiennej o 5

	printf("[*] Ponowne modyfikowanie zawartosci zmiennych...\n\n");
	
	// modyfikowanie zmiennych lokalnych
	
	for (int i = 0; (byte_t*)&doubleLocal + i < (byte_t*)&intLocal + sizeof(int); i++)
	{
		*((byte_t*)&doubleLocal + i) += 5;
	}
	
	// modyfikowanie zmiennych globalnych
	
	for (int i = 0; (byte_t*)&longGlobal + i < (byte_t*)&floatGlobal + sizeof(int); i++)
	{
		*((byte_t*)&longGlobal + i) += 5;
	}
	
	printLocalVariablesMemoryInfo(intLocal, charLocal, floatLocal, shortLocal, longLocal, doubleLocal);

    printGlobalVariablesMemoryInfo();

    char answer;
    printf("\nWypisac rowniez adresy zmiennych dynamicznych, srodowiskowych oraz argumentow wiersza polecen? (t/n) ");
    scanf("%c", &answer);

    if (answer != 't')
        return;

    // Zmienne dynamiczne (na stercie)

    printf("\n[+] Zmienne dynamiczne:\n\n");

    int* intArrayDynamic = new int[20];

    float* floatDynamic = new float;

    char* charArrayDynamic = new char[10];

    double* doubleDynamic = new double;

    long* longArrayDynamic = new long[15];

    printf("intArrayDynamic: Adres: %p\n", intArrayDynamic);
    printf("floatDynamic: Adres: %p\n", floatDynamic);
    printf("charArrayDynamic: Adres: %p\n", charArrayDynamic);
    printf("doubleDynamic: Adres: %p\n", doubleDynamic);
    printf("longArrayDynamic: Adres: %p\n", longArrayDynamic);

    delete[] intArrayDynamic;
    delete floatDynamic;
    delete[] charArrayDynamic;
    delete doubleDynamic;
    delete[] longArrayDynamic;

    // Argumenty wiersza polecen

    printf("\n[+] Argumenty wiersza polecen:\n\n");

    for (int i = 0; i < argc; i++)
    {
        printf("%d: Wartosc: %s, Adres: %p, Dlugosc: %u\n", i, argv[i], argv[i], strlen(argv[i]));
    }

    printf("\n[+] Zmienne srodowiskowe:\n\n");

    for (int i = 0; envp[i] != NULL; ++i)
    {
        printf("%d: Wartosc: %s, Adres: %p, Dlugosc: %u\n", i, envp[i], envp[i], strlen(envp[i]));
    }
}