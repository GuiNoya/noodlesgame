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
        QRect rect; // Rectangle to draw image on
        QImage image; // Image to draw

    public:
        Item(int id, string name, string description, QRect rect = QRect(), string filename = "");
        int getId() const;
        string getName() const;
        string getDescription() const;
        QRect getRect() const;
        const QImage& getImage() const;
        string toString();
};

#endif /*ITEM_H_*/
