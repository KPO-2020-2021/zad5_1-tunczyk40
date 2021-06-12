#ifndef DRON_HH
#define DRON_HH

#include "Prostopadloscian.hh"
#include "wirnik.hh"
#include "lacze_do_gnuplota.hh"
#include <unistd.h> // biblioteka dla usleep
#define CZAS 20000

class Dron
{
    std::vector<Wektor3D> droga_drona;
    PzG::LaczeDoGNUPlota &Lacze;
    Prostopadloscian oryginal;
    Prostopadloscian kopia;
    wirnik org_wir[4];
    wirnik kopia_wir[4];
    Macierz3x3 obr;
    Wektor3D droga;
    double kat;
    int id; 
public:

  
  Dron(int id,PzG::LaczeDoGNUPlota &Lacze,Wektor3D polozenie);
  void wznoszenie(double droga);
  void ruch(double droga);
  void obrot(double kat); // kat podajemy w stopniach
  void obroty_wirnikow(); // kat podajemy w stopniach
  void zapisz();
  void sterowanie();
  void okresl_droge(double droga);
};

#endif
