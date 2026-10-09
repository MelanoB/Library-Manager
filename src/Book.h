#pragma once
#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    int pages;
    std::string genre;

public:
    Book(int i, std::string t, std::string c, int y, bool a, int p, std::string g);

    void display() const override;
    std::string getType() const override;
    void saveToFile(std::ofstream& out) const override;
    double calculateLateFee(int overdueDays) const override;
};

