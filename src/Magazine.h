#pragma once
#include "LibraryItem.h"
class Magazine : public LibraryItem {

private:
    int issueNumber;
    std::string month;

public:

    Magazine(int i, std::string t, std::string c, int y, bool a, int issue, std::string m);

    void display() const override;
    std::string getType() const override;
    void saveToFile(std::ofstream& out) const override;
    double calculateLateFee(int overdueDays) const override;
};

