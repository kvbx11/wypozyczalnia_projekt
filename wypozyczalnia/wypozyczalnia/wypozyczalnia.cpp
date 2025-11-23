#include <iostream>
#include <conio.h> // dla _getch()
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class Sprzet {
private:
    string nazwa;
    int ilosc;
    double cena;
public:
    Sprzet(string n, int il, double c){
        this->nazwa = n;
        this->ilosc = il;
        this->cena = c;
    }

    string get_nazwa() {
        return nazwa;
	}
    int get_ilosc() {
        return ilosc;
	}
    double get_cena() {
        return cena;
    }
    void set_nazwa(string n) {
        this->nazwa = n;
    }
    void set_cena(double c) {
        this->cena = c;
    }
    void set_ilosc(int il) {
        this->ilosc = il;
    }
};

class OsobaWypozyczajaca{
private:
    string imie;
    string nazwisko;
	string telefon;
public:
	OsobaWypozyczajaca() {}
    OsobaWypozyczajaca(string im, string naz, string tel) {
        this->imie = im;
        this->nazwisko = naz;
        this->telefon = tel;
	}
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
        tm.tm_mday = stoi(poczatek_wypozyczenia.substr(8, 2));
        tm.tm_mday += ilosc_dni_wypozyczenia;

        mktime(&tm);
        char buf[11];
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
        return string(buf);
    }

public:
    Wypozyczenie(int id, string nazwa, int ilosc, int dni) {
        this->id_wypozyczenia = id;
        this->nazwa_sprzetu = nazwa;
        this->ilosc_sprzetu = ilosc;
        this->ilosc_dni_wypozyczenia = dni;

        this->poczatek_wypozyczenia = get_date();
        this->koniec_wypozyczenia = oblicz_date();
    }

    void wypozycz() {
        cout << "========= PODAJ DANE KLIENTA ======== " << endl;
		string imie, nazwisko, telefon;
		cout << "Imię: ";
		cin >> imie;
		cout << "Nazwisko: ";
		cin >> nazwisko;
		cout << "Telefon: ";
		cin >> telefon;
        cout << "=====================================\n";
        cout << endl;
		klient=OsobaWypozyczajaca(imie, nazwisko, telefon);
		cout << "Pomyślnie wypożyczono sprzęt!" << endl;
    }
    string get_nazwa_sprzetu() {
        return nazwa_sprzetu;
	}
    int get_ilosc_sprzetu() {
        return ilosc_sprzetu;
	}
    int get_id() {
		return id_wypozyczenia;
    }
    int get_ilosc_dni_wypozyczenia() {
        return ilosc_dni_wypozyczenia;
	}
    string get_koniec_wypozyczenia() {
        return koniec_wypozyczenia;
    }
};


class Wypozyczalnia{
private:
    vector<Sprzet>sprzety;
	vector<Wypozyczenie>wypozyczenia;
public:
    Wypozyczalnia() {
        wczytaj();
    }

    void wczytaj() {
        ifstream plik;
        plik.open("sprzet_wodny.txt", ios::in);

        if (plik.good()) {
            string line;
            while (getline(plik, line)) {
                istringstream ss(line);
                string nazwa;
                int ilosc;
                double cena;

                ss >> nazwa >> ilosc >> cena;
                Sprzet s1(nazwa, ilosc, cena);
                sprzety.push_back(s1);
            }
        }
        else {
            cout << "Błąd otwarcia pliku!" << endl;
        }
    }

    void zapisz_stan() {
        ofstream plik;
        plik.open("sprzet_wodny.txt", ios::out);
        if (plik.good()) {
            for (auto it : sprzety) {
                plik << it.get_nazwa() << " " << it.get_ilosc() << " " << it.get_cena() << endl;
            }
        }
        else {
            cout << "Błąd zapisu do pliku!" << endl;
        }
	}

    void wyswietl_sprzety() {
        cout << "SPRZĘT DOSTĘPNY W NASZEJ WYPOŻYCZALNI" << endl;
		for (auto it : sprzety) {
            cout <<" > " << it.get_nazwa() << ", dostępna ilość: " << it.get_ilosc() << endl;
        }
        cout << "=====================================\n";
    }

