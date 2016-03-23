#include "Event.h"

Event::Event(string message) : message(message) {
}

Event::~Event() {
    for (auto i = options.begin(); i != options.end(); i++) {
        delete (*i);
    }
}

string Event::getMessage() {
    return message;
}

vector<Event::Option*> Event::getOptions() {
    return options;
}

void Event::addOption(Option *option) {
    for (auto i = options.begin(); i != options.end(); i++) {
        if ((*i)->id == option->id) {
            return;
        }
    }
    options.push_back(option);
}
