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

void Event::disableOption(int i) {
    Option* o = options.at(i);
    o->enabled = false;
}

void Event::enableOption(int i) {
    Option* o = options.at(i);
    o->enabled = true;
}

vector<Event::Option*> Event::getEnabledOptions(){
    vector<Option*> r;
    for (auto i: options){
        if (i->enabled)
            r.push_back(i);
    }
    return r;
}
