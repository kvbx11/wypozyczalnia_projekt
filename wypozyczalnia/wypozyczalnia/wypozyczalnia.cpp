#include <iostream>
#include <conio.h> // dla _getch()
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Sprzet {
private:
    string nazwa;
    int ilosc; // stan poczatkowy
    int dostepne; // stan aktualny
    double cena;
public:
    Sprzet(string n, int il, double c){
        this->nazwa = n;
        this->ilosc = il;
        this->dostepne = this->ilosc;
        this->cena = c;
    }

    string get_nazwa() {
        return nazwa;
	}
    int get_ilosc() {
        return ilosc;
	}
    int get_dostepne() {
        return dostepne;
    }
    double get_cena() {
        return cena;
    }
    void set_nazwa(string n) {
        this->nazwa = n;
    }
    void set_ilosc(int i) {
        this->ilosc = i;
    }
    void set_cena(double c) {
        this->cena = c;
    }
};

class Wypozyczalnia{
private:
    vector<Sprzet>sprzety;
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
                plik << it.get_nazwa() << " " << it.get_dostepne() << " " << it.get_cena() << endl;
            }
        }
        else {
            cout << "Błąd zapisu do pliku!" << endl;
        }
	}

    void wyswietl_sprzety() {
        cout << "SPRZĘT DOSTĘPNY W NASZEJ WYPOŻYCZALNI" << endl;
		for (auto it : sprzety) {
            cout <<" > " << it.get_nazwa() << ", dostępna ilość: " << it.get_dostepne() << endl;
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
            cout << (wybor == 0 ? "> " : "  ") << sprzety[idx].get_nazwa() << "\n";
            cout << (wybor == 1 ? "> " : "  ") << sprzety[idx].get_ilosc() << "\n";
            cout << (wybor == 2 ? "> " : "  ") << sprzety[idx].get_cena() << "\n";
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
                cout << "Funkcja wypożyczania sprzętu w budowie." << endl;
                system("pause");
				break;
            case 2:
                cout << "Funkcja zakończenia wypożyczenia w budowie." << endl;
				system("pause");
                break;
            case 3:
				wypozyczalnia.wyswietl_cennik();
				system("pause");
                break;
            case 4:
                wypozyczalnia.wybierz_sprzet_do_edycji();
                //system("pause");
				break;
            case 5:
                cout << "Dziękujemy za skorzystanie z oprogramowania. Do zobaczenia!" << endl;
                wypozyczalnia.zapisz_stan();
				return 0;
            }
        }
    }
}