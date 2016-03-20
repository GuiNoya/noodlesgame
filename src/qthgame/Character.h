#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Character {

    private:
        string description;
        vector<Item> inventory;

    public:
        Character(string description);
        string shortDescription();
        string longDescription();
        void addItems(string Item);

};

#endif /*CHARACTER_H_*/
