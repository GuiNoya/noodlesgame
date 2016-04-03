#include "Item.h"

Item::Item(int id, string name, string description, QRect rect, string filename)
    : id(id), name(name), description(description), rect(rect), image(ASSET(filename)) {
}

int Item::getId() {
    return id;
}

string Item::getName() {
    return name;
}

string Item::getDescription() {
    return description;
}

QRect Item::getRect() {
    return rect;
}

QImage& Item::getImage() {
    return image;
}

string Item::toString() {
    string s = "<Item ID=";
    s += to_string(id);
    s += ", Name=" + name + ", Description=" + description;
    s += ">";
    return s;
}
