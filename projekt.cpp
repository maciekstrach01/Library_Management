#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <chrono>

using namespace std::chrono;
using namespace std;

enum class TypUzytkownika {
    Wylogowany,
    Dyrektor,
    Pracownik,
    KlientPremium,
    Klient
};

TypUzytkownika wyborTypuUzytkownika() {
    int wybor;
    cout << "Wybierz typ uzytkownika:\n1. Dyrektor\n2. Pracownik\n3. Klient Premium\n4. Klient\n0. Wyjscie\n";
    cin >> wybor;

    switch (wybor) {
        case 1:
            return TypUzytkownika::Dyrektor;
        case 2:
            return TypUzytkownika::Pracownik;
        case 3:
            return TypUzytkownika::KlientPremium;
        case 4:
            return TypUzytkownika::Klient;
        case 0:
            exit(0); 
        default:
            throw runtime_error("Nieznany typ uzytkownika");
    }
}

class Ksiazka {
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

public:
    Ksiazka(string t, string a, int r, string w, int ls)
        : tytul(t), autor(a), rok_wydania(r), wydawnictwo(w), liczba_stron(ls),
          wypozyczona(false), zakupiona(false), mozeBycWypozyczona(true),aktualnieWypozyczona(false) {}

    void wypozycz() {
        if (!wypozyczona && !zakupiona && mozeBycWypozyczona && !aktualnieWypozyczona) {
            wypozyczona = true;
            czas_wypozyczenia = chrono::system_clock::now();
            aktualnieWypozyczona = true; 
        } else if (wypozyczona) {
            cout << "Ksiazka jest juz wypozyczona." << endl;
        } else if (zakupiona) {
            cout << "Ksiazka jest zakupiona i nie moze byc wypozyczona." << endl;
        } else if (aktualnieWypozyczona) { 
            cout << "Ksiazka jest obecnie wypozyczona i nie moze byc zakupiona." << endl;
        }
    }

      void oddaj() {
        wypozyczona = false;
        aktualnieWypozyczona = false; 
    }

    bool czyWypozyczona() const {
        return wypozyczona;
    }

    bool czyZakupiona() const {
    return zakupiona;
    }

    bool czyMoznaKupic() const {
        return !wypozyczona;
    }

   void zakup() {
        if (!wypozyczona) {
            zakupiona = true;
            mozeBycWypozyczona = false;
        } else {
            cout << "Ksiazka jest wypozyczona i nie moze zostac zakupiona." << endl;
        }
    }

    string getTytul() const {
        return tytul;
    }

    string getAutor() const {
        return autor;
    }

    int getRokWydania() const {
        return rok_wydania;
    }

    string getWydawnictwo() const {
        return wydawnictwo;
    }

    int getLiczbaStron() const {
        return liczba_stron;
    }

    chrono::seconds czasDoOddania() const {
        auto teraz = chrono::system_clock::now();
        auto roznica = teraz - czas_wypozyczenia;
        auto limit = chrono::hours(24 * 14);  // 2 tygodnie
        if (roznica >= limit) {
            return chrono::seconds(0);
        }
        else {
            return chrono::duration_cast<chrono::seconds>(limit - roznica);
        }
    }
};


class Pracownik {
    string imie;
    string nazwisko;
    double wynagrodzenie;
    int stazPracy;
    string wyksztalcenie;
    string pesel;

public:
    Pracownik(const string& i, const string& n, double w, int s, const string& wy,const string& p)
        : imie(i), nazwisko(n), wynagrodzenie(w), stazPracy(s), wyksztalcenie(wy), pesel(p) {}


    string getImie() const {
        return imie;
    }

    string getNazwisko() const {
        return nazwisko;
    }

    double getWynagrodzenie() const {
        return wynagrodzenie;
    }

    int getStazPracy() const {
        return stazPracy;
    }

    string getWyksztalcenie() const {
        return wyksztalcenie;
    }

    string getPesel() const {
    return pesel;
    }
};




