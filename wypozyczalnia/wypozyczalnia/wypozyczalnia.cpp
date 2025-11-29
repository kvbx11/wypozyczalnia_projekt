#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <windows.h>

using namespace std;

class Sprzet {
private:
    string nazwa;
    int ilosc;
    double cena;
public:
    Sprzet(string n = "", int il = 0, double c = 0) : nazwa(n), ilosc(il), cena(c) {}

    string get_nazwa() { return nazwa; }
    int get_ilosc() { return ilosc; }
    double get_cena() { return cena; }

    void set_nazwa(string n) { nazwa = n; }
    void set_ilosc(int il) { ilosc = il; }
    void set_cena(double c) { cena = c; }
};

class OsobaWypozyczajaca {
private:
    string imie;
    string nazwisko;
    string telefon;
public:
    OsobaWypozyczajaca() {}
    OsobaWypozyczajaca(string im, string naz, string tel) : imie(im), nazwisko(naz), telefon(tel) {}

    string get_imie() { return imie; }
    string get_nazwisko() { return nazwisko; }
    string get_telefon() { return telefon; }
};

class Wypozyczenie {
private:
    int id_wypozyczenia;
    string nazwa_sprzetu;
    int ilosc_sprzetu;
    string poczatek_wypozyczenia;
    string koniec_wypozyczenia;
    int ilosc_dni_wypozyczenia;
    OsobaWypozyczajaca klient;

    string get_date() {
        time_t now = time(0);
        tm tm;
        localtime_s(&tm, &now);
        char buf[11];
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
        return string(buf);
    }

    string oblicz_date() {
        tm tm = {};
        tm.tm_year = stoi(poczatek_wypozyczenia.substr(0, 4)) - 1900;
        tm.tm_mon = stoi(poczatek_wypozyczenia.substr(5, 2)) - 1;
        tm.tm_mday = stoi(poczatek_wypozyczenia.substr(8, 2)) + ilosc_dni_wypozyczenia;
        mktime(&tm);
        char buf[11];
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
        return string(buf);
    }

public:
    Wypozyczenie(int id = 0, string nazwa = "", int ilosc = 0, int dni = 0) {
        id_wypozyczenia = id;
        nazwa_sprzetu = nazwa;
        ilosc_sprzetu = ilosc;
        ilosc_dni_wypozyczenia = dni;
        poczatek_wypozyczenia = get_date();
        koniec_wypozyczenia = oblicz_date();
    }

    void wypozycz() {
        cout << "========= PODAJ DANE KLIENTA ========\n";
        string imie, nazwisko, telefon;
        cin.ignore();
        cout << "Imię: "; getline(cin, imie);
        cout << "Nazwisko: "; getline(cin, nazwisko);
        cout << "Telefon: "; getline(cin, telefon);
        klient = OsobaWypozyczajaca(imie, nazwisko, telefon);
        cout << "=====================================\n";
    }


    string get_nazwa_sprzetu() { return nazwa_sprzetu; }
    int get_ilosc_sprzetu() { return ilosc_sprzetu; }
    int get_id() { return id_wypozyczenia; }
    int get_ilosc_dni_wypozyczenia() { return ilosc_dni_wypozyczenia; }
    string get_koniec_wypozyczenia() { return koniec_wypozyczenia; }
    string get_poczatek_wypozyczenia() { return poczatek_wypozyczenia; }
    OsobaWypozyczajaca get_klient() { return klient; }

    void set_poczatek_wypozyczenia(const string& data) { poczatek_wypozyczenia = data; }
    void set_koniec_wypozyczenia(const string& data) { koniec_wypozyczenia = data; }
    void set_klient(OsobaWypozyczajaca k) { klient = k; }
};

class Wypozyczalnia {
private:
    vector<Sprzet> sprzety;
    vector<Wypozyczenie> wypozyczenia;
    vector<OsobaWypozyczajaca> klienci;

