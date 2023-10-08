#pragma once
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;


class Ksiazka {

public:
    string tytul;
    string autor;
    int rok_wydania;
    string wydawnictwo;
    int liczba_stron;
    bool wypozyczona;
    bool zakupiona;
    bool mozeBycWypozyczona;
    bool aktualnieWypozyczona;
    chrono::system_clock::time_point czas_wypozyczenia;


    Ksiazka(std::string t, std::string a, int r, std::string w, int ls);

    void wypozycz();
    void oddaj();
    bool czyWypozyczona() const;
    bool czyZakupiona() const;
    bool czyMoznaKupic() const;
    void zakup();
    string getTytul() const;
    string getAutor() const;
    int getRokWydania() const;
    string getWydawnictwo() const;
    int getLiczbaStron() const;
    chrono::seconds czasDoOddania() const;
};

