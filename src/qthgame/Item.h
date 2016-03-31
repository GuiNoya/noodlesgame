#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>

#include <QImage>
#include <QRect>
#include "Defines.h"

using namespace std;

class Item {

    private:
        int id;
        string name;
        string description;
        bool usable;
        QRect rect;
        QRect initialRect;
        QImage image;

    public:
        Item(int id, string name, string description, bool usable=true, QRect rect = QRect(), string filename = "");
        Item(int id, string name, string description, QRect rect, string filename, bool usable=true);
        int getId();
        string getName();
        string getDescription();
        QRect getRect();
        QImage& getImage();
        bool isUsable();
        void setUsable(bool usable);
        void setDrawableStatus(bool status);
        string toString();

};

#endif /*ITEM_H_*/
