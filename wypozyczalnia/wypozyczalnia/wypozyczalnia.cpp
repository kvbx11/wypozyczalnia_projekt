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
				cout << "Funkcja edytowania sprzętu w budowie." << endl;
                system("pause");
				break;
            case 5:
                cout << "Dziękujemy za skorzystanie z oprogramowania. Do zobaczenia!" << endl;
                wypozyczalnia.zapisz_stan();
				return 0;
            }
            

        }
    }
}