#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <queue>
#include <functional>
#include <QImage>
#include <QTimer>
#include "Defines.h"

using namespace std;

class Character {
    protected:
        // AnimationStep is used for storing animations
        struct AnimationStep {
            const QPointF point;
            const int duration;
            const function<void()> callback;
            AnimationStep(const QPointF p, const int d, const function<void()>& c) : point(p), duration(d), callback(c) {}
        };

        string name;
        QRectF rect; // The position and size that image will be displayed
        QImage image; // The image to be displayed
        QPointF direction; // The vector to the next destination of the current animation
        QPointF dest; // The destination point of the current animation
        queue<AnimationStep*> nextSteps; // The next animations
        function<void()> animCallback = 0; // The callback to be run after the end of the current animation
        bool moving; // Indicates if the player is in processing an animation
        bool waiting; // Indicates if the actual animation is to stay
        static const int CHARACTER_HEIGHT = 30;
        static const int CHARACTER_WIDTH = 30;

    public:
        Character(string name, int x, int y, string filename);
        ~Character();
        string getName() const;
        QRectF getRect() const;
        const QImage& getImage() const;
        bool isMoving() const;
        void setPosition(int x, int y);
        void setPosition(const QPointF point);
        void addAnimation(const QPointF dest, int duration, const function<void()>& c=0);
        void addSleepAnimation(int duration, const function<void()>& c=0);
        virtual bool update(); // Function to run inside the main loop, that will mainly update the player's position
        virtual string toString();
};

#endif // CHARACTER_H
