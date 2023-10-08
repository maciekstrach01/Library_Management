#include <iostream>
#include <fstream>
#include <algorithm>
#include "Biblioteka.h"
using namespace std::chrono;
using namespace std;

void Biblioteka::dodajKsiazke(const Ksiazka& k) {
    ksiazki.push_back(k);
}

void Biblioteka::dodajPracownika(const Pracownik& pracownik) {
    pracownicy.push_back(pracownik);
}

void Biblioteka::zwolnijPracownika(const std::string& nazwisko, const std::string& pesel) {
    auto it = std::remove_if(pracownicy.begin(), pracownicy.end(),
                             [&](const Pracownik& p) {
                                 return p.getNazwisko() == nazwisko && p.getPesel() == pesel;
                             });

    if (it != pracownicy.end()) {
        pracownicy.erase(it, pracownicy.end());
        std::cout << "Zwolniono pracownika o nazwisku " << nazwisko << " i PESEL-u " << pesel << "\n";
    } else {
        std::cout << "Nie znaleziono pracownika o nazwisku " << nazwisko << " i PESEL-u " << pesel << "\n";
    }
}

void Biblioteka::wyswietlObecnychPracownikow() const {
    for (const auto& p : pracownicy) {
        std::cout << "Imie: " << p.getImie() << ", Nazwisko: " << p.getNazwisko()
                  << ", Wynagrodzenie: " << p.getWynagrodzenie()
                  << ", Staz pracy: " << p.getStazPracy() << ", Wyksztalcenie: " << p.getWyksztalcenie() << ", PESEL: " << p.getPesel() << std::endl;
    }
}

Ksiazka* Biblioteka::znajdzKsiazkePoAutorze(const std::string& autor) {
    for (auto& k : ksiazki) {
        if (k.getAutor() == autor) {
            return &k;
        }
    }
    return nullptr;
}

Ksiazka* Biblioteka::znajdzKsiazke(const std::string& tytul) {
    for (auto& k : ksiazki) {
        if (k.getTytul() == tytul) {
            return &k;
        }
    }
    return nullptr;
}

void Biblioteka::wyswietlKsiazki() const {
    for (const auto& k : ksiazki) {
        std::cout << "Tytul: " << k.getTytul() << ", Autor: " << k.getAutor()
                  << ", Rok wydania: " << k.getRokWydania() << ", Wydawnictwo: "
                  << k.getWydawnictwo() << ", Liczba stron: " << k.getLiczbaStron()
                  << ", Wypozyczona: " << (k.czyWypozyczona() ? "Tak" : "Nie") << "\n";
    }
}

void Biblioteka::zapiszDoPliku(const std::string& nazwaPliku) const {
    std::ofstream plik(nazwaPliku);
    if (!plik) {
        throw std::runtime_error("Nie moge otworzyc pliku do zapisu");
    }

    for (const auto& k : ksiazki) {
        plik << k.getTytul() << ";" << k.getAutor() << ";" << k.getRokWydania()
             << ";" << k.getWydawnictwo() << ";" << k.getLiczbaStron()
             << ";" << k.czyWypozyczona() << "\n";
    }
}

void Biblioteka::wczytajZPliku(const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);
    if (!plik) {
        throw std::runtime_error("Nie moge otworzyc pliku do odczytu");
    }

    ksiazki.clear();
    std::string linia;
    while (std::getline(plik, linia)) {
        auto separator = linia.find(';');
        std::string tytul = linia.substr(0, separator);

        linia = linia.substr(separator + 1);
        separator = linia.find(';');
        std::string autor = linia.substr(0, separator);

        linia = linia.substr(separator + 1);
        separator = linia.find(';');
        int rok_wydania = std::stoi(linia.substr(0, separator));

        linia = linia.substr(separator + 1);
        separator = linia.find(';');
        std::string wydawnictwo = linia.substr(0, separator);

        linia = linia.substr(separator + 1);
        separator = linia.find(';');
        int liczba_stron = std::stoi(linia.substr(0, separator));

        linia = linia.substr(separator + 1);
        bool wypozyczona = std::stoi(linia);

        ksiazki.push_back(Ksiazka(tytul, autor, rok_wydania, wydawnictwo, liczba_stron));
        if (wypozyczona) {
            ksiazki.back().wypozycz();
        }
    }
}