class Biblioteka {
    vector<Ksiazka> ksiazki;
    vector<Ksiazka*> zakupioneKsiazki;
    vector<Pracownik> pracownicy;

public:
    void dodajKsiazke(const Ksiazka& k) {
        ksiazki.push_back(k);
    }

void dodajPracownika(const Pracownik& pracownik) {
    pracownicy.push_back(pracownik); 
}


void zwolnijPracownika(const string& nazwisko, const string& pesel) {
    bool pracownikZwolniony = false;
    for (auto it = pracownicy.begin(); it != pracownicy.end(); ++it) {
        if (it->getNazwisko() == nazwisko && it->getPesel() == pesel) {
            pracownicy.erase(it);
            cout << "Zwolniono pracownika o nazwisku " << nazwisko << " i PESEL-u " << pesel << "\n";
            pracownikZwolniony = true;
            break;
        }
    }

    if (!pracownikZwolniony) {
        cout << "Nie znaleziono pracownika o nazwisku " << nazwisko << " i PESEL-u " << pesel << "\n";
    }
}


    void wyswietlObecnychPracownikow() const {
        for (const auto& p : pracownicy) {
            cout << "Imie: " << p.getImie() << ", Nazwisko: " << p.getNazwisko()
                << ", Wynagrodzenie: " << p.getWynagrodzenie()
                << ", Staz pracy: " << p.getStazPracy() << ", Wyksztalcenie: " << p.getWyksztalcenie() << ", PESEL: " << p.getPesel() << endl;
        }
    }


    Ksiazka* znajdzKsiazkePoAutorze(const string& autor) {
        for (auto& k : ksiazki) {
            if (k.getAutor() == autor) {
                return &k;
            }
        }
        return nullptr;
    }

    Ksiazka* znajdzKsiazke(const string& tytul) {
        for (auto& k : ksiazki) {
            if (k.getTytul() == tytul) {
                return &k;
            }
        }
        return nullptr;
    }

    void wyswietlKsiazki() const {
        for (const auto& k : ksiazki) {
            cout << "Tytul: " << k.getTytul() << ", Autor: " << k.getAutor()
                 << ", Rok wydania: " << k.getRokWydania() << ", Wydawnictwo: "
                 << k.getWydawnictwo() << ", Liczba stron: " << k.getLiczbaStron()
                 << ", Wypozyczona: " << (k.czyWypozyczona() ? "Tak" : "Nie") << "\n";
        }
    }

    void zapiszDoPliku(const string& nazwaPliku) const {
        ofstream plik(nazwaPliku);
        if (!plik) {
            throw runtime_error("Nie moge otworzyc pliku do zapisu");
        }

        for (const auto& k : ksiazki) {
            plik << k.getTytul() << ";" << k.getAutor() << ";" << k.getRokWydania()
                 << ";" << k.getWydawnictwo() << ";" << k.getLiczbaStron()
                 << ";" << k.czyWypozyczona() << "\n";
        }
    }

    void wczytajZPliku(const string& nazwaPliku) {
        ifstream plik(nazwaPliku);
        if (!plik) {
            throw runtime_error("Nie moge otworzyc pliku do odczytu");
        }

        ksiazki.clear();
        string linia;
        while (getline(plik, linia)) {
            auto separator = linia.find(';');
            string tytul = linia.substr(0, separator);

            linia = linia.substr(separator + 1);
            separator = linia.find(';');
            string autor = linia.substr(0, separator);

            linia = linia.substr(separator + 1);
            separator = linia.find(';');
            int rok_wydania = stoi(linia.substr(0, separator));

            linia = linia.substr(separator + 1);
            separator = linia.find(';');
            string wydawnictwo = linia.substr(0, separator);

            linia = linia.substr(separator + 1);
            separator = linia.find(';');
            int liczba_stron = stoi(linia.substr(0, separator));

            linia = linia.substr(separator + 1);
            bool wypozyczona = stoi(linia);

            ksiazki.push_back(Ksiazka(tytul, autor, rok_wydania, wydawnictwo, liczba_stron));
            if (wypozyczona) {
                ksiazki.back().wypozycz();
            }
        }
    }

