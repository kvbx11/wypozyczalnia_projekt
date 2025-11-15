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
    int ilosc;
    int dostepne;
    double cena;
public:
    Sprzet(string n, int il, double c){
        this->nazwa = n;
        this->ilosc = il;
        this->dostepne = this->ilosc;
        this->cena = c;
    }
};

class Wypozyczalnia {
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

    void wyswietl_sprzety() {
        cout<<""
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
            
            }
        }
    }

    return 0;
}