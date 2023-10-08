#pragma once
#include <string>

class Pracownik {
public:
    Pracownik(const std::string& i, const std::string& n, double w, int s, const std::string& wy, const std::string& p);

    std::string getImie() const;
    std::string getNazwisko() const;
    double getWynagrodzenie() const;
    int getStazPracy() const;
    std::string getWyksztalcenie() const;
    std::string getPesel() const;


    std::string imie;
    std::string nazwisko;
    double wynagrodzenie;
    int stazPracy;
    std::string wyksztalcenie;
    std::string pesel;
};