    void usunKsiazke(const string& tytul) {
        for (auto it = ksiazki.begin(); it != ksiazki.end(); ++it) {
            if (it->getTytul() == tytul) {
                ksiazki.erase(it);
                cout << "Usunieto ksiazke\n";
                return;
            }
        }
        cout << "Nie znaleziono ksiazki\n";
    }

    void oddajKsiazke(const string& tytul) {
        for (auto& k : ksiazki) {
            if (k.getTytul() == tytul) {
                if (!k.czyWypozyczona()) {
                    cout << "Ksiazka nie jest wypozyczona\n";
                }
                else {
                    k.oddaj();
                    cout << "Oddano ksiazke\n";
                }
                return;
            }
        }
        cout << "Nie znaleziono ksiazki\n";
    }

    void zakupKsiazke(const string& tytul) {
        for (auto& k : ksiazki) {
            if (k.getTytul() == tytul) {
                k.zakup();
                zakupioneKsiazki.push_back(&k); 
                cout << "Zakupiono ksiazke\n";
                return;
            }
        }
        cout << "Nie znaleziono ksiazki\n";
    }

    void wyswietlWypozyczoneKsiazki() const {
        for (const auto& k : ksiazki) {
            if (k.czyWypozyczona()) {
                auto pozostaly_czas = k.czasDoOddania();
                auto godziny = chrono::duration_cast<chrono::hours>(pozostaly_czas);
                pozostaly_czas -= godziny;
                auto minuty = chrono::duration_cast<chrono::minutes>(pozostaly_czas);
                pozostaly_czas -= minuty;
                auto sekundy = chrono::duration_cast<chrono::seconds>(pozostaly_czas);
                cout << "Tytul: " << k.getTytul() << ", Autor: " << k.getAutor()
                    << ", Rok wydania: " << k.getRokWydania() << ", Wydawnictwo: "
                    << k.getWydawnictwo() << ", Liczba stron: " << k.getLiczbaStron()
                    << ", Wypozyczona: Tak, Pozostaly czas: "
                    << godziny.count() << "h " << minuty.count() << "m " << sekundy.count() << "s\n";
            }
        }
    }

    void wyswietlZakupioneKsiazki() const {
        for (const auto& k : zakupioneKsiazki) {
            cout << "Tytul: " << k->getTytul() << ", Autor: " << k->getAutor()
                 << ", Rok wydania: " << k->getRokWydania() << ", Wydawnictwo: "
                 << k->getWydawnictwo() << ", Liczba stron: " << k->getLiczbaStron() << "\n";
        }
    }

};

int main() {
    TypUzytkownika typUzytkownika = TypUzytkownika::Wylogowany;
    Biblioteka biblioteka;

    Pracownik pracownik1("Jan", "Kowalski", 5000, 3, "Wyzsze","12345678901");
    Pracownik pracownik2("Anna", "Nowak", 4500, 2, "Srednie", "23456789012");

    biblioteka.dodajPracownika(pracownik1);
    biblioteka.dodajPracownika(pracownik2);

    biblioteka.dodajKsiazke(Ksiazka("Pan Tadeusz", "Adam Mickiewicz", 1834, "Ksiegarnia Grzybowska", 400));
    biblioteka.dodajKsiazke(Ksiazka("Lalka", "Boleslaw Prus", 1890, "Nakladem Autora", 690));
    biblioteka.dodajKsiazke(Ksiazka("Quo Vadis", "Henryk Sienkiewicz", 1896, "Ksiegarnia F. Hoesicka", 580));
    biblioteka.dodajKsiazke(Ksiazka("Ferdydurke", "Witold Gombrowicz", 1937, "Roj", 248));
    biblioteka.dodajKsiazke(Ksiazka("Solaris", "Stanislaw Lem", 1961, "Wydawnictwo Literackie", 296));
    biblioteka.dodajKsiazke(Ksiazka("Chlopi", "Wladyslaw Reymont", 1904, "Towarzystwo Wydawnicze Ignis", 560));

    while (true) {
        switch (typUzytkownika) {
            case TypUzytkownika::Wylogowany: {
                typUzytkownika = wyborTypuUzytkownika();
                break;
            }
            case TypUzytkownika::Dyrektor: {
                cout << "Menu Dyrektora:\n";
                cout << "1. Dodaj ksiazke\n";
                cout << "2. Wyswietl ksiazki\n";
                cout << "3. Zapisz do pliku\n";
                cout << "4. Wczytaj z pliku\n";
                cout << "5. Usun ksiazke\n";
                cout << "6. Zatrudnij pracownika\n";
                cout << "7. Zwolnij pracownika\n";
                cout << "8. Wyswietl obecnych pracownikow\n";
                cout << "0. Wyloguj\n";
                int wybor;
                cin >> wybor;
                cin.ignore();
                vector<Pracownik> pracownicy;

                switch (wybor) {
                    case 1: {
                        string tytul, autor, wydawnictwo;
                        int rok_wydania, liczba_stron;
                        cout << "Podaj tytul: ";
                        getline(cin, tytul);
                        cout << "Podaj autora: ";
                        getline(cin, autor);
                        cout << "Podaj rok wydania: ";
                        cin >> rok_wydania;
                        cin.ignore();
                        cout << "Podaj wydawnictwo: ";
                        getline(cin, wydawnictwo);
                        cout << "Podaj liczbe stron: ";
                        cin >> liczba_stron;
                        cin.ignore();

                        biblioteka.dodajKsiazke(Ksiazka(tytul, autor, rok_wydania, wydawnictwo, liczba_stron));
                        cout << "Dodano ksiazke\n";
                        break;
                    }
                    case 2: {
                        biblioteka.wyswietlKsiazki();
                        break;
                    }
                    case 3: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.zapiszDoPliku(nazwaPliku);
                        cout << "Zapisano do pliku\n";
                        break;
                    }
                    case 4: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.wczytajZPliku(nazwaPliku);
                        cout << "Wczytano z pliku\n";
                        break;
                    }
                    case 5: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do usuniecia: ";
                        getline(cin, tytul);
                        biblioteka.usunKsiazke(tytul);
                        break;
                    }

                    case 6: {
                        string imie, nazwisko, pesel; 
                        double wynagrodzenie;
                        int dotychczasowyStazPracy;
                        string wyksztalcenie;

                        cout << "Podaj imie pracownika: ";
                        cin >> imie;
                        cout << "Podaj nazwisko pracownika: ";
                        cin >> nazwisko;
                        cout << "Podaj PESEL pracownika: ";
                        cin >> pesel;
                        cout << "Podaj wynagrodzenie pracownika: ";
                        cin >> wynagrodzenie;
                        cout << "Podaj dotychczasowy staz pracy pracownika: ";
                        cin >> dotychczasowyStazPracy;
                        cout << "Podaj wyksztalcenie pracownika: ";
                        cin >> wyksztalcenie;

                       Pracownik nowyPracownik(imie, nazwisko, wynagrodzenie, dotychczasowyStazPracy, wyksztalcenie, pesel);
                       biblioteka.dodajPracownika(nowyPracownik);

                        cout << "Pracownik " << nazwisko << " o PESEL " << pesel << " zostal zatrudniony." << endl;
                        break;

                    }

                   
                        case 7: {
                            string nazwisko, pesel;
                            cout << "Podaj nazwisko pracownika: ";
                            cin >> nazwisko;
                            cout << "Podaj PESEL pracownika: ";
                            cin >> pesel;
                            biblioteka.zwolnijPracownika(nazwisko, pesel);
                            break;
                        }

                        case 8: {
                            biblioteka.wyswietlObecnychPracownikow();
                            break;
                        }

                    case 0: {
                        typUzytkownika = TypUzytkownika::Wylogowany;
                        break;
                    }
                    default: {
                        cout << "Nieznana opcja\n";
                        break;
                    }
                }
                break;
            }
            case TypUzytkownika::Pracownik: {
                cout << "Menu Pracownika:\n";
                cout << "1. Dodaj ksiazke\n";
                cout << "2. Wyswietl ksiazki\n";
                cout << "3. Zapisz do pliku\n";
                cout << "4. Wczytaj z pliku\n";
                cout << "0. Wyloguj\n";
                int wybor;
                cin >> wybor;
                cin.ignore();

                switch (wybor) {
                    case 1: {
                        string tytul, autor, wydawnictwo;
                        int rok_wydania, liczba_stron;
                        cout << "Podaj tytul: ";
                        getline(cin, tytul);
                        cout << "Podaj autora: ";
                        getline(cin, autor);
                        cout << "Podaj rok wydania: ";
                        cin >> rok_wydania;
                        cin.ignore();
                        cout << "Podaj wydawnictwo: ";
                        getline(cin, wydawnictwo);
                        cout << "Podaj liczbe stron: ";
                        cin >> liczba_stron;
                        cin.ignore();

                        biblioteka.dodajKsiazke(Ksiazka(tytul, autor, rok_wydania, wydawnictwo, liczba_stron));
                        cout << "Dodano ksiazke\n";
                        break;
                    }
                    case 2: {
                        biblioteka.wyswietlKsiazki();
                        break;
                    }
                    case 3: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.zapiszDoPliku(nazwaPliku);
                        cout << "Zapisano do pliku\n";
                        break;
                    }
                    case 4: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.wczytajZPliku(nazwaPliku);
                        cout << "Wczytano z pliku\n";
                        break;
                    }
                    case 0: {
                        typUzytkownika = TypUzytkownika::Wylogowany;
                        break;
                    }
                    default: {
                        cout << "Nieznana opcja\n";
                        break;
                    }
                }
                break;
            }
            case TypUzytkownika::KlientPremium: {
                cout << "Menu Klienta Premium:\n";
                cout << "1. Wypozycz ksiazke\n";
                cout << "2. Wyswietl ksiazki\n";
                cout << "3. Zapisz do pliku\n";
                cout << "4. Wczytaj z pliku\n";
                cout << "5. Oddaj ksiazke\n";
                cout << "6. Zakup ksiazke\n";
                cout << "7. Wyswietl wypozyczone ksiazki\n";
                cout << "8. Znajdz ksiazke po tytule\n";
                cout << "9. Znajdz ksiazke po autorze\n";
                cout << "10. Wyswietl zakupione ksiazki\n";
                cout << "0. Wyloguj\n";
                int wybor;
                cin >> wybor;
                cin.ignore();

                switch (wybor) {
                    case 1: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do wypozyczenia: ";
                        getline(cin, tytul);
                        Ksiazka* ksiazka = biblioteka.znajdzKsiazke(tytul);
                        if (ksiazka) {
                            if (ksiazka->czyWypozyczona()) {
                                cout << "Ksiazka jest juz wypozyczona\n";
                            }
                            else {
                                ksiazka->wypozycz();
                                cout << "Wypozyczono ksiazke\n";
                            }
                        }
                        else {
                            cout << "Nie znaleziono ksiazki\n";
                        }
                        break;
                    }
                    case 2: {
                        biblioteka.wyswietlKsiazki();
                        break;
                    }
                    case 3: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.zapiszDoPliku(nazwaPliku);
                        cout << "Zapisano do pliku\n";
                        break;
                    }
                    case 4: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.wczytajZPliku(nazwaPliku);
                        cout << "Wczytano z pliku\n";
                        break;
                    }
                    case 5: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do oddania: ";
                        getline(cin, tytul);
                        biblioteka.oddajKsiazke(tytul);
                        break;
                    }
                    case 6: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do zakupu: ";
                        getline(cin, tytul);
                        biblioteka.zakupKsiazke(tytul);
                        break;
                    }
                    case 7: {
                        biblioteka.wyswietlWypozyczoneKsiazki();
                        break;
                    }
                    case 8: {
                        string tytul;
                        cout << "Podaj tytul ksiazki: ";
                        getline(cin, tytul);
                        Ksiazka* ksiazka = biblioteka.znajdzKsiazke(tytul);
                        if (ksiazka) {
                            cout << "Tytul: " << ksiazka->getTytul() << ", Autor: " << ksiazka->getAutor()
                                << ", Rok wydania: " << ksiazka->getRokWydania() << ", Wydawnictwo: "
                                << ksiazka->getWydawnictwo() << ", Liczba stron: " << ksiazka->getLiczbaStron() << "\n";
                        }
                        else {
                            cout << "Nie znaleziono ksiazki\n";
                        }
                        break;
                    }
                    case 9: {
                        string autor;
                        cout << "Podaj autora ksiazki: ";
                        getline(cin, autor);
                        Ksiazka* ksiazka = biblioteka.znajdzKsiazkePoAutorze(autor);
                        if (ksiazka) {
                            cout << "Tytul: " << ksiazka->getTytul() << ", Autor: " << ksiazka->getAutor()
                                << ", Rok wydania: " << ksiazka->getRokWydania() << ", Wydawnictwo: "
                                << ksiazka->getWydawnictwo() << ", Liczba stron: " << ksiazka->getLiczbaStron() << "\n";
                        }
                        else {
                            cout << "Nie znaleziono ksiazki\n";
                        }
                        break;
                    }

                    case 10: {
                        biblioteka.wyswietlZakupioneKsiazki(); 
                        break;
                        }
                    case 0: {
                        typUzytkownika = TypUzytkownika::Wylogowany;
                        break;
                    }
                    default: {
                        cout << "Nieznana opcja\n";
                        break;
                    }
                }
                break;
            }
            case TypUzytkownika::Klient: {
                cout << "Menu Klienta:\n";
                cout << "1. Wypozycz ksiazke\n";
                cout << "2. Wyswietl ksiazki\n";
                cout << "3. Zapisz do pliku\n";
                cout << "4. Wczytaj z pliku\n";
                cout << "5. Oddaj ksiazke\n";
                cout << "6. Wyswietl wypozyczone ksiazki\n";
                cout << "0. Wyloguj\n";
                int wybor;
                cin >> wybor;
                cin.ignore();

                switch (wybor) {
                    case 1: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do wypozyczenia: ";
                        getline(cin, tytul);
                        Ksiazka* ksiazka = biblioteka.znajdzKsiazke(tytul);
                        if (ksiazka) {
                            if (ksiazka->czyWypozyczona()) {
                                cout << "Ksiazka jest juz wypozyczona\n";
                            }
                            else {
                                ksiazka->wypozycz();
                                cout << "Wypozyczono ksiazke\n";
                            }
                        }
                        else {
                            cout << "Nie znaleziono ksiazki\n";
                        }
                        break;
                    }
                    case 2: {
                        biblioteka.wyswietlKsiazki();
                        break;
                    }
                    case 3: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.zapiszDoPliku(nazwaPliku);
                        cout << "Zapisano do pliku\n";
                        break;
                    }
                    case 4: {
                        string nazwaPliku;
                        cout << "Podaj nazwe pliku: ";
                        getline(cin, nazwaPliku);
                        biblioteka.wczytajZPliku(nazwaPliku);
                        cout << "Wczytano z pliku\n";
                        break;
                    }
                    case 5: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do oddania: ";
                        getline(cin, tytul);
                        biblioteka.oddajKsiazke(tytul);
                        break;
                    }
                    case 6: {
                        biblioteka.wyswietlWypozyczoneKsiazki();
                        break;
                    }
                    case 0: {
                        typUzytkownika = TypUzytkownika::Wylogowany;
                        break;
                    }
                    default: {
                        cout << "Nieznana opcja\n";
                        break;
                    }
                }
                break;
            }
            default: {
                cout << "Nieznany typ uzytkownika\n";
                typUzytkownika = TypUzytkownika::Wylogowany;
                break;
            }
        }
    }

    return 0;
}










