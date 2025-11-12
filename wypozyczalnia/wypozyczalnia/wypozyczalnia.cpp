#include <iostream>
#include <conio.h> // dla _getch()

int main() {
    setlocale(LC_ALL, "polish");
    int wybor = 0;
    char key;

    while (true) {
        system("cls"); // czyści konsolę
        std::cout << "=== MENU ===\n";
        std::cout << (wybor == 0 ? "> " : "  ") << "Opcja 1\n";
        std::cout << (wybor == 1 ? "> " : "  ") << "Opcja 2\n";
        std::cout << (wybor == 2 ? "> " : "  ") << "Opcja 3\n";

        key = _getch(); // odczytuje znak bez Entera

        if (key == 72) wybor = (wybor + 2) % 3; // strzałka w górę
        else if (key == 80) wybor = (wybor + 1) % 3; // strzałka w dół
        else if (key == 13) { // Enter
            std::cout << "Wybrano opcję " << (wybor + 1) << "!\n";
            system("pause");
            break;
        }
    }

    return 0;
}