#include "Item.h"
#include <string>

Item::Item(int id, string name, string description, bool usable)
    : id(id), name(name), description(description), usable(usable) {
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

bool Item::isUsable() {
    return usable;
}

void Item::setUsable(bool usable) {
    this->usable = usable;
}

string Item::toString() {
    string s = "<Item ID=";
    s += to_string(id);
    s += ", Name=" + name + ", Description=" + description + ", Usable=";
    s += usable ? "True" : "False";
    s += ">";
    return s;
}
