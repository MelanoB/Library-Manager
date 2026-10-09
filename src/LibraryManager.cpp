#include "LibraryManager.h"
#include "Book.h"
#include "Magazine.h"
#include "DVD.h"
#include "ResearchPaper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <stdexcept>

using namespace std;


//case insensitive
static string toLowerCase(string text) {

    for (char& c : text) {

        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    return text;
}

// ---------- Input helpers ----------
// All input is read line-by-line with getline, so no stray newlines are
// left in the buffer and every invalid input becomes a catchable exception.
static string readLine(const string& prompt) {
    cout << prompt;
    string value;
    if (!getline(cin, value))
        throw runtime_error("Input stream closed.");
    return value;
}

static string readNonEmpty(const string& prompt) {
    string value = readLine(prompt);
    if (value.empty())
        throw runtime_error("Input cannot be empty.");
    return value;
}

static int readInt(const string& prompt) {
    string text = readLine(prompt);
    try {
        size_t pos = 0;
        int value = stoi(text, &pos);
        if (pos != text.size())
            throw invalid_argument("trailing characters");
        return value;
    }
    catch (const exception&) {
        throw runtime_error("Invalid input: expected a whole number.");
    }
}

static int readPositiveInt(const string& prompt) {
    int value = readInt(prompt);
    if (value <= 0)
        throw runtime_error("Value must be a positive number.");
    return value;
}

static int readNonNegativeInt(const string& prompt) {
    int value = readInt(prompt);
    if (value < 0)
        throw runtime_error("Value cannot be negative.");
    return value;
}

static int currentYear() {
    time_t now = time(nullptr);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif
    return local.tm_year + 1900;
}

static void validateYear(int year) {
    const int maxYear = currentYear();
    if (year < 1450 || year > maxYear)
        throw runtime_error("Publication year must be between 1450 and " +
                            to_string(maxYear) + ".");
}


//add
void LibraryManager::addItem() {
    cout << "\nChoose Item Type:\n";
    cout << "1. Book\n";
    cout << "2. Magazine\n";
    cout << "3. DVD\n";
    cout << "4. Research Paper\n";

    int choice = readInt("Enter type: ");
    if (choice < 1 || choice > 4) {
        cout << "Invalid choice.\n";
        return;
    }

    // ID: must be positive and unique
    int id = readPositiveInt("Enter ID: ");
    for (const auto& item : items) {
        if (item->getId() == id)
            throw runtime_error("Duplicate ID detected.");
    }

    string title = readNonEmpty("Enter Title: ");
    string creator = readNonEmpty("Enter Creator: ");
    int year = readPositiveInt("Enter Publication Year: ");
    validateYear(year);

    // book
    if (choice == 1) {

        int pages = readPositiveInt("Enter Pages: ");
        string genre = readNonEmpty("Enter Genre: ");

        items.push_back(
            make_unique<Book>(id, title, creator, year, true, pages, genre)
        );
    }

    // magazine
    else if (choice == 2) {

        int issue = readPositiveInt("Enter Issue Number: ");
        string month = readNonEmpty("Enter Month: ");

        items.push_back(
            make_unique<Magazine>(id, title, creator, year, true, issue, month)
        );
    }

    // DVD
    else if (choice == 3) {

        int duration = readPositiveInt("Enter Duration: ");
        string rating = readNonEmpty("Enter Age Rating: ");

        items.push_back(
            make_unique<DVD>(id, title, creator, year, true, duration, rating)
        );
    }

    // research paper
    else if (choice == 4) {

        string journal = readNonEmpty("Enter Journal: ");
        string doi = readNonEmpty("Enter DOI: ");   // DOI cannot be empty

        items.push_back(
            make_unique<ResearchPaper>(id, title, creator, year, true, journal, doi)
        );
    }

    else {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "\nItem added successfully.\n";
}

//display
void LibraryManager::displayAllItems() const {

    if (items.empty()) {

        cout << "\nNo items in library.\n";
        return;
    }

    for (const auto& item : items) {

        item->display();

        cout << "-------------------\n";
    }
}


//borrow
void LibraryManager::borrowItem() {

    int id = readPositiveInt("Enter ID to borrow: ");

    for (auto& item : items) {

        if (item->getId() == id) {

            if (!item->isAvailable()) {
                throw runtime_error("Item already borrowed.");
            }

            item->borrowItem();

            cout << "\nItem borrowed successfully.\n";

            return;
        }
    }

    throw runtime_error("Item not found.");
}

//return
void LibraryManager::returnItem() {

    int id = readPositiveInt("Enter ID to return: ");

    for (auto& item : items) {

        if (item->getId() == id) {

            if (item->isAvailable()) {
                throw runtime_error("Item was not borrowed.");
            }

            int overdueDays = readNonNegativeInt("Enter overdue days: ");

            double fee =
                item->calculateLateFee(overdueDays);

            item->returnItem();

            cout << "\nItem returned successfully.\n";

            cout << "Late Fee: "
                << fee
                << " GEL\n";
            return;
        }
    }

    throw runtime_error("Item not found.");
}

//delete
void LibraryManager::deleteItem() {

    if (items.empty()) {
        cout << "\nLibrary is empty.\n";
        return;
    }

    int id = readPositiveInt("Enter ID to delete: ");

    for (auto it = items.begin(); it != items.end(); it++) {

        if ((*it)->getId() == id) {
            items.erase(it);
            cout << "\nItem deleted successfully.\n";
            return;
        }
    }

    throw runtime_error("Item not found.");
}

//search by term
void LibraryManager::searchItems() const {
    if (items.empty()) {
        cout << "\nLibrary is empty.\n";
        return;
    }

    string search = readNonEmpty("\nEnter search term: ");

    bool found = false;

    for (const auto& item : items) {

        bool match = false;
        try {

            int number = stoi(search);

            if (item->getId() == number ||
                item->getYear() == number) {

                match = true;
            }

        }
        catch (...) {

    
        }

        if (toLowerCase(item->getTitle()).find(toLowerCase(search)) != string::npos) {
            match = true;
        }
        if (toLowerCase(item->getCreator()).find(toLowerCase(search)) != string::npos) {
            match = true;
        }
        if (toLowerCase(item->getType()).find(toLowerCase(search)) != string::npos) {
            match = true;
        }

        if (match) {
            item->display();
            cout << "-------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo matching items found.\n";
    }
}

//save to file
void LibraryManager::saveItemsToFile() const {
    ofstream fout(DATA_FILE);
    if (!fout) {
        throw runtime_error("File could not be opened.");
    }

    for (auto& item : items) {

        item->saveToFile(fout);
    }
    fout.close();
    cout << "\nItems saved successfully.\n";
}


//load from file
void LibraryManager::loadItemsFromFile() {
    ifstream fin(DATA_FILE);
    if (!fin) {
        throw runtime_error(string("Could not open ") + DATA_FILE +
                            ". Save some items first, or run from the folder containing it.");
    }
    items.clear();
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> data;
        string field;
        while (getline(ss, field, '|')) {
            data.push_back(field);
        }
        if (data.empty())
            continue;
        try {
            if (data[0] == "Book" && data.size() == 8) {
                items.push_back(
                    make_unique<Book>(stoi(data[1]), data[2], data[3], stoi(data[4]), stoi(data[5]), stoi(data[6]), data[7])
                );
            }
            else if (data[0] == "Magazine" && data.size() == 8) {
                items.push_back(
                    make_unique<Magazine>(stoi(data[1]), data[2], data[3], stoi(data[4]), stoi(data[5]), stoi(data[6]), data[7])
                );
            }
            else if (data[0] == "DVD" && data.size() == 8) {

                items.push_back(
                    make_unique<DVD>(stoi(data[1]), data[2], data[3], stoi(data[4]), stoi(data[5]), stoi(data[6]), data[7])
                );
            }

            else if (data[0] == "ResearchPaper"
                && data.size() == 8) {

                items.push_back(
                    make_unique<ResearchPaper>(stoi(data[1]), data[2], data[3], stoi(data[4]), stoi(data[5]), data[6], data[7])
                );
            }

            else {
                cout << "Invalid record skipped.\n";
                continue;
            }
        }

        catch (...) {

            cout << "Corrupted record skipped.\n";
        }
    }

    fin.close();

    cout << "\nFile loaded successfully " << endl;
}

//sorts

void LibraryManager::sortByTitle() {
    sort(items.begin(), items.end(), [](const unique_ptr<LibraryItem>& a, const unique_ptr<LibraryItem>& b) {
        return a->getTitle() < b->getTitle();
        });
    cout << "\nSorted by title.\n";
}
void LibraryManager::sortByYear() {
    sort(items.begin(), items.end(), [](const unique_ptr<LibraryItem>& a, const unique_ptr<LibraryItem>& b) {
        return a->getYear() < b->getYear();
        });
    cout << "\nSorted by year.\n";
}
void LibraryManager::sortByType() {
    sort(items.begin(), items.end(), [](const unique_ptr<LibraryItem>& a, const unique_ptr<LibraryItem>& b) {
        return a->getType() < b->getType();
        });
    cout << "\nSorted by type.\n";
}
void LibraryManager::sortByAvailability() {
    sort(items.begin(), items.end(), [](const unique_ptr<LibraryItem>& a, const unique_ptr<LibraryItem>& b) {
        return a->isAvailable() > b->isAvailable();
        });
    cout << "\nSorted by availability.\n";
}

//generate report
void LibraryManager::generateReport() const {
    cout << "\n===== LIBRARY REPORT =====\n";
    cout << "Total Items: " << items.size() << endl;
    int availableCount = 0;
    int borrowedCount = 0;
    int books = 0;
    int magazines = 0;
    int dvds = 0;
    int papers = 0;
    for (const auto& item : items) {
        if (item->isAvailable())
            availableCount++;
        else
            borrowedCount++;
        if (item->getType() == "Book")
            books++;
        else if (item->getType() == "Magazine")
            magazines++;
        else if (item->getType() == "DVD")
            dvds++;
        else if (item->getType() == "ResearchPaper")
            papers++;
    }

    cout << "Available Items: " << availableCount << endl;

    cout << "Borrowed Items: " << borrowedCount << endl;

    cout << "\nBooks: " << books << endl;
    cout << "Magazines: " << magazines << endl;
    cout << "DVDs: " << dvds << endl;
    cout << "Research Papers: " << papers << endl;

    if (!items.empty()) {
        auto oldest =
            min_element(items.begin(), items.end(), [](const unique_ptr<LibraryItem>& a, const unique_ptr<LibraryItem>& b) {
            return a->getYear() < b->getYear();
                });

        auto newest =
            max_element(items.begin(), items.end(), [](const unique_ptr<LibraryItem>& a, const unique_ptr<LibraryItem>& b) {
            return a->getYear() < b->getYear();
                });

        cout << "\nOldest Item:\n";
        (*oldest)->display();

        cout << "\nNewest Item:\n";
        (*newest)->display();
    }
}