#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <random>
using namespace std;
//zmienne mapy
const int szerokosc= 35;
const int wysokosc= 20;
//zmienne polozenia 
int x, y, f_x,f_y, wynik;
int kierunek;
int snakeX[300], snakeY[300], dlugosc;
bool GameOver = false;//zmienna trwania
//generator liczb losowych
mt19937 generator(time(nullptr));
uniform_int_distribution <int > distribution(0, 1000);
void ClearScreen()
{
    //funkcja ktora czysci obraz bez migania 
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;   
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

//funkcja która zajmuje sie rysowaniem
void Rysuj()
{
    //rysunek gornej krawedzi
    for (int i = 0; i < szerokosc + 2; i++)
        cout << "#";
    cout << endl;
    //rysowanie srodka w podwojnej petli
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            //pierwszy element z lewej to kawalek sciany
            if (j == 0)
                cout << "#";
            if (i == y && j == x) {
                //glowa weza jest wyswietlana jako O
                cout << "O";
            }
            else if (i == f_y && j == f_x)
                //wylosowane kordy owocu mają wyswietlic procent
                cout << "%";
            else
            {
               
                bool z1 = false;
                //sprawdzamy czy na kordzie leży elemeny weza
                for (int k = 0; k < dlugosc; k++)
                {
                    if (snakeX[k] == j && snakeY[k] == i)
                    {
     
                        cout << "O";
                        z1 = true;
                    }
                }
                if (!z1)
                    cout << " ";
            }
            if (j == szerokosc - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < szerokosc + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Wynik : " << wynik << endl;
}
void Logika()
{
    //pobieranie z klawiatury znaku i zmiana kierunku oraz sprawdzenie czy z danego kierunku mozna wykonac inny
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            if (kierunek != 4)kierunek = 3;
            break;
        case 's':
            if (kierunek != 3)kierunek = 4;
            break;
        case 'a':
            if (kierunek != 2)kierunek = 1;
            break;
        case 'd':
            if (kierunek != 1)kierunek = 2;
            break;
        }
    }
    //tworzymy historie zmiany poruszenia sie weza
    int pX = snakeX[0];
    int pY = snakeY[0];
    int pX2, pY2;
    snakeX[0] = x;
    snakeY[0] = y;
    for (int i = 1; i < dlugosc; i++)
    {
        pX2 = snakeX[i];
        pY2 = snakeY[i];
        snakeX[i] = pX;
        snakeY[i] = pY;
        pX = pX2;
        pY = pY2;
    }
    //w zaleznosci od kierunku tak sie z zmienia polozenie glowy weza
    switch (kierunek)
    {
    case 1:
        x--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y--;
        break;
    case 4:
        y++;
        break;
    default:
        break;
    }
    //sprawdzanie czy wąż walnął w sciane
    if (x > szerokosc-1 || x < 0 || y > wysokosc-1 || y < 0)
        GameOver = true;
    for (int i = 0; i < dlugosc; i++)
        if (x==snakeX[i]  && y==snakeY[i] )
            GameOver = true;
    //sprawdzenie czy wąż zjadł owoc jesli tak zwieksza sie dlugosc oraz losowany jest nowy kord
    if (x == f_x && y == f_y)
    {
        wynik += 10;
        f_x = distribution(generator) % szerokosc;
        f_y = distribution(generator) % wysokosc;
        dlugosc++;
    }
}

int main()
{
    //poczatkowe ustawienia mapy
    x = szerokosc / 2;
    y = wysokosc / 2;
    f_x= distribution(generator) % szerokosc;
    f_y = distribution(generator) % wysokosc;
    //petla z gra ktora sie wykonuje do konca gry
    while (!GameOver)
    {
        Rysuj();
        ClearScreen();
        Logika();
        if (kierunek == 1 || kierunek == 2)Sleep(40);
        if (kierunek == 3 || kierunek == 4)Sleep(100);
    }
    system("cls");
    cout << "koniec gry przegrales!";
}