    void wczytaj_wypozyczenia() {
        ifstream plik("wypozyczenia.txt");
        if (!plik.is_open()) return;
        string line;
        while (getline(plik, line)) {
            istringstream ss(line);
            int id, ilosc, dni;
            string nazwa, poczatek, koniec, imie, nazwisko, telefon;
            ss >> id >> nazwa >> ilosc >> dni >> poczatek >> koniec >> imie >> nazwisko >> telefon;
            Wypozyczenie w(id, nazwa, ilosc, dni);
            w.set_poczatek_wypozyczenia(poczatek);
            w.set_koniec_wypozyczenia(koniec);
            w.set_klient(OsobaWypozyczajaca(imie, nazwisko, telefon));
            wypozyczenia.push_back(w);
        }
    }

public:
    Wypozyczalnia() { wczytaj_sprzet(); wczytaj_wypozyczenia(); }

    void wczytaj_sprzet() {
        ifstream plik("sprzet_wodny.txt");
        if (!plik.is_open()) { cout << "Błąd otwarcia pliku!" << endl; return; }

        string line;
        while (getline(plik, line)) {
            istringstream ss(line);
            string nazwa;
            int ilosc;
            double cena;
            ss >> nazwa >> ilosc >> cena;
            sprzety.push_back(Sprzet(nazwa, ilosc, cena));
        }
    }

    void zapisz_stan() {
        ofstream plik("sprzet_wodny.txt");
        for (auto& s : sprzety)
            plik << s.get_nazwa() << " " << s.get_ilosc() << " " << s.get_cena() << "\n";
    }

    void zapisz_wypozyczenia() {
        ofstream plik("wypozyczenia.txt");
        for (auto& w : wypozyczenia)
            plik << w.get_id() << " " << w.get_nazwa_sprzetu() << " "
            << w.get_ilosc_sprzetu() << " " << w.get_ilosc_dni_wypozyczenia() << " "
            << w.get_poczatek_wypozyczenia() << " " << w.get_koniec_wypozyczenia() << " "
            << w.get_klient().get_imie() << " " << w.get_klient().get_nazwisko() << " " << w.get_klient().get_telefon() << "\n";
    }

    

    string dzisiejsza_data() {
        time_t now = time(0);
        tm tm;
        localtime_s(&tm, &now);
        char buf[11];
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
        return string(buf);
    }

    void wyswietl_sprzety() {
        cout << "=== SPRZĘT DOSTĘPNY W NASZEJ WYPOŻYCZALNI ===\n";
        for (auto& s : sprzety)
            cout << " > " << s.get_nazwa() << ", ilość: " << s.get_ilosc() << "\n";
        cout << "=============================================\n";
        system("pause");
    }

    void wyswietl_cennik() {
        cout << "=== CENNIK WYPOŻYCZALNI SPRZĘTU WODNEGO ===\n";
        for (auto& s : sprzety)
            cout << " > " << s.get_nazwa() << ": " << s.get_cena() << " PLN/dzień\n";
        cout << "===========================================\n";
        system("pause");
    }

