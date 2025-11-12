#include <iostream>
#include <conio.h> // dla _getch()

int main() {
    setlocale(LC_ALL, "polish");
    int wybor = 0;
    char key;

    while (true) {
        system("cls"); 
        std::cout << "=== WYPOŻYCZALNIA SPRZĘTU WODNEGO ===\n";
        std::cout << (wybor == 0 ? "> " : "  ") << "Wyświetl dostępne sprzęty\n";
        std::cout << (wybor == 1 ? "> " : "  ") << "Wypożycz sprzęt\n";
        std::cout << (wybor == 2 ? "> " : "  ") << "Zakończ wypożyczenie\n";
        std::cout << (wybor == 3 ? "> " : "  ") << "Cennik\n";
        std::cout << (wybor == 4 ? "> " : "  ") << "Edytuj sprzęty\n";
        std::cout << (wybor == 5 ? "> " : "  ") << "Wyjdź\n";
        std::cout << "=====================================\n";


        key = _getch();

        if (key == 72) wybor = (wybor + 5) % 6;
        else if (key == 80) wybor = (wybor + 1) % 6; 
        else if (key == 13) { // Enter
            std::cout << "Wybrano opcję " << (wybor + 1) << "!\n";
            system("pause");
        }
    }

    return 0;
}