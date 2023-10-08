#include "Ksiazka.h"
#include <iostream>

Ksiazka::Ksiazka(std::string t, std::string a, int r, std::string w, int ls)
    : tytul(t), autor(a), rok_wydania(r), wydawnictwo(w), liczba_stron(ls),
      wypozyczona(false), zakupiona(false), mozeBycWypozyczona(true), aktualnieWypozyczona(false) {}

void Ksiazka::wypozycz() {
    if (!wypozyczona && !zakupiona && mozeBycWypozyczona && !aktualnieWypozyczona) {
        wypozyczona = true;
        czas_wypozyczenia = std::chrono::system_clock::now();
        aktualnieWypozyczona = true;
    } else if (wypozyczona) {
        std::cout << "Ksiazka jest juz wypozyczona." << std::endl;
    } else if (zakupiona) {
        std::cout << "Ksiazka jest zakupiona i nie moze byc wypozyczona." << std::endl;
    } else if (aktualnieWypozyczona) {
        std::cout << "Ksiazka jest obecnie wypozyczona i nie moze byc zakupiona." << std::endl;
    }
}

void Ksiazka::oddaj() {
    wypozyczona = false;
    aktualnieWypozyczona = false;
}

bool Ksiazka::czyWypozyczona() const {
    return wypozyczona;
}

bool Ksiazka::czyZakupiona() const {
    return zakupiona;
}

bool Ksiazka::czyMoznaKupic() const {
    return !wypozyczona;
}

void Ksiazka::zakup() {
    if (!wypozyczona) {
        zakupiona = true;
        mozeBycWypozyczona = false;
    } else {
        std::cout << "Ksiazka jest wypozyczona i nie moze zostac zakupiona." << std::endl;
    }
}

std::string Ksiazka::getTytul() const {
    return tytul;
}

std::string Ksiazka::getAutor() const {
    return autor;
}

int Ksiazka::getRokWydania() const {
    return rok_wydania;
}

std::string Ksiazka::getWydawnictwo() const {
    return wydawnictwo;
}

int Ksiazka::getLiczbaStron() const {
    return liczba_stron;
}

std::chrono::seconds Ksiazka::czasDoOddania() const {
    auto teraz = std::chrono::system_clock::now();
    auto roznica = teraz - czas_wypozyczenia;
    auto limit = std::chrono::hours(24 * 14);  // 2 tygodnie
    if (roznica >= limit) {
        return std::chrono::seconds(0);
    } else {
        return std::chrono::duration_cast<std::chrono::seconds>(limit - roznica);
    }
}
