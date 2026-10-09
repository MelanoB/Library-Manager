#include "LibraryItem.h"

using namespace std;

LibraryItem::LibraryItem(int i, string t, string c, int y, bool a) {
    id = i;
    title = t;
    creator = c;
    publicationYear = y;
    available = a;
}

LibraryItem::~LibraryItem() {
}

int LibraryItem::getId() const {
    return id;
}

string LibraryItem::getTitle() const {
    return title;
}

string LibraryItem::getCreator() const {
    return creator;
}

int LibraryItem::getYear() const {
    return publicationYear;
}

bool LibraryItem::isAvailable() const {
    return available;
}

void LibraryItem::borrowItem() {
    available = false;
}

void LibraryItem::returnItem() {
    available = true;
}

bool LibraryItem::operator<(const LibraryItem& other) const {
    return publicationYear < other.publicationYear;
}

bool LibraryItem::operator==(const LibraryItem& other) const {
    return id == other.id;
}

ostream& operator<<(ostream& out, const LibraryItem& item) {
    item.display();
    return out;
}