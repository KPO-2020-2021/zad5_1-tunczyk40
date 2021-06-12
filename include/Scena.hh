#ifndef SCENA_HH
#define SCENA_HH
#include <iostream>
#include <iomanip>
#include <fstream>
#include "wirnik.hh"
#include "lacze_do_gnuplota.hh"
#include "Dron.hh"
#include "Plaszczyzna.hh"

#define N 2

class Scena
{
 PzG::LaczeDoGNUPlota Lacze;
 Dron *tab[N];
 Plaszczyzna *dno;
 public:
 Scena();
 void rysuj();
 bool interfejs();
~Scena();
};



#endif
