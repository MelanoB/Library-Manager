#include "Magazine.h"

using namespace std;

Magazine::Magazine(int i, string t, string c, int y,  bool a, int issue, string m): LibraryItem(i, t, c, y, a)
{
    issueNumber = issue;
    month = m;
}

void Magazine::display() const {

    cout << "\n[Magazine]\n";

    cout << "ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Publisher: " << creator << endl;
    cout << "Year: " << publicationYear << endl;
    cout << "Issue: " << issueNumber << endl;
    cout << "Month: " << month << endl;

    cout << "Status: ";

    if (available)
        cout << "Available\n";
    else
        cout << "Borrowed\n";
}

string Magazine::getType() const {
    return "Magazine";
}

void Magazine::saveToFile(ofstream& out) const {
    out << "Magazine|" << id << "|"<< title << "|" << creator << "|" << publicationYear << "|" << available << "|" << issueNumber << "|" << month << endl;
}

double Magazine::calculateLateFee(int overdueDays) const {
    return overdueDays * 0.30;
}