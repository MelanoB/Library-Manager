#pragma once
#include <vector>
#include <memory>

#include "LibraryItem.h"

// Single file used for both saving and loading.
inline constexpr const char* DATA_FILE = "library_data.txt";

class LibraryManager {

private:

    std::vector<std::unique_ptr<LibraryItem>> items;

public:

    void addItem();
    void displayAllItems() const;
    void borrowItem();
    void returnItem();
    void deleteItem();
    void searchItems() const;
    void sortByTitle();
    void sortByYear();
    void sortByType();
    void sortByAvailability();

    void saveItemsToFile() const;
    void loadItemsFromFile();
    void generateReport() const;
};

