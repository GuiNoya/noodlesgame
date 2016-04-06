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

class Gateway; // Forward declaration to avoid cross reference

class Room {

    private:
        string name;
        vector<Item*> items;
        vector<Gateway*> gateways; // Gateways on the room
        vector<Room*> viewableRooms; // Rooms that are visible if the player is on the room
        bool visible = false; // If the room is visible
        QRect rect; // Rectangle to draw the image on
        QImage image; // Image to be draw
        map<string, QPoint> positions; // Pre-defined player's positions

    public:
        Room(string name, QRect rect, string filename);
        string toString();

        string getName() const;
        vector<Item*> getItems() const;
        vector<Room*> getViewableRooms() const;
        QRect getRect() const;
        const QImage& getImage() const;
        QPoint getPosition(string id);
        bool isVisible() const;
        void setName(string name);
        void setVisible(bool visible);

        void addGateway(Gateway* gateway);
        void addViewableRoom(Room* room);
        void addViewableRooms(initializer_list<Room*> rooms);
        void addPosition(string id, const QPoint& position);
        void addPosition(string id, const int x, const int y);

        void addItem(Item *item);
        void removeItem(Item *item);
        bool removeItem(int id);
        bool isItemInRoom(Item *item);
        bool isItemInRoom(int id);
        string displayItems();

        // operator<< used with an Item* indicates to add the item to the room
        Room* operator<<(Item* item) {
            if (!isItemInRoom(item)) {
                items.push_back(item);
            }
            return this;
        }

        // operator>> used with an Item* indicates to remove the item from the room
        Room* operator>>(Item* item) {
            FINDREMOVE(items, item);
            return this;
        }
};

#endif // ROOM_H_
