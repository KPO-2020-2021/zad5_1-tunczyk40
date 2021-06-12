#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <cmath>
using namespace std;

template <int Wymiar>
class Wektor
{
    static int wszystkie;
    static int aktualne;
    double wspolrzedne[Wymiar];

public:
    Wektor();
    Wektor(Wektor<Wymiar> &wek)
    {
        for (int i = 0; i < Wymiar; i++)
            wspolrzedne[i] = wek.wspolrzedne[i];

        aktualne++;
    }
    constexpr Wektor(const Wektor &other)
    {
        for (int i = 0; i < Wymiar; i++)
            wspolrzedne[i] = other.wspolrzedne[i];
        aktualne++;
    }
    Wektor &operator=(const Wektor &other)
    {
        for (int i = 0; i < Wymiar; i++)
            wspolrzedne[i] = other.wspolrzedne[i];
        return *this;
    }

    Wektor &operator=(const float &other)
    {
        for (int i = 0; i < Wymiar; i++)
            wspolrzedne[i] = other;
        return *this;
    }
    ~Wektor();
    Wektor(double wspolrzedne[Wymiar]);
    double operator[](int index) const;
    double &operator[](int index);
    Wektor<Wymiar> operator+(Wektor<Wymiar> &arg);
    Wektor<Wymiar> operator-(Wektor<Wymiar> &arg);
    void informacje();
};

template <int Wymiar>
int Wektor<Wymiar>::wszystkie = 0;

template <int Wymiar>
int Wektor<Wymiar>::aktualne = 0;

/* Podaje informacje o aktualnych i wszystkich wektorach */
template <int Wymiar>
void Wektor<Wymiar>::informacje()
{
    cout << "Aktualne wektory: " << aktualne << endl;
    cout << "Wszystkie wektory: " << wszystkie << endl;
}

template <int Wymiar>
Wektor<Wymiar>::Wektor()
{
    for (int i = 0; i < Wymiar; i++)
        wspolrzedne[i] = 0;
    aktualne++;
    wszystkie++;
}

template <int Wymiar>
Wektor<Wymiar>::Wektor(double wspolrzedne[Wymiar])
{
    for (int i = 0; i < Wymiar; i++)
        this->wspolrzedne[i] = wspolrzedne[i];
    aktualne++;
    wszystkie++;
}

template <int Wymiar>
Wektor<Wymiar>::~Wektor()
{
    aktualne--;
}

template <int Wymiar>
double Wektor<Wymiar>::operator[](int index) const
{
    if (index > Wymiar || index < 0)
    {
        std::cerr << "Indeks poza skala" << std::endl;
        exit(1);
    }
    return wspolrzedne[index];
}

template <int Wymiar>
double &Wektor<Wymiar>::operator[](int index)
{
    if (index > Wymiar || index < 0)
    {
        std::cerr << "Indeks poza skala" << std::endl;
        exit(1);
    }
    return wspolrzedne[index];
}

template <int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator+(Wektor<Wymiar> &arg)
{
    Wektor<Wymiar> Wynik;
    for (int i = 0; i < Wymiar; i++)
    {
        Wynik[i] = wspolrzedne[i] + arg[i];
    }
    return Wynik;
}

template <int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator-(Wektor<Wymiar> &arg)
{
    Wektor<Wymiar> Wynik;
    for (int i = 0; i < Wymiar; i++)
    {
        Wynik[i] = wspolrzedne[i] - arg[i];
    }
    return Wynik;
}

template <int Wymiar>
std::istream &operator>>(std::istream &Strm, Wektor<Wymiar> &Wek)
{
    for (int i = 0; i < Wymiar; i++)
    {
        Strm >> Wek[i];
    }
    return Strm;
    return Strm;
}

template <int Wymiar>
inline std::ostream &operator<<(std::ostream &Strm, const Wektor<Wymiar> &Wek)
{
    for (int i = 0; i < Wymiar; i++)
    {
        Strm << Wek[i] << " ";
    }
    return Strm;
}

#endif
