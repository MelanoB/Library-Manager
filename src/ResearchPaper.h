#pragma once
#include "LibraryItem.h"

    class ResearchPaper : public LibraryItem {

    private:
        std::string journal;
        std::string doi;

    public:

        ResearchPaper(int i,
            std::string t,
            std::string c,
            int y,
            bool a,
            std::string j,
            std::string d);

        void display() const override;
        std::string getType() const override;
        void saveToFile(std::ofstream& out) const override;
        double calculateLateFee(int overdueDays) const override;
    };


