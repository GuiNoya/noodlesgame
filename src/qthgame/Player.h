#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Player {

    private:
        string name;
        vector<Item*> inventory;

    public:
        Player(string name);
        string getName();
        void addItem(Item *item);
        void removeItem(Item* item);
        string toString();

};

#endif /*CHARACTER_H_*/
