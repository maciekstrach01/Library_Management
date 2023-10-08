#include <iostream>
#include "Pracownik.h"
using namespace std;

Pracownik::Pracownik(const string& i, const string& n, double w, int s, const string& wy, const string& p)
    : imie(i), nazwisko(n), wynagrodzenie(w), stazPracy(s), wyksztalcenie(wy), pesel(p) {}

string Pracownik::getImie() const {
    return imie;
}

string Pracownik::getNazwisko() const {
    return nazwisko;
}

double Pracownik::getWynagrodzenie() const {
    return wynagrodzenie;
}

int Pracownik::getStazPracy() const {
    return stazPracy;
}

string Pracownik::getWyksztalcenie() const {
    return wyksztalcenie;
}

string Pracownik::getPesel() const {
    return pesel;
}