    void wypozycz_sprzet() {
        int wybor = 0;
        char key;

        while (true) {
            system("cls");
            cout << "=== WYBIERZ SPRZĘT DO WYPOŻYCZENIA ===\n";
            for (int i = 0; i < sprzety.size(); i++)
                cout << (wybor == i ? "> " : "  ") << sprzety[i].get_nazwa() << " (dostępne: " << sprzety[i].get_ilosc() << ")\n";
            cout << (wybor == sprzety.size() ? "> " : "  ") << "Wstecz\n";
            cout << "=========================================\n";

            key = _getch();
            if (key == 72) wybor = (wybor + sprzety.size()) % (sprzety.size() + 1);
            else if (key == 80) wybor = (wybor + 1) % (sprzety.size() + 1);
            else if (key == 13) {
                if (wybor == sprzety.size()) return;

                int ilosc, dni;
                cout << "Podaj ilość: "; cin >> ilosc;
                cout << "Podaj liczbę dni: "; cin >> dni;

                if (ilosc > sprzety[wybor].get_ilosc()) {
                    cout << "Niewystarczająca ilość sprzętu!\n";
                    system("pause");
                    continue;
                }

                int nowe_id = wypozyczenia.size() + 1;
                Wypozyczenie w(nowe_id, sprzety[wybor].get_nazwa(), ilosc, dni);
                w.wypozycz();
                sprzety[wybor].set_ilosc(sprzety[wybor].get_ilosc() - ilosc);
                wypozyczenia.push_back(w);
                zapisz_wypozyczenia();
                cout << "Sprzęt został wypożyczony pomyślnie!\n";
                system("pause");
                return;
            }
        }
    }
    void wczytaj_wypozyczenia_z_pliku() {
        wypozyczenia.clear();
        ifstream plik("wypozyczenia.txt");
        if (!plik.is_open()) return;

        string line;
        while (getline(plik, line)) {
            istringstream ss(line);
            int id, ilosc, dni;
            string nazwa, poczatek, koniec, imie, nazwisko, telefon;
            ss >> id >> nazwa >> ilosc >> dni >> poczatek >> koniec >> imie >> nazwisko >> telefon;
            Wypozyczenie w(id, nazwa, ilosc, dni);
            w.set_poczatek_wypozyczenia(poczatek);
            w.set_koniec_wypozyczenia(koniec);
            w.set_klient(OsobaWypozyczajaca(imie, nazwisko, telefon));
            wypozyczenia.push_back(w);
        }
    }

    void zakoncz_wypozyczenie(int idx) {
        if (idx < 0 || idx >= wypozyczenia.size()) return;

        string nazwa = wypozyczenia[idx].get_nazwa_sprzetu();
        int ilosc = wypozyczenia[idx].get_ilosc_sprzetu();
        int dni = wypozyczenia[idx].get_ilosc_dni_wypozyczenia();
        double cena = 0;
        for (auto& s : sprzety) {
            if (s.get_nazwa() == nazwa) {
                cena = s.get_cena();
                s.set_ilosc(s.get_ilosc() + ilosc);
                break;
            }
        }

        double do_zaplaty = cena * ilosc * dni;
        cout << "========= PODSUMOWANIE WYPOŻYCZENIA =========\n";
        cout << "Sprzęt: " << nazwa << "\nIlość: " << ilosc << "\nDni: " << dni
            << "\nCena za dzień: " << cena << " PLN\n-------------------------------------------\nDO ZAPŁATY: "
            << do_zaplaty << " PLN\n===========================================\n";

        ofstream archiwum("archiwalne_wypozyczenia.txt", ios::app);
        auto& w = wypozyczenia[idx];
        archiwum << w.get_id() << " " << w.get_nazwa_sprzetu() << " "
            << w.get_ilosc_sprzetu() << " " << w.get_ilosc_dni_wypozyczenia() << " "
            << w.get_poczatek_wypozyczenia() << " " << w.get_koniec_wypozyczenia() << " "
            << w.get_klient().get_imie() << " " << w.get_klient().get_nazwisko() << " "
            << w.get_klient().get_telefon() << "\n";
        archiwum.close();

        wypozyczenia.erase(wypozyczenia.begin() + idx);
        zapisz_wypozyczenia();
        system("pause");
    }

    void wyswietl_wypozyczenia() {
        if (wypozyczenia.empty()) {
            cout << "Brak aktualnych wypożyczeń.\n";
            system("pause");
            return;
        }

        int wybor = 0;
        char key;
        while (true) {
            system("cls");
            cout << "========= AKTUALNE WYPOŻYCZENIA =========\n";
            for (int i = 0; i < wypozyczenia.size(); i++)
                cout << (wybor == i ? "> " : "  ") << "ID: " << wypozyczenia[i].get_id()
                << " -> " << wypozyczenia[i].get_nazwa_sprzetu()
                << ", ilość: " << wypozyczenia[i].get_ilosc_sprzetu()
                << ", koniec: " << wypozyczenia[i].get_koniec_wypozyczenia() << "\n";
            cout << (wybor == wypozyczenia.size() ? "> " : "  ") << "Wstecz\n";
            cout << "=========================================\n";

            key = _getch();
            if (key == 72) wybor = (wybor + wypozyczenia.size()) % (wypozyczenia.size() + 1);
            else if (key == 80) wybor = (wybor + 1) % (wypozyczenia.size() + 1);
            else if (key == 13) {
                if (wybor == wypozyczenia.size()) return;
                zakoncz_wypozyczenie(wybor);
                if (wypozyczenia.empty()) {
                    cout << "Brak aktualnych wypożyczeń.\n";
                    system("pause");
                    return;
                }
            }
        }
    }

