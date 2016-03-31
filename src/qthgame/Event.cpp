#include "Event.h"

#include <iostream>

Event::Event(int id, string message) : id(id), message(message) {
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

void Event::setMessage(string s) {
    message = s;
}

void Event::addOption(Option *option) {
    for (auto i = options.begin(); i != options.end(); i++) {
        if ((*i)->id == option->id) {
            return;
        }
    }
    options.push_back(option);
}

void Event::disableOption(int o) {
    Option* t = options.at(o);
    options.erase(options.begin() + o);
    disabledOptions[o] = t;
}

void Event::disableOption(Option* o) {
    int p = -1;
    for (auto i = options.begin(); i != options.end(); i++) {
        if (*i == o) {
            p = i - options.begin();
            options.erase(i);
            disabledOptions[p] = o;
            return;
        }
    }
    cout << "Option not removed! " << to_string(o->id) << " " << o->label << endl;
}

void Event::reenableOption(int i) {
    Option* o = disabledOptions.at(i);
    disabledOptions.erase(i);
    options.insert(options.begin() + i, o);
}

void Event::reenableOption(Option* o) {
    int p = -1;
    for (auto i = disabledOptions.begin(); i != disabledOptions.end(); i++) {
        if (i->second == o) {
            p = i->first;
            disabledOptions.erase(i);
            options.insert(options.begin() + p, o);
            return;
        }
    }
    cout << "Option not reenabled! " << to_string(o->id) << " " << o->label << endl;
}
