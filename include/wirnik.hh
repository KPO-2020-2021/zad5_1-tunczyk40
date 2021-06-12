#ifndef WIRNIK_HH
#define WIRNIK_HH

#include "Bryla.hh"

class wirnik : public Bryla
{
    public:
    wirnik(Wektor3D srodek=Wektor3D(),double z=10,double promien=15,std::string nazwa = "../datasets/wirnik.dat" );
     ~wirnik(){delete wymiary;}
};




#endif
