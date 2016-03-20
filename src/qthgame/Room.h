#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "Gateway.h"
#include "Item.h"

using namespace std;

class Room {

    private:
        string name;
        string description;
        vector<Gateway*> gateways;
        vector<Item> items;

    public:
        Room(string name, string description);
        string toString();

        // Getters and Setters
        string getName();
        string getDescription();
        void setName(string name);
        void setDescription(string description);

        // Room related
        void addGateway(Gateway* gateway);
        vector<Gateway*> getGateways();

        // Item related
        void addItem(Item *item);
        bool removeItem(Item *item);
        bool removeItem(int id);
        bool isItemInRoom(Item *item);
        bool isItemInRoom(int id);
        string displayItems();
        int numberOfItems();

}

#endif
