#include <iostream>
#include <stdexcept>
#include <string>
#include "LibraryManager.h"

using namespace std;

static void printMenu() {
    cout << "\n========== LIBRARY MENU ==========\n";
    cout << "1. Add Item\n";
    cout << "2. Display All Items\n";
    cout << "3. Search Items\n";
    cout << "4. Borrow Item\n";
    cout << "5. Return Item\n";
    cout << "6. Delete Item\n";

    cout << "\n----- SORTING -----\n";
    cout << "7. Sort By Title\n";
    cout << "8. Sort By Year\n";
    cout << "9. Sort By Type\n";
    cout << "10. Sort By Availability\n";

    cout << "\n----- FILES & REPORTS -----\n";
    cout << "11. Generate Report\n";
    cout << "12. Save To File\n";
    cout << "13. Load From File\n";

    cout << "\n0. Exit\n";
    cout << "\nEnter choice: ";
}

int main() {
    LibraryManager manager;
    int choice = -1;

    do {
        printMenu();

        string line;
        if (!getline(cin, line)) {   // end of input (Ctrl+D / Ctrl+Z)
            cout << "\nExiting program...\n";
            break;
        }

        try {
            size_t pos = 0;
            choice = stoi(line, &pos);
            if (pos != line.size())
                throw invalid_argument("trailing characters");
        }
        catch (const exception&) {
            cout << "\nInvalid option. Please enter a number from the menu.\n";
            choice = -1;
            continue;
        }

        try {
            switch (choice) {
            case 1:  manager.addItem();            break;
            case 2:  manager.displayAllItems();    break;
            case 3:  manager.searchItems();        break;
            case 4:  manager.borrowItem();         break;
            case 5:  manager.returnItem();         break;
            case 6:  manager.deleteItem();         break;
            case 7:  manager.sortByTitle();        break;
            case 8:  manager.sortByYear();         break;
            case 9:  manager.sortByType();         break;
            case 10: manager.sortByAvailability(); break;
            case 11: manager.generateReport();     break;
            case 12: manager.saveItemsToFile();    break;
            case 13: manager.loadItemsFromFile();  break;
            case 0:  cout << "\nExiting program...\n"; break;
            default: cout << "\nInvalid option.\n";
            }
        }
        catch (const exception& e) {
            cout << "\nError: " << e.what() << "\n";
            if (!cin) {              // input stream closed mid-operation
                cout << "Exiting program...\n";
                break;
            }
        }

    } while (choice != 0);

    return 0;
}