    bool czy_data_minela(const string& data) {
        // data w formacie YYYY-MM-DD
        time_t now = time(0);
        tm tm_now;
        localtime_s(&tm_now, &now);

        int rok = stoi(data.substr(0, 4));
        int miesiac = stoi(data.substr(5, 2));
        int dzien = stoi(data.substr(8, 2));

        if (rok < tm_now.tm_year + 1900) return true;
        if (rok > tm_now.tm_year + 1900) return false;
        if (miesiac < tm_now.tm_mon + 1) return true;
        if (miesiac > tm_now.tm_mon + 1) return false;
        if (dzien < tm_now.tm_mday) return true;
        return false;
    }

    void wyswietl_archiwalne_wypozyczenia_klient(const string& telefon) {
        cout << "=== ARCHIWALNE WYPOŻYCZENIA ===\n";
        ifstream plik("archiwalne_wypozyczenia.txt");
        if (!plik.is_open()) { cout << "Brak archiwalnych danych.\n"; system("pause"); return; }

        string line;
        bool jest = false;
        while (getline(plik, line)) {
            istringstream ss(line);
            int id, ilosc, dni;
            string nazwa, poczatek, koniec, imie, nazwisko, tel;
            ss >> id >> nazwa >> ilosc >> dni >> poczatek >> koniec >> imie >> nazwisko >> tel;

            if (tel == telefon && czy_data_minela(koniec)) { 
                cout << "ID: " << id
                    << ", Sprzęt: " << nazwa
                    << ", Ilość: " << ilosc
                    << ", Od: " << poczatek
                    << ", Do: " << koniec << "\n";
                jest = true;
            }
        }

        if (!jest) cout << "Brak archiwalnych wypożyczeń.\n";
        cout << "===============================\n";
        system("pause");
    }

    void wyswietl_aktualne_wypozyczenia_klient(const string& telefon) {
        cout << "=== AKTUALNE WYPOŻYCZENIA ===\n";
        bool jest = false;
        for (auto& w : wypozyczenia) {
            if (w.get_klient().get_telefon() == telefon && !czy_data_minela(w.get_koniec_wypozyczenia())) {
                cout << "ID: " << w.get_id()
                    << ", Sprzęt: " << w.get_nazwa_sprzetu()
                    << ", Ilość: " << w.get_ilosc_sprzetu()
                    << ", Koniec: " << w.get_koniec_wypozyczenia() << "\n";
                jest = true;
            }
        }
        if (!jest) cout << "Brak aktualnych wypożyczeń.\n";
        cout << "===============================\n";
        system("pause");
    }

    void wyswietl_wypozyczenia_bez_zakonczenia() {
        if (wypozyczenia.empty()) {
            cout << "Brak aktualnych wypożyczeń.\n";
            system("pause");
            return;
        }

        cout << "========= AKTUALNE WYPOŻYCZENIA =========\n";
        for (auto& w : wypozyczenia)
            cout << "ID: " << w.get_id() << " -> " << w.get_nazwa_sprzetu()
            << ", ilość: " << w.get_ilosc_sprzetu()
            << ", koniec: " << w.get_koniec_wypozyczenia() << "\n";
        cout << "=========================================\n";
        system("pause");
    }


