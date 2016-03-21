#include "Item.h"

Item::Item(string name, string description, int id, bool usable) : id(id), name(name), description(description), usable(usable) {
}

Item::Item(string name, string description) : id(0), name(name), description(description), usable(true) {
}

int Item::getId() {
    return 0;
}

string Item::getName() {
    return "";
}

string Item::getDescription() {
    return "";
}

bool Item::isUsable() {
    return true;
}

void Item::setUsable(bool usable) {
    this->usable = usable;
}

string Item::toString() {
    return "<Item>";
}
