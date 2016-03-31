#include "Item.h"

Item::Item(int id, string name, string description, bool usable, QRect rect, string filename)
    : id(id), name(name), description(description), usable(usable), rect(rect), initialRect(rect), image(ASSET(filename)) {
}

Item::Item(int id, string name, string description, QRect rect, string filename, bool usable)
    : id(id), name(name), description(description), usable(usable), rect(rect), initialRect(rect), image(ASSET(filename)) {
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

bool Item::isUsable() {
    return usable;
}

void Item::setUsable(bool usable) {
    this->usable = usable;
}

void Item::setDrawableStatus(bool status) {
    if (status) {
        rect = initialRect;
    } else {
        rect.setHeight(0);
        rect.setWidth(0);
    }
}

string Item::toString() {
    string s = "<Item ID=";
    s += to_string(id);
    s += ", Name=" + name + ", Description=" + description + ", Usable=";
    s += usable ? "True" : "False";
    s += ">";
    return s;
}