    void wybierz_sprzet_do_edycji() {
        int wybor = 0;
        char key;
        while (true) {
            system("cls");
            cout << "===== EDYTUJ SPRZĘT =====\n";
            for (int i = 0; i < sprzety.size(); i++)
                cout << (wybor == i ? "> " : "  ") << sprzety[i].get_nazwa() << "\n";
            cout << (wybor == sprzety.size() ? "> " : "  ") << "Wstecz\n";
            cout << "==========================\n";

            key = _getch();
            if (key == 72) wybor = (wybor + sprzety.size()) % (sprzety.size() + 1);
            else if (key == 80) wybor = (wybor + 1) % (sprzety.size() + 1);
            else if (key == 13) {
                if (wybor == sprzety.size()) return;
                edytuj_sprzet(wybor);
            }
        }
    }

    void edytuj_sprzet(int idx) {
        int wybor = 0;
        char key;
        while (true) {
            system("cls");
            cout << "===== EDYCJA PARAMETRÓW SPRZĘTU =====\n";
            cout << (wybor == 0 ? "> " : "  ") << "Nazwa: " << sprzety[idx].get_nazwa() << "\n";
            cout << (wybor == 1 ? "> " : "  ") << "Ilość: " << sprzety[idx].get_ilosc() << "\n";
            cout << (wybor == 2 ? "> " : "  ") << "Cena: " << sprzety[idx].get_cena() << "\n";
            cout << (wybor == 3 ? "> " : "  ") << "Powrót\n";
            cout << "=====================================\n";

            key = _getch();
            if (key == 72) wybor = (wybor + 3) % 4;
            else if (key == 80) wybor = (wybor + 1) % 4;
            else if (key == 13) {
                switch (wybor) {
                case 0: { string n; cout << "Podaj nową nazwę: "; cin >> n; sprzety[idx].set_nazwa(n); break; }
                case 1: { int il; cout << "Podaj nową ilość: "; cin >> il; sprzety[idx].set_ilosc(il); break; }
                case 2: { double c; cout << "Podaj nową cenę: "; cin >> c; sprzety[idx].set_cena(c); break; }
                case 3: return;
                }
                zapisz_stan();
            }
        }
    }

};


void modul_pracownika(Wypozyczalnia& wypozyczalnia) {
    int wybor = 0;
    char key;

    while (true) {
        system("cls");
        cout << "=== WYPOŻYCZALNIA SPRZĘTU WODNEGO ===\n";
        cout << (wybor == 0 ? "> " : "  ") << "Wyświetl dostępne sprzęty\n";
        cout << (wybor == 1 ? "> " : "  ") << "Wypożycz sprzęt\n";
        cout << (wybor == 2 ? "> " : "  ") << "Zakończ wypożyczenie\n";
        cout << (wybor == 3 ? "> " : "  ") << "Cennik\n";
        cout << (wybor == 4 ? "> " : "  ") << "Edytuj sprzęty\n";
        cout << (wybor == 5 ? "> " : "  ") << "Wyświetl wypożyczenia\n";
        // edycja danych uzytkownika
        cout << (wybor == 6 ? "> " : "  ") << "Wyjdź\n";
        cout << "=====================================\n";

        key = _getch();
        if (key == 72) wybor = (wybor + 6) % 7;
        else if (key == 80) wybor = (wybor + 1) % 7;
        else if (key == 13) {
            switch (wybor) {
            case 0: wypozyczalnia.wyswietl_sprzety(); break;
            case 1: wypozyczalnia.wypozycz_sprzet(); break;
            case 2: wypozyczalnia.wyswietl_wypozyczenia(); break;
            case 3: wypozyczalnia.wyswietl_cennik(); break;
            case 4: wypozyczalnia.wybierz_sprzet_do_edycji(); break;
            case 5: wypozyczalnia.wyswietl_wypozyczenia_bez_zakonczenia(); break;
            case 6:
                wypozyczalnia.zapisz_stan();
                wypozyczalnia.zapisz_wypozyczenia();
                cout << "Dziękujemy za skorzystanie z oprogramowania. Do zobaczenia!\n";
                return;
            }
            

        }
    }
}

