#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>

using namespace std;

class Item {

    private:
        int id;
        string name;
        string description;
        bool usable;

    public:
        Item(int id, string name, string description, bool usable=true);
        int getId();
        string getName();
        string getDescription();
        bool isUsable();
        void setUsable(bool usable);
        string toString();

};

#endif /*ITEM_H_*/