void Biblioteka::usunKsiazke(const std::string& tytul) {
    auto it = std::remove_if(ksiazki.begin(), ksiazki.end(),
                             [&](const Ksiazka& k) {
                                 return k.getTytul() == tytul;
                             });

    if (it != ksiazki.end()) {
        ksiazki.erase(it, ksiazki.end());
        //std::cout << "Usunieto ksiazke\n";
    } else {
        std::cout << "Nie znaleziono ksiazki\n";
    }
}

void Biblioteka::oddajKsiazke(const std::string& tytul) {
    for (auto& k : ksiazki) {
        if (k.getTytul() == tytul) {
            if (!k.czyWypozyczona()) {
                std::cout << "Ksiazka nie jest wypozyczona\n";
            } else {
                k.oddaj();
                std::cout << "Oddano ksiazke\n";
            }
            return;
        }
    }
    std::cout << "Nie znaleziono ksiazki\n";
}

void Biblioteka::zakupKsiazke(const std::string& tytul) {
    for (auto& k : ksiazki) {
        if (k.getTytul() == tytul) {
            k.zakup();
            zakupioneKsiazki.push_back(&k);
            //std::cout << "Zakupiono ksiazke\n";
            return;
        }
    }
    std::cout << "Nie znaleziono ksiazki\n";
}

void Biblioteka::wyswietlZakupioneKsiazki() const {
    for (const auto* k : zakupioneKsiazki) {
        std::cout << "Tytul: " << k->getTytul() << ", Autor: " << k->getAutor()
                  << ", Rok wydania: " << k->getRokWydania() << ", Wydawnictwo: "
                  << k->getWydawnictwo() << ", Liczba stron: " << k->getLiczbaStron() << "\n";
    }
}

/*
void Biblioteka::wyswietlWypozyczoneKsiazki() const {
    for (const auto& k : biblioteka.ksiazki) {
        if (k.czyWypozyczona()) {
            auto pozostaly_czas = k.czasDoOddania();
            auto pozostaly_czas_sec = chrono::duration_cast<chrono::seconds>(pozostaly_czas).count();
            auto godziny = pozostaly_czas_sec / 3600;
            auto minuty = (pozostaly_czas_sec % 3600) / 60;
            auto sekundy = pozostaly_czas_sec % 60;
            cout << "Tytul: " << k.getTytul() << ", Autor: " << k.getAutor()
                << ", Rok wydania: " << k.getRokWydania() << ", Wydawnictwo: "
                << k.getWydawnictwo() << ", Liczba stron: " << k.getLiczbgaStron()
                << ", Wypozyczona: Tak, Pozostaly czas: "
                << godziny << "h " << minuty << "m " << sekundy << "s\n";
        }
    }
}
*/

void Biblioteka::wyswietlWypozyczoneKsiazki() const {
    for (const auto& k : ksiazki) {
        if (k.czyWypozyczona()) {
            auto pozostaly_czas = k.czasDoOddania();
            auto pozostaly_czas_sec = chrono::duration_cast<chrono::seconds>(pozostaly_czas).count();
            auto godziny = pozostaly_czas_sec / 3600;
            auto minuty = (pozostaly_czas_sec % 3600) / 60;
            auto sekundy = pozostaly_czas_sec % 60;
            cout << "Tytul: " << k.getTytul() << ", Autor: " << k.getAutor()
                << ", Rok wydania: " << k.getRokWydania() << ", Wydawnictwo: "
                << k.getWydawnictwo() << ", Liczba stron: " << k.getLiczbaStron()
                << ", Wypozyczona: Tak, Pozostaly czas: "
                << godziny << "h " << minuty << "m " << sekundy << "s\n";
        }
    }

}