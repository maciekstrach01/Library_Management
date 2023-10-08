#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <chrono>
#include "Biblioteka.h"
#include "Ksiazka.h"
#include "Pracownik.h"

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
                    /*case 1: {
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
                    */
                    case 1: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do wypozyczenia: ";
                        getline(cin, tytul);
                        Ksiazka* ksiazka = biblioteka.znajdzKsiazke(tytul);
                        if (ksiazka) {
                            if (ksiazka->czyWypozyczona()) {
                                cout << "Ksiazka jest juz wypozyczona\n";
                            }
                            else if (ksiazka->czyZakupiona()) {
                                cout << "Ksiazka jest juz zakupiona, nie mozna wypozyczyc\n";
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

                        // Sprawdź, czy książka jest już wypożyczona
                        Ksiazka* ksiazka = biblioteka.znajdzKsiazke(tytul);
                        if (ksiazka) {
                            if (ksiazka->czyWypozyczona()) {
                                cout << "Nie mozna zakupic wypozyczonej ksiazki\n";
                            }
                            else {
                                biblioteka.zakupKsiazke(tytul);
                                cout << "Zakupiono ksiazke\n";
                                biblioteka.usunKsiazke(tytul);
                            }
                        }
                        else {
                            cout << "Nie znaleziono ksiazki\n";
                        }
                        break;
                    }

                    /*case 6: {
                        string tytul;
                        cout << "Podaj tytul ksiazki do zakupu: ";
                        getline(cin, tytul);
                        biblioteka.zakupKsiazke(tytul);
                        break;
                    }*/
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