    void wyswietl_cennik() {
        cout << "CENNIK WYPOŻYCZALNI SPRZĘTU WODNEGO" << endl;
        for (auto it : sprzety) {
            cout << " > " << it.get_nazwa() << ", cena za dzień: " << it.get_cena() << " PLN" << endl;
        }
        cout << "=====================================\n";
    }

    void wybierz_sprzet_do_edycji() {
        int wybor = 0;
        char key;
        while (true) {
            system("cls");
            cout << "===== EDYTUJ PARAMETRY SPRZĘTU: =====\n";
            for (int i = 0; i < sprzety.size(); i++) {
                cout << (wybor == i ? "> " : "  ") << sprzety[i].get_nazwa()<<"\n";
            }
            cout << endl;
            cout << (wybor == sprzety.size() ? "> " : "  ") << "Wstecz" << "\n";
            cout << "=====================================\n";
            key = _getch();

            if (key == 72) wybor = (wybor + sprzety.size()) % (sprzety.size()+1);
            else if (key == 80) wybor = (wybor + 1) % (sprzety.size()+1);
            else if (key == 13) { // Enter
                if (wybor == sprzety.size()) {
                    return;
                }
                else {
                    edytuj_sprzet(wybor);
                    system("pause");
                }
                
            }
        }
    }
        
    void edytuj_sprzet(int idx) {
        int wybor = 0;
        char key;
        cout << "===== WYBÓR PARAMETRU DO EDYCJI =====" << endl;
        while (true) {
            system("cls");
            cout << (wybor == 0 ? "> " : "  ") <<"Sprzęt: " << sprzety[idx].get_nazwa() << "\n";
            cout << (wybor == 1 ? "> " : "  ") <<"Ilość (początkowa): " << sprzety[idx].get_ilosc() << "\n";
            cout << (wybor == 2 ? "> " : "  ") << "Cena wynajmu (per dzień): " << sprzety[idx].get_cena() << "\n";
            cout << endl;
            cout << (wybor == 3 ? "> " : "  ") << "Powrót" << "\n";
            cout << "=====================================\n";
            key = _getch();

            if (key == 72) wybor = (wybor + 3) % 4;
            else if (key == 80) wybor = (wybor + 1) % 4;
            else if (key == 13) { // Enter
                string nowa_n;
                int nowa_ilosc;
                double nowa_cena;
                switch (wybor) {
                case 0:
                    cout << "Podaj nową nazwę: " << endl;
                    cin >> nowa_n;
                    sprzety[idx].set_nazwa(nowa_n);
                    cout << "Pomyślnie zmieniono nazwę!";
                    break;
                case 1:
                    cout << "Podaj nową ilość: " << endl;
                    cin >> nowa_ilosc;
                    sprzety[idx].set_ilosc(nowa_ilosc);
                    cout << "Pomyślnie zmieniono ilość!";
                    break;
                case 2:
                    cout << "Podaj nową cenę: " << endl;
                    cin >> nowa_cena;
                    sprzety[idx].set_cena(nowa_cena);
                    cout << "Pomyślnie zmieniono cenę!";
                    break;
                case 3:
                    return;
                    break;
                }

            }
        }
    }

    void wypozycz_sprzet() {
        int wybor = 0;
        char key;

        while (true) {
            system("cls");
            cout << "===== WYBIERZ SPRZĘT DO WYPOŻYCZENIA =====\n";

            for (int i = 0; i < sprzety.size(); i++) {
                cout << (wybor == i ? "> " : "  ") << sprzety[i].get_nazwa()
                    << " (dostępne: " << sprzety[i].get_ilosc() << ")\n";
            }

            cout << endl;
            cout << (wybor == sprzety.size() ? "> " : "  ") << "Wstecz\n";
            cout << "===========================================\n";

            key = _getch();

            if (key == 72) wybor = (wybor + sprzety.size()) % (sprzety.size() + 1);
            else if (key == 80) wybor = (wybor + 1) % (sprzety.size() + 1);
            else if (key == 13) { // Enter

                if (wybor == sprzety.size()) {
                    return; // powrót
                }

                int ilosc, dni;
                cout << "Podaj ilość do wypożyczenia: ";
                cin >> ilosc;

                cout << "Podaj ilość dni wypożyczenia: ";
                cin >> dni;

                if (sprzety[wybor].get_ilosc() < ilosc) {
                    cout << "Niewystarczająca ilość sprzętu!\n";
                    system("pause");
                    continue;
                }

                int nowe_id = wypozyczenia.size() + 1;
                Wypozyczenie w1(nowe_id, sprzety[wybor].get_nazwa(), ilosc, dni);

                w1.wypozycz(); 

                sprzety[wybor].set_ilosc(sprzety[wybor].get_ilosc() - ilosc);

                wypozyczenia.push_back(w1);

                cout << "\nSprzęt został wypożyczony poprawnie!\n";
                system("pause");
            }
        }
    }

