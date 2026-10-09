#include "Book.h"

using namespace std;
Book::Book(int i, string t, string c, int y, bool a, int p, string g) : LibraryItem(i, t, c, y, a)
{
    pages = p;
    genre = g;
}

void Book::display() const {

    cout << "\n[Book]\n";

    cout << "ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << creator << endl;
    cout << "Year: " << publicationYear << endl;
    cout << "Pages: " << pages << endl;
    cout << "Genre: " << genre << endl;

    cout << "Status: ";

    if (available)
        cout << "Available\n";
    else
        cout << "Borrowed\n";
}

string Book::getType() const {
    return "Book";
}

void Book::saveToFile(ofstream& out) const {

    out << "Book|" << id << "|" << title << "|" << creator << "|" << publicationYear << "|" << available << "|" << pages << "|" << genre << endl;
}

double Book::calculateLateFee(int overdueDays) const {
    return overdueDays * 0.50;
}