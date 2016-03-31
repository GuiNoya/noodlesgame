#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include <initializer_list>

#include <QImage>
#include <QRect>
#include <QPoint>
#include "Defines.h"

#include "Item.h"

using namespace std;

class Gateway;

class Room {

    private:
        string name;
        string description;
        vector<Item*> items;
        vector<Gateway*> gateways;
        vector<Room*> viewableRooms;
        QRect rect;
        QImage image;
        QPoint playerPosition;

    public:
        Room(string name, string description);
        Room(string name, string description, QRect rect, string filename, int x, int y);
        string toString();

        string getName();
        string getDescription();
        vector<Item*> getItems();
        vector<Room*> getViewableRooms();
        QRect getRect();
        QImage& getImage();
        QPoint getPlayerPosition();
        void setName(string name);
        void setDescription(string description);

        void addGateway(Gateway* gateway);
        void addViewableRoom(Room* room);
        void addViewableRooms(initializer_list<Room*> rooms);

        void addItem(Item *item);
        bool removeItem(Item *item);
        bool removeItem(int id);
        bool isItemInRoom(Item *item);
        bool isItemInRoom(int id);
        string displayItems();
        int numberOfItems();

};

#endif
