#pragma once
#include <iostream>
#include <fstream>
#include <string>

class LibraryItem
{
    protected:
        int id;
        std::string title;
        std::string creator;
        int publicationYear;
        bool available;

    public:
        LibraryItem(int i, std::string t, std::string c, int y, bool a = true);
        virtual ~LibraryItem();
        virtual void display() const = 0;
        virtual std::string getType() const = 0;
        virtual void saveToFile(std::ofstream& out) const = 0;
        virtual double calculateLateFee(int overdueDays) const = 0;

        int getId() const;
        std::string getTitle() const;
        std::string getCreator() const;
        int getYear() const;
        bool isAvailable() const;
        void borrowItem();
        void returnItem();

        bool operator<(const LibraryItem& other) const;
        bool operator==(const LibraryItem& other) const;

        friend std::ostream& operator<<(std::ostream& out, const LibraryItem& item);
    };