void modul_klienta(Wypozyczalnia& wypozyczalnia, const string& telefon_zalogowanego) {
    int wybor = 0;
    char key;

    while (true) {
        system("cls");
        cout << "=== WYPOŻYCZALNIA SPRZĘTU WODNEGO ===\n";
        cout << (wybor == 0 ? "> " : "  ") << "Wyświetl dostępność sprzętów\n";
        cout << (wybor == 1 ? "> " : "  ") << "Cennik\n";
        cout << (wybor == 2 ? "> " : "  ") << "Wyświetl aktualne wypożyczenia\n";
        cout << (wybor == 3 ? "> " : "  ") << "Wyświetl archiwalne wypożyczenia\n";
        cout << (wybor == 4 ? "> " : "  ") << "Wyjdź\n";
        cout << "=====================================\n";

        key = _getch();
        if (key == 72) wybor = (wybor + 4) % 5;
        else if (key == 80) wybor = (wybor + 1) % 5;
        else if (key == 13) {
            switch (wybor) {
            case 0: wypozyczalnia.wyswietl_sprzety(); break;
            case 1: wypozyczalnia.wyswietl_cennik(); break;
            case 2: wypozyczalnia.wyswietl_aktualne_wypozyczenia_klient(telefon_zalogowanego); break;
            case 3: wypozyczalnia.wyswietl_archiwalne_wypozyczenia_klient(telefon_zalogowanego); break;
            case 4:
                wypozyczalnia.zapisz_stan();
                wypozyczalnia.zapisz_wypozyczenia();
                cout << "Dziękujemy za skorzystanie z oprogramowania. Do zobaczenia!\n";
                return;
            }
        }
    }
}

bool sprawdz_dane_w_pliku(const string& nazwa_pliku, const string& login, const string& haslo, string& telefon) {
    ifstream plik(nazwa_pliku);
    if (!plik.is_open()) return false;

    string l, h, tel;
    while (plik >> l >> h >> tel) {
        if (l == login && h == haslo) {
            telefon = tel;
            return true;
        }
    }
    return false;
}

bool login(string& rola, string& telefon_zalogowanego) {
    string login_input, haslo_input;
    char znak;

    cout << "=========== LOGOWANIE ===========\n";
    cout << "LOGIN: ";
    cin >> login_input;

    cout << "HASŁO: ";
    haslo_input = "";

    while (true) {
        znak = _getch();
        if (znak == 13) break;
        else if (znak == 8) {
            if (!haslo_input.empty()) { haslo_input.pop_back(); cout << "\b \b"; }
        }
        else { haslo_input += znak; cout << "*"; }
    }
    cout << "\n=================================\n";

    // admin
    if (login_input == "admin" && haslo_input == "admin") {
        rola = "pracownik";
        telefon_zalogowanego = "";
        return true;
    }

    // pracownicy
    if (sprawdz_dane_w_pliku("pracownicy.txt", login_input, haslo_input, telefon_zalogowanego)) {
        rola = "pracownik";
        return true;
    }

    // klienci
    if (sprawdz_dane_w_pliku("klienci.txt", login_input, haslo_input, telefon_zalogowanego)) {
        rola = "klient";
        return true;
    }

    return false;
}

int main() {
    setlocale(LC_ALL, "polish");
    Wypozyczalnia wypozyczalnia;

    while (true) {
        system("cls");
        string rola;
        string telefon_zalogowanego;
        if (!login(rola, telefon_zalogowanego)) {
            cout << "Błędne dane logowania!\n";
            system("pause");
            continue;
        }

        if (rola == "pracownik") {
            cout << "Pomyślnie zalogowano jako: pracownik!" << endl;
            cout << "Trwa wczytywanie panelu..." << endl;
            Sleep(2000);
            modul_pracownika(wypozyczalnia);
        }

        if (rola == "klient") {
            wypozyczalnia.wczytaj_wypozyczenia_z_pliku();
            cout << "Pomyślnie zalogowano jako: klient!" << endl;
            cout << "Trwa wczytywanie panelu..." << endl;
            Sleep(2000);
            modul_klienta(wypozyczalnia, telefon_zalogowanego);
        }
            
    }
    // todo
    // archiwalne wypozyczenia po stronie klienta
    // dodawanie uzytkownikow po stronie pracownika
    // kolorki, debug
    return 0;
}
