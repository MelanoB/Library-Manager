#include "ResearchPaper.h"

using namespace std;
ResearchPaper::ResearchPaper(int i, string t, string c,int y, bool a, string j, string d): LibraryItem(i, t, c, y, a)
{
    journal = j;
    doi = d;
}

void ResearchPaper::display() const {

    cout << "\n[Research Paper]\n";

    cout << "ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << creator << endl;
    cout << "Year: " << publicationYear << endl;
    cout << "Journal: " << journal << endl;
    cout << "DOI: " << doi << endl;

    cout << "Status: ";

    if (available)
        cout << "Available\n";
    else
        cout << "Borrowed\n";
}

string ResearchPaper::getType() const {
    return "ResearchPaper";
}

void ResearchPaper::saveToFile(ofstream& out) const {

    out << "ResearchPaper|" << id << "|" << title << "|" << creator << "|"  << publicationYear << "|" << available << "|" << journal << "|" << doi << endl;
}

double ResearchPaper::calculateLateFee(int overdueDays) const {
    return overdueDays * 0.20;
}