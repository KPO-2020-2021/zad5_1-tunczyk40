
#include "Dron.hh"

Dron::Dron(int id, PzG::LaczeDoGNUPlota &Lacze, Wektor3D polozenie) : Lacze(Lacze)
{
    kat=0;
    this->id = id;
    oryginal.set_nazwa("../datasets/korpus" + std::to_string(id) + ".dat");

    for (int i = 0; i < 4; i++)
        org_wir[i].set_nazwa("../datasets/wirnik" + std::to_string(i) + std::to_string(id) + ".dat");

    Lacze.DodajNazwePliku(oryginal.get_nazwa().c_str(), PzG::RR_Ciagly, 2);
    for (int i = 0; i < 4; i++)
        Lacze.DodajNazwePliku(org_wir[i].get_nazwa().c_str(), PzG::RR_Ciagly, 2);
    kopia = oryginal;

    kopia.ruch(polozenie);
    for (int i = 0; i < 4; i++)
        kopia_wir[i] = org_wir[i];

    for (int i = 0; i < 4; i++)
        kopia_wir[i].ruch(oryginal[i * 2] + polozenie);

    this->droga = this->droga + polozenie;
}

/* Funkcja odpowiedzialna za unoszenie sie drona */

void Dron::wznoszenie(double droga)
{
    Wektor3D droga_2;
    droga_2[2] = droga;

    this->droga = this->droga + droga_2;
    kopia.translacja(obr);
    kopia.ruch(this->droga);
}

/* Funkcja odpowiedzialna za przesuwanie drona po scenie */

void Dron::ruch(double droga)
{
    Wektor3D droga_2;
    droga_2[0] = droga * cos(kat * M_PI / 180);
    droga_2[1] = droga * sin(kat * M_PI / 180);
    this->droga = this->droga + droga_2;
    kopia.translacja(obr);
    kopia.ruch(this->droga);
}

/*Funkcja odpowiedzialna za obrot drona o zadany kat w stopniach */

void Dron::obrot(double kat)
{
    this->kat += kat;
    Macierz3x3 nowa;
    obr = nowa * macierz_obrotu_z(this->kat);
    kopia.translacja(obr);
    kopia.ruch(this->droga);
}

/* Funkcja odpowiedzialna za obroty wirnikow */

void Dron::obroty_wirnikow()
{
    static int kat = 0;
    kat += 3;
    if (kat == 360)
        kat = 0;

    Macierz3x3 nowa,nowa2;
    nowa = nowa * macierz_obrotu_z(kat);
    for (int i = 0; i < 4; i++)
    {
        /* Rozroznienie kierunkow krecenia sie rotorow */

        if((i+1)%2==0)
        {
            nowa = nowa * macierz_obrotu_z(kat);
            kopia_wir[i].translacja(nowa);
        }
        else
        {
            nowa2 = nowa2 * macierz_obrotu_z(-kat);
            kopia_wir[i].translacja(nowa2);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        kopia_wir[i].ruch(kopia[i * 2]);
    }
}

/* Funkcja odpowiedzialna za zapisanie zmienionego polozenia drona */

void Dron::zapisz()
{
    kopia.zapisz();
    for (int i = 0; i < 4; i++)
        kopia_wir[i].zapisz();
}

/* Cale menu ze sterowaniem dronami */

void Dron::sterowanie()
{
    double droga;
    double kat;
    char opcja;

    zapisz();
    cout << "Menu:\n p - Przelot drona w kierunku w ktorym jest ustawiony\n o - Obrot drona o kat podany w stopniach\n m - Powrot do wyboru drona\n";
    cin >> opcja;
    switch (opcja)
    {
    case 'p':
        cout << "Podaj droge do przelotu:\n";
        cin >> droga;
        okresl_droge(droga);
        Lacze.DodajNazwePliku("../datasets/droga.dat", PzG::RR_Ciagly, 2);
        for (int i = 0; i < 100; i++)
        {
            kopia = oryginal;
            for (int j = 0; j < 4; j++)
            {
                kopia_wir[j] = org_wir[j];
            }
            wznoszenie(1);
            obroty_wirnikow();
            zapisz();
            Lacze.Rysuj();
            usleep(CZAS);
        }

        for (int i = 0; i < droga; i++)
        {
            kopia = oryginal;
            for (int j = 0; j < 4; j++)
            {
                kopia_wir[j] = org_wir[j];
            }
            ruch(1);
            obroty_wirnikow();
            zapisz();
            Lacze.Rysuj();
            usleep(CZAS);
        }

        for (int i = 0; i < 100; i++)
        {
            kopia = oryginal;
            for (int j = 0; j < 4; j++)
            {
                kopia_wir[j] = org_wir[j];
            }
            wznoszenie(-1);
            obroty_wirnikow();
            zapisz();
            Lacze.Rysuj();
            usleep(CZAS);
        }
    Lacze.UsunOstatniaNazwe();
        break;
    case 'o':
        cout << "Podaj kat o jaki dron ma sie obrocic:\n";
        cin >> kat;
        if (kat > 0)
        {
            for (int i = 0; i < kat; i++)
            {
                /* przypisanie kopi wartosci oryginalu aby na niej wykonac dzialanie */
                kopia = oryginal;
                for (int i = 0; i < 4; i++)
                {
                    kopia_wir[i] = org_wir[i];
                }
                obrot(1);
                obroty_wirnikow();
                zapisz();
                Lacze.Rysuj();
                usleep(CZAS);
            
            }
        }
        else
        {
            for (int i = 0; i > kat; i--)
            {
                kopia = oryginal;
                for (int i = 0; i < 4; i++)
                {
                    kopia_wir[i] = org_wir[i];
                }
                obrot(-1);
                obroty_wirnikow();
                zapisz();
                Lacze.Rysuj();
                usleep(CZAS);
            }
        }
   
        break;
    case 'm':
    {
        break;
    }
    default:
        break;
    }
}

void Dron::okresl_droge(double droga)
{
    Wektor3D nastepny = kopia.get_srodek();
    nastepny[2] = 0;
    droga_drona.push_back(nastepny);
    nastepny[2] = 100;
    droga_drona.push_back(nastepny);
    nastepny[0] += droga * cos(kat * M_PI / 180);
    nastepny[1] += droga * sin(kat * M_PI / 180);
    droga_drona.push_back(nastepny);
    nastepny[2] = 0;
    droga_drona.push_back(nastepny);

    std::fstream plik;

    plik.open("../datasets/droga.dat", std::ios::out);
    for (int i = 0; i < (int)droga_drona.size(); i++)
    {

        plik << droga_drona[i] << std::endl;
    }
    plik.close();
}