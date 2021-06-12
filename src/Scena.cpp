#include "Scena.hh"


 Scena::Scena()
 {

      Lacze.ZmienTrybRys(PzG::TR_3D);

       Lacze.UstawZakresY(-300, 300);
       Lacze.UstawZakresX(-300, 300);
       Lacze.UstawZakresZ(-300, 300);

       double tab_wym[3]={600,600,0};
       Wektor3D wym_dna(tab_wym);
       dno=new Plaszczyzna(wym_dna,20);
       Lacze.DodajNazwePliku(dno->get_nazwa().c_str(), PzG::RR_Ciagly, 2);
       dno->zapisz();

       for(int i=0;i<N; i++)
       {
        double polozenie[3]={(double)(rand()%440-220),(double)(rand()%440-220),25};
        tab[i]=new Dron(i,Lacze,Wektor3D(polozenie));
        tab[i]->zapisz();
       }

       Lacze.Rysuj();
 }
 void  Scena::rysuj()
 {
     
   Lacze.Rysuj();
 }
 /* Funkcja wyboru drona a nastepnie przejscie do funkcji sterowania */
 bool  Scena::interfejs()
 {
    cout<<"Wybierz drona do sterowania 0 albo 1 lub wpisz 2 aby zakonczyc dzialanie programu:"<<endl;
    int numer;
    cin>>numer;
    if(numer<N)
    {
        tab[numer]->sterowanie();
    }
    else
    {
        return false;
    }
  return true;
 }

 Scena::~Scena()
 {
  delete dno;
  for(int i=0; i<N; i++)
  {
    delete tab[i];
  }
 }