    void wyswietl_wypozyczenia() {
        cout << "===== AKTUALNE WYPOŻYCZENIA =====" << endl;
        if (wypozyczenia.empty()) {
            cout << "Brak aktualnych wypożyczeń." << endl;
        }
        else {
            int wybor = 0;
            char key;


            while (true) {
                system("cls");
                int i = 0;
                for (auto it : wypozyczenia) {
                    cout << (wybor == i ? "> " : "  ") <<"ID: " << wypozyczenia[i].get_id() <<" -> "<<wypozyczenia[i].get_nazwa_sprzetu() <<", " << wypozyczenia[i].get_ilosc_sprzetu()<<" szt, koniec wypożyczenia: "<< wypozyczenia[i].get_koniec_wypozyczenia()<< "\n";
                    i++;
                }
                cout << endl;
                cout << (wybor == wypozyczenia.size() ? "> " : "  ") << "Wstecz" << "\n";
                cout << "=====================================\n";
                key = _getch();

                if (key == 72) wybor = (wybor + wypozyczenia.size()) % (wypozyczenia.size() + 1);
                else if (key == 80) wybor = (wybor + 1) % (wypozyczenia.size() + 1);
                else if (key == 13) { // Enter
                    if (wybor == wypozyczenia.size()) {
                        return;
                    }
                    else {
						cout << "Funkcja zakończenia wypożyczenia nie została jeszcze zaimplementowana."<<endl;
                        //zakoncz_wypozyczenie();
                        system("pause");
                    }

                }
            }

        }
        cout << "=================================" << endl;
	}
};




int main() {
    setlocale(LC_ALL, "polish");
    int wybor = 0;
    char key;

    Wypozyczalnia wypozyczalnia;

    while (true) {
        system("cls"); 
        cout << "=== WYPOŻYCZALNIA SPRZĘTU WODNEGO ===\n";
        cout << (wybor == 0 ? "> " : "  ") << "Wyświetl dostępne sprzęty\n";
        cout << (wybor == 1 ? "> " : "  ") << "Wypożycz sprzęt\n";
        cout << (wybor == 2 ? "> " : "  ") << "Zakończ wypożyczenie\n";
        cout << (wybor == 3 ? "> " : "  ") << "Cennik\n";
        cout << (wybor == 4 ? "> " : "  ") << "Edytuj sprzęty\n";
        cout << endl;
        cout << (wybor == 5 ? "> " : "  ") << "Wyjdź\n";
        cout << "=====================================\n";
        cout << endl;

        key = _getch();

        if (key == 72) wybor = (wybor + 5) % 6;
        else if (key == 80) wybor = (wybor + 1) % 6; 
        else if (key == 13) { // Enter
            switch (wybor) {
            case 0:
                wypozyczalnia.wyswietl_sprzety();
                cout << endl;
                system("pause");
                break;
            case 1:
				wypozyczalnia.wypozycz_sprzet();
				break;
            case 2:
                wypozyczalnia.wyswietl_wypozyczenia();
				system("pause");
                break;
            case 3:
				wypozyczalnia.wyswietl_cennik();
				system("pause");
                break;
            case 4:
                wypozyczalnia.wybierz_sprzet_do_edycji();
				break;
            case 5:
                cout << "Dziękujemy za skorzystanie z oprogramowania. Do zobaczenia!" << endl;
                wypozyczalnia.zapisz_stan();
				return 0;
            }
        }
    }
}