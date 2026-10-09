#include "DVD.h"

using namespace std;

DVD::DVD(int i, string t, string c, int y, bool a, int d, string r): LibraryItem(i, t, c, y, a)
{
    duration = d;
    ageRating = r;
}

void DVD::display() const {

    cout << "\n[DVD]\n";

    cout << "ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Director: " << creator << endl;
    cout << "Year: " << publicationYear << endl;
    cout << "Duration: " << duration << " mins\n";
    cout << "Age Rating: " << ageRating << endl;

    cout << "Status: ";

    if (available)
        cout << "Available\n";
    else
        cout << "Borrowed\n";
}

string DVD::getType() const {
    return "DVD";
}

void DVD::saveToFile(ofstream& out) const {

    out << "DVD|"
        << id << "|"
        << title << "|"
        << creator << "|"
        << publicationYear << "|"
        << available << "|"
        << duration << "|"
        << ageRating << endl;
}

double DVD::calculateLateFee(int overdueDays) const {
    return overdueDays * 1.00;
}