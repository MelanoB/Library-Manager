#pragma once
#include "LibraryItem.h"

    class DVD : public LibraryItem {

    private:
        int duration;
        std::string ageRating;

    public:

        DVD(int i, std::string t, std::string c, int y, bool a, int d, std::string r);

        void display() const override;
        std::string getType() const override;
        void saveToFile(std::ofstream& out) const override;
        double calculateLateFee(int overdueDays) const override;
};

