#include "Bryla.hh"

Wektor3D &Bryla::operator[](int index)
{
    return wierz[index];
}
Wektor3D Bryla::operator[](int index) const
{
    return wierz[index];
}
/* Ustawia nazwe bryly */
void Bryla::set_nazwa(std::string nazwa)
{
    this->nazwa = nazwa;
}
/* Ustawia srodek bryly */
void Bryla::set_srodek(Wektor3D srodek)
{
    this->srodek = srodek;
}
/* Pozyskuje srodek bryly */
Wektor3D Bryla::get_srodek() const
{
    return srodek;
}
/* Pozyskuje nazwe bryly */
std::string Bryla::get_nazwa() const
{
    return nazwa;
}
/* Przesuwanie bryly */
void Bryla::ruch(Wektor3D przes)
{
    for (int i = 0; i < (int)wierz.size(); i++)
    {
        wierz[i] = wierz[i] + przes;
    }
    srodek = srodek + przes;
}

/* przesuniecie o wektor */
void Bryla::translacja(Macierz3x3 obr)
{
    for (int i = 0; i < (int)wierz.size(); i++)
    {
        wierz[i] = (obr * wierz[i]);
    }
    srodek=obr*srodek;
}

/* Zapisanie wymiarow bryly */
void Bryla::zapisz()
{
    std::fstream plik;
    double tab[] = {0, 0, (*wymiary)[2] / 2};
    Wektor3D ruch_sr(tab);

    plik.open(nazwa, std::ios::out);

    for (int i = 0; i < (int)wierz.size(); i += 2)
    {
        plik << srodek + ruch_sr << std::endl;
        for (int j = 0; j < 2; j++)
        {
            plik << wierz[j + i] << std::endl;
        }
        plik << srodek - ruch_sr << std::endl
             << std::endl;
    }

    plik << srodek + ruch_sr << std::endl;
    for (int j = 0; j < 2; j++)
    {
        plik << wierz[j] << std::endl;
    }
    plik << srodek - ruch_sr << std::endl
         << std::endl;
    plik.close();
}