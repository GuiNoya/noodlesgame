#include "Item.h"

Item::Item(int id, string name, string description, QRect rect, string filename)
    : id(id), name(name), description(description), rect(rect), image(ASSET(filename)) {
}

int Item::getId() const {
    return id;
}

string Item::getName() const {
    return name;
}

string Item::getDescription() const {
    return description;
}

QRect Item::getRect() const {
    return rect;
}

const QImage& Item::getImage() const {
    return image;
}

string Item::toString() {
    string s = "<Item ID=";
    s += to_string(id);
    s += ", Name=" + name + ", Description=" + description;
    s += ">";
    return s;
}
