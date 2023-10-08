#pragma once
#include <vector>
#include "Ksiazka.h"
#include "Pracownik.h"
using namespace std;

class Biblioteka {

    public:
    
    vector<Ksiazka> ksiazki;
    vector<Ksiazka*> zakupioneKsiazki;
    vector<Pracownik> pracownicy;
    
    void dodajKsiazke(const Ksiazka& k);
    void dodajPracownika(const Pracownik& pracownik);
    void zwolnijPracownika(const std::string& nazwisko, const std::string& pesel);
    void wyswietlObecnychPracownikow() const;
    Ksiazka* znajdzKsiazkePoAutorze(const std::string& autor);
    Ksiazka* znajdzKsiazke(const std::string& tytul);
    void wyswietlKsiazki() const;
    void zapiszDoPliku(const std::string& nazwaPliku) const;
    void wczytajZPliku(const std::string& nazwaPliku);
    void usunKsiazke(const std::string& tytul);
    void oddajKsiazke(const std::string& tytul);
    void zakupKsiazke(const std::string& tytul);
    void wyswietlWypozyczoneKsiazki() const;
    void wyswietlZakupioneKsiazki() const;
    


    
};


