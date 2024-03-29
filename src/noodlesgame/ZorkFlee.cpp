#include "ZorkFlee.h"

#define ROOM(x) rooms[x-1] // Easier access to rooms
#define CORR(x) rooms[6+x] // Easier access to corridors
#define _SE showingEvent =

using namespace std;

ZorkFlee::ZorkFlee(QWidget *parent) :
        QMainWindow(parent), player("Main Character", 0, 0, "player.png"), enemy("Player's Enemy", 0, 0, "enemy.png"),
        gameLogo(ASSET((string)"game.png")) {

    createGame();

    setWindowTitle(QString::fromUtf8("FLEE (if you can)"));
    setStyleSheet("background-color:black;");
    setFixedSize(1100, 600);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(ANIMATION_DELAY);
}

ZorkFlee::~ZorkFlee() {
    for (vector<Room*>::iterator i = rooms.begin(); i != rooms.end(); ++i) {
        delete (*i);
    }
    for (auto i = gateways.begin(); i != gateways.end(); ++i) {
        delete (*i);
    }
    for (map<int, Event*>::iterator i = events.begin(); i != events.end(); ++i) {
        delete i->second;
    }
    for (auto i = items.begin(); i != items.end(); ++i) {
        delete i->second;
    }

    delete timer;
}

void ZorkFlee::createGame() {
    createRooms();
    createEvents();
    createItems();

    enemy.addPosition("initial", ROOM(5), QPoint(214, 167));
    enemy.addPosition("playerhides1", ROOM(5), QPoint(314, 167));
    enemy.addPosition("playerhides2", CORR(4), QPoint(8, 25));
    enemy.addPosition("playerhides3", CORR(2), QPoint(5, 45));
    enemy.addPosition("playerhides4", ROOM(4), QPoint(170, 205));
    enemy.addPosition("playerstays1", ROOM(5), QPoint(314, 167));
    enemy.addPosition("playerstays2", CORR(4), QPoint(8, 25));
    enemy.addPosition("playerstays3", CORR(3), QPoint(10, 25));
    enemy.addPosition("playerstaysfight", CORR(3), QPoint(10, 100));
    enemy.addPosition("playerstayspipe", CORR(3), QPoint(10, 130));
    enemy.addPosition("playerstaysrun", CORR(1), QPoint(10, 35));
    enemy.addPosition("enemyreturned", ROOM(5), QPoint(214, 167));
    enemy.addPosition("playerinroom5", CORR(4), QPoint(8, 0));

    currentRoom = ROOM(1);
    _SE events[1];
    player.setPosition(currentRoom->getPosition("initial"));
    enemy.setPosition(enemy.getPosition("initial"));
}

void ZorkFlee::createRooms() {
    Room *r1, *r2, *r3, *r4, *r5, *r6, *r7;
    Room *c1, *c2, *c3, *c4, *c5, *c6, *c7;

    r1 = new Room("Cell", QRect(548, 0, 103, 210), "R1.png");
    r2 = new Room("Cell office", QRect(400, 0, 148, 210), "R2.png");
    r3 = new Room("Dark Room", QRect(400, 210, 251, 115), "R3.png");
    r4 = new Room("Storage Room", QRect(129, 0, 222, 325), "R4.png");
    r5 = new Room("Surgical Room", QRect(0, 325, 351, 275), "R5.png");
    r6 = new Room("Boxes Room", QRect(400, 325, 400, 226), "R6.png");
    r7 = new Room("Courtyard", QRect(651, 0, 149, 325), "R7.png");
    c1 = new Room("Initial Corridor", QRect(351, 0, 49, 161), "C1.png");
    c2 = new Room("Second Corridor", QRect(351, 161, 49, 164), "C2.png");
    c3 = new Room("Third Corridor", QRect(351, 325, 49, 141), "C3.png");
    c4 = new Room("Corridor Corner", QRect(351, 466, 49, 134), "C4.png");
    c5 = new Room("First Corridor on the Right", QRect(400, 551, 141, 49), "C5.png");
    c6 = new Room("Middle Corridor on the Right", QRect(541, 551, 129, 49), "C6.png");
    c7 = new Room("Last Corridor", QRect(670, 551, 130, 49), "C7.png");

    r1->addPosition("initial", 56, 145);
    r1->addPosition("window", 67, 62);
    r1->addPosition("toilet", 42, 44);
    r1->addPosition("bed", 18, 154);
    r1->addPosition("bars", 8, 88);
    r2->addPosition("initial", 108, 88);
    r2->addPosition("water", 43, 10);
    r2->addPosition("table", 81, 151);
    r2->addPosition("door", 6, 65);
    r3->addPosition("initial", 6, 47);
    r3->addPosition("middle", 70, 47);
    r3->addPosition("table", 77, 71);
    r3->addPosition("debris", 176, 67);
    r3->addPosition("tarp", 217, 78);
    r3->addPosition("p1", 50, 85);
    r3->addPosition("p2", 80, 15);
    r4->addPosition("initial", 183, 206);
    r4->addPosition("sink", 127, 245);
    r4->addPosition("flashlight", 81, 286);
    r4->addPosition("cabinet", 134, 135);
    r4->addPosition("freezer", 64, 165);
    r5->addPosition("initial", 313, 163);
    r5->addPosition("desk", 292, 188);
    r5->addPosition("sink", 259, 70);
    r5->addPosition("stretcher", 200, 130);
    r5->addPosition("garbage", 81, 207);
    r5->addPosition("table", 30, 124);
    r6->addPosition("initial", 178, 169);
    r6->addPosition("walkaround1", 91, 136);
    r6->addPosition("walkaround2", 278, 128);
    r6->addPosition("bulletinboard", 172, 65);
    r6->addPosition("passcode", 152, 10);
    r7->addPosition("initial", 1, 268);
    r7->addPosition("p1", 58, 239);
    r7->addPosition("p2", 60, -30);
    c1->addPosition("initial", 15, 65);
    c1->addPosition("plant", 9, 30);
    c1->addPosition("default", 10, 80);
    c2->addPosition("initial", 10, 66);
    c2->addPosition("leftdoor", 3, 44);
    c2->addPosition("rightdoor", 16, 95);
    c3->addPosition("initial", 10, 75);
    c3->addPosition("window", 10, 101);
    c4->addPosition("initial", 10, 40);
    c4->addPosition("door", 4, 26);
    c4->addPosition("corner", 10, 93);
    c5->addPosition("initial", 85, 8);
    c5->addPosition("default", 45, 8);
    c6->addPosition("initial", 50, 8);
    c6->addPosition("door", 39, 4);
    c6->addPosition("window", 107, 14);
    c7->addPosition("initial", 91, 9);

    rooms.push_back(r1);
    rooms.push_back(r2);
    rooms.push_back(r3);
    rooms.push_back(r4);
    rooms.push_back(r5);
    rooms.push_back(r6);
    rooms.push_back(r7);
    rooms.push_back(c1);
    rooms.push_back(c2);
    rooms.push_back(c3);
    rooms.push_back(c4);
    rooms.push_back(c5);
    rooms.push_back(c6);
    rooms.push_back(c7);

    createGateway(0, r1, r2, true);
    createGateway(1, r2, c1, false);
    createGateway(2, c1, c2, false);
    createGateway(3, c2, r3, false);
    createGateway(4, r3, r7, true);
    createGateway(5, c2, r4, true);
    createGateway(6, c2, c3, false);
    createGateway(7, c3, c4, false);
    createGateway(8, c4, r5, false);
    createGateway(9, c4, c5, false);
    createGateway(10, c5, c6, false);
    createGateway(11, c6, c7, false);
    createGateway(12, c6, r6, true);

    r1->addViewableRoom(r2);
    r2->addViewableRoom(r1);
    c1->addViewableRooms({c2, c3, c4});
    c2->addViewableRooms({c1, c3, c4});
    c3->addViewableRooms({c1, c2, c4});
    c4->addViewableRooms({c1, c2, c3, c5, c6, c7});
    c5->addViewableRooms({c4, c6, c7});
    c6->addViewableRooms({c4, c5, c7});
    c7->addViewableRooms({c4, c5, c6});
}

void ZorkFlee::createEvents() {
    EVENT(1, "You feel your head pounding and slowly open your eyes.\n"
            "You sit up and look around. You were lying in a metal bed. "
            "There is a toilet on the other side of the room and a boarded window on the wall. There are iron bars in front of you.\n"
            "You realize you are in some kind of a cell, but you have no idea how you ended up there.\n"
            "What do you want to do?",
        {
        OPTION(2, "Go back to sleep"),
        OPTION(3, "Check the window"),
        OPTION(4, "Check the toilet"),
        OPTION(5, "Check the bars")
        }
    );

    EVENT(2, "Seriously? \n"
          "You try to sleep but the bed is too uncomfortable. What do you want to do?",
        {
        OPTION(2, "Go back to sleep"),
        OPTION(3, "Check the window"),
        OPTION(4, "Check the toilet"),
        OPTION(5, "Check the bars")
        }
    );

    EVENT(3, "You go to the window. The boards cover the space completely; you cannot see anything outside.",
        {
        OPTION(6, "Try to remove boards"),
        OPTION(7, "Check the bed"),
        OPTION(4, "Check the toilet"),
        OPTION(5, "Check the bars")
        }
    );

    EVENT(4, "It is just a normal, dirty toilet.",
        {
        OPTION(100, "Pee"),
        OPTION(7, "Check the bed"),
        OPTION(3, "Check the window"),
        OPTION(5, "Check the bars")
        }
    );

    EVENT(5, "You try to open the cell door, but it is locked. You are getting nervous. What do you do?",
        {
        OPTION(8, "Kick the bars"),
        OPTION(7, "Check the bed"),
        OPTION(4, "Check the toilet"),
        OPTION(3, "Check the window")
        }
    );

    EVENT(6, "The boards are nailed to the wall. You cannot pry them open with your bare hands.",
        {
        OPTION(7, "Check the bed"),
        OPTION(4, "Check the toilet"),
        OPTION(5, "Check the bars")
        }
    );

    EVENT(7, "It is just a rusty metal bed, with an old mattress.",
        {
        OPTION(3, "Check the window"),
        OPTION(4, "Check the toilet"),
        OPTION(5, "Check the bars")
        }
    );

    EVENT(8, "Out of frustration, you kick the cell bars. You hear the sound of metal shaking.",
        {
        OPTION(9, "Kick again"),
        OPTION(3, "Check the window"),
        OPTION(4, "Check the toilet"),
        OPTION(7, "Check the bed")
        }
    );

    EVENT(9, "You hear the sound again. Maybe there is a loosened bar.",
        {
        OPTION(10, "Inspect bars"),
        OPTION(3, "Check the window"),
        OPTION(4, "Check the toilet"),
        OPTION(7, "Check the bed")
        }
    );

    EVENT(10, "You find the loose bar. If you draw it out, maybe you can slip through the gap.",
        {
        OPTION(11, "Try to remove bar"),
        OPTION(3, "Check the window"),
        OPTION(4, "Check the toilet"),
        OPTION(7, "Check the bed")
        }
    );

    EVENT(11, "Yey, you removed the bar.\n"
              "With great effort, you slip through the bars and get out of the cell.\n"
              "You are now in the adjacent room, where you see a water dispenser, a wooden table and a chair. There is also a door.",
        {
        OPTION(12, "Check the water dispenser"),
        OPTION(13, "Check the table"),
        OPTION(14, "Check the chair"),
        OPTION(15, "Check the door")
        }
    );

    EVENT(12, "There is no water in the gallon.",
        {
        OPTION(13, "Check the table"),
        OPTION(14, "Check the chair"),
        OPTION(15, "Check the door")
        }
    );

    EVENT(13, "There is just dust on it. Same on the chair.",
        {
        OPTION(12, "Check the water dispenser"),
        OPTION(15, "Check the door")
        }
    );

    EVENT(14, "There is just dust on it. Same on the table.",
        {
        OPTION(12, "Check the water dispenser"),
        OPTION(15, "Check the door")
        }
    );

    EVENT(15, "You go to the door and pull the knob. The door opens.\n"
              "You are now in a corridor. On your right, there is a window and a plant. What do you do?",
        {
        OPTION(16, "Check the window"),
        OPTION(17, "Check the plant"),
        OPTION(24, "Check the plant"),
        OPTION(18, "Go back to the room"),
        OPTION(19, "Continue down the hall")
        }
    );

    EVENT(16, "The glass is too thick, you cannot see any detail outside, only the sun light.",
        {
        OPTION(17, "Check the plant"),
        OPTION(24, "Check the plant"),
        OPTION(18, "Go back to the room"),
        OPTION(19, "Continue down the hall")
        }
    );

    EVENT(17, "You get closer to the plant and see a broken pipe behind it, against the wall.",
        {
        OPTION(20, "Grab pipe"),
        OPTION(16, "Check the window"),
        OPTION(18, "Go back to the room"),
        OPTION(19, "Continue down the hall")
        }
    );

    EVENT(18, "You are back to the adjacent room to the cell. What are you going to do?",
        {
        OPTION(12, "Check the water dispenser"),
        OPTION(13, "Check the table"),
        OPTION(14, "Check the chair"),
        OPTION(21, "Go back to the corridor")
        }
    );

    EVENT(19, "You keep walking and you see two doors, one on each side of the corridor.",
        {
        OPTION(22, "Check door on the right"),
        OPTION(23, "Check door on the left"),
        OPTION(30, "Check door on the left"),
        OPTION(69, "Check door on the left"),
        OPTION(21, "Go back"),
        OPTION(26, "Continue down the hall"),
        OPTION(31, "Continue down the hall"),
        OPTION(38, "Continue down the hall")
        }
    );

    EVENT(20, "You now have a broken pipe. Cool.",
        {
        OPTION(16, "Check the window"),
        OPTION(18, "Go back to the room"),
        OPTION(19, "Continue down the hall")
        }
    );

    EVENT(21, "You are back to the beginning of the corridor.",
        {
        OPTION(16, "Check the window"),
        OPTION(17, "Check the plant"),
        OPTION(24, "Check the plant"),
        OPTION(18, "Go back to the cell room"),
        OPTION(19, "Continue down the hall")
        }
    );

    EVENT(22, "The door is unlocked. You open it. It is too dark inside the room so you see nothing.",
        {
        OPTION(25, "Enter room"),
        OPTION(82, "Enter room"),
        OPTION(23, "Check door on the left"),
        OPTION(30, "Check door on the left"),
        OPTION(69, "Check door on the left"),
        OPTION(21, "Go back"),
        OPTION(26, "Continue down the hall"),
        OPTION(38, "Continue down the hall")
        }
    );

    EVENT(23, "You try the door, but it is locked."
              "On the wall, besides it, you see a digital lock. You try the passcode \"1234\", but it does not work.",
        {
        OPTION(22, "Check door on the right"),
        OPTION(21, "Go back on the corridor"),
        OPTION(26, "Continue down the hall"),
        }
    );

    EVENT(24, "The plant is doing photosynthesis.",
        {
        OPTION(16, "Check the window"),
        OPTION(18, "Go back to the room"),
        OPTION(19, "Continue down the hall")
        }
    );

    EVENT(25, "All you see is darkness. You stumble in something and almost fall. It seems like a chair. You decide to get out of the room.",
        {
        OPTION(82, "Enter room"),
        OPTION(23, "Check door on the left"),
        OPTION(30, "Check door on the left"),
        OPTION(69, "Check door on the left"),
        OPTION(21, "Go back on the corridor"),
        OPTION(26, "Continue down the hall"),
        OPTION(38, "Continue down the hall")
        }
    );

    EVENT(26, "You give a few more steps and hear a sound.",
        {
        OPTION(27, "Stay in the corridor"),
        OPTION(29, "Stay in the corridor"),
        OPTION(28, "Enter the closest room")
        }
    );

    EVENT(27, "A man gets out of a room at the end of the corridor and sees you.\n"
              "He is big and strong.\n"
              "You are weak and has no kind of weapon.\n"
              "You try to run, but he catches you and punches you in the face.\n"
              "The world turns to black.\n\n"
              "YOU LOST", {}
    );

    EVENT(28, "You quickly enter the room and close the door. You hear footsteps approaching, and then some beeps and a door opening and closing.\n"
              "You slowly get out of the room.",
        {
        OPTION(30, "Check the door across from you"),
        OPTION(21, "Go back on the corridor"),
        OPTION(31, "Keep walking ahead")
        }
    );

    EVENT(29, "A man gets out of a room at the end of the corridor and sees you.\n"
               "He is big and strong.",
        {
        OPTION(32, "Try to run"),
        OPTION(33, "Wrestle with him"),
        OPTION(34, "Hit him with the pipe")
        }
    );

    EVENT(30, "You can see that the light inside the room is turned on. You still do not know the passcode for the door.",
        {
        OPTION(22, "Check door on the right"),
        OPTION(21, "Go back on the corridor"),
        OPTION(31, "Keep walking ahead")
        }
    );

    EVENT(31, "You see a big window on your right. You try to see inside the room but there is something blocking the view. It seems like cardboard boxes.",
        {
        OPTION(35, "Go back on the corridor"),
        OPTION(36, "Keep walking ahead")
        }
    );

    EVENT(32, "You reaches the beginning of the corridor and he tackles you.\n"
              "You fall and hit your head on the plant’s vase.\n"
              "The world turns to black.\n\n"
              "YOU LOST", {}
    );

    EVENT(33, "He is much stronger than you are.\n"
              "He hits you with the pipe that you should have used against him.\n"
              "The world turns to black.\n\n"
              "YOU LOST", {}
    );

    EVENT(34, "You quickly hit him in the head with the pipe. He falls down in front of you.\n"
              "Well done.\n"
              "You see a big window on your right. You try to see inside the room but there is something blocking the view. It seems like cardboard boxes",
        {
        OPTION(35, "Go back on the corridor"),
        OPTION(36, "Keep walking ahead")
        }
    );

    EVENT(35, "You went back. And now?",
        {
        OPTION(22, "Check door on the right"),
        OPTION(23, "Check door on the left"),
        OPTION(30, "Check door on the left"),
        OPTION(69, "Check door on the left"),
        OPTION(21, "Go back up"),
        OPTION(38, "Continue down the hall")
        }
    );

    EVENT(36, "You reach the corner of the corridor. There is a door to your left and the corridor continues on your right.",
        {
        OPTION(37, "Check door"),
        OPTION(38, "Go back on the corridor"),
        OPTION(39, "Turn right on the corridor")
        }
    );

    EVENT(37, "The door is ajar and you hear no sound inside it. You smell a distinct odour.",
        {
        OPTION(40, "Enter room"),
        OPTION(38, "Go back on the corridor"),
        OPTION(39, "Turn right on the corridor")
        }
    );

    EVENT(38, "You are again in front of the big window.",
        {
        OPTION(35, "Go Up"),
        OPTION(36, "Go to the corner of the corridor"),
        OPTION(68, "Go to the corner of the corridor")
        }
    );

    EVENT(39, "This part of the corridor is brighter because of the windows on the right. You look through the closest windows and see an open field.",
        {
        OPTION(41, "Keep walking"),
        OPTION(68, "Go back on the corridor")
        }
    );

    EVENT(40, "You are faced with a surgical environment… -ish.\n"
              "The floor is made of white tiles and there is a stretcher in the middle of the room, with a figure laying over it."
              "You also see a metal table behind the stretcher, a sink, a desk and trash cans.",
        {
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(44, "Check stretcher"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(41, "You keep walking and see a new door. To your right, right ahead, there is another window.",
        {
        OPTION(47, "Check door"),
        OPTION(48, "Check window"),
        OPTION(49, "Keep walking"),
        OPTION(50, "Go back on the corridor")
        }
    );

    EVENT(42, "You are back at the corner of the corridor.\n"
              "Maybe you killed the man you struck with the pipe, because he is still on the ground.",
        {
        OPTION(40, "Check room at the left"),
        OPTION(38, "Go back on the first portion of the corridor"),
        OPTION(67, "Walk to the right")
        }
    );

    EVENT(43, "There are a few papers on the table, looking like hospital forms. You also see a key.",
        {
        OPTION(51, "Grab key"),
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(44, "Check stretcher"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(44, "There is a body on the stretcher. You see an incision going from the neck to the abdomen.",
        {
        OPTION(53, "Poke body"),
        OPTION(92, "Get out of room ASAP"),
        OPTION(93, "Get out of room ASAP"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(45, "There is many surgical instruments on the table.",
        {
        OPTION(54, "Grab something"),
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(44, "Check stretcher"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(46, "There are three trash cans, one for recyclable waste, one for general and a big one for biological residue. Well, at least they recycle.",
        {
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(44, "Check stretcher"),
        OPTION(45, "Check table"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(47, "You go for the knob. It does not turn.",
        {
        OPTION(55, "Use key on door"),
        OPTION(48, "Check window behind you"),
        OPTION(49, "Keep walking"),
        OPTION(50, "Go back on the corridor")
        }
    );

    EVENT(48, "You see the same from the other window: an open field.",
        {
        OPTION(47, "Check door behind you"),
        OPTION(59, "Enter the room behind you"),
        OPTION(49, "Keep walking"),
        OPTION(50, "Go back on the corridor")
        }
    );

    EVENT(49, "You reach the end of the corridor. Through the window, you see what looks like a parking lot and a car.",
        {
        OPTION(56, "Go back"),
        OPTION(57, "Sit down")
        }
    );

    EVENT(50, "Nothing to do here.",
        {
        OPTION(56, "Turn around and walk back"),
        OPTION(42, "Go towards the corner of the corridors"),
        OPTION(66, "Go towards the corner of the corridors"),
        OPTION(68, "Go towards the corner of the corridors")
        }
    );

    EVENT(51, "You put the key in your pocket. What does it open?",
        {
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(44, "Check stretcher"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(52, "There are a few papers on the table, looking like hospital forms.",
        {
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(44, "Check stretcher"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(53, "Yep, the person is dead.",
        {
        OPTION(58, "Poke again"),
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(54, "You now have a scalpel. This may came in handy. \n You need to be careful not to cut yourself.",
        {
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(44, "Check stretcher"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(55, "The key fits. You turn it and the door unlocks.",
        {
        OPTION(59, "Enter room"),
        OPTION(48, "Check window behind you"),
        OPTION(49, "Keep walking to the right"),
        OPTION(50, "Go back on the corridor")
        }
    );

    EVENT(56, "You are between the door and the window again.",
        {
        OPTION(47, "Check door"),
        OPTION(59, "Enter room"),
        OPTION(48, "Check window"),
        OPTION(49, "Go right"),
        OPTION(50, "Go left")
        }
    );

    EVENT(57, "How did you ended up here? How do you get out? What is the meaning of life?",
        {
        OPTION(56, "Go back"),
        OPTION(57, "Keep divagating")
        }
    );

    EVENT(58, "Don't.",
        {
        OPTION(58, "Poke again"),
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(58, "Don't.",
        {
        OPTION(58, "Poke again"),
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        OPTION(81, "Check sink")
        }
    );

    EVENT(59, "You are in a room full of cardboard boxes piled up. It seems that no one goes in there for a while.",
        {
        OPTION(60, "Walk around the room"),
        OPTION(64, "Get out of room")
        }
    );

    EVENT(60, "Boxes and more boxes, all but one closed up with duct tape. You find just office equipment inside that one, nothing useful.",
        {
        OPTION(61, "Keep walking around"),
        OPTION(63, "Keep walking around"),
        OPTION(64, "Get out of room")
        }
    );

    EVENT(61, "A green bulletin board call your attention.",
        {
        OPTION(62, "Look closely"),
        OPTION(99, "Look closely"),
        OPTION(63, "Keep walking around"),
        OPTION(64, "Get out of room")
        }
    );

    EVENT(62, "You make a way between the boxes and gets close to the board. You see a dirt piece of paper with four numbers on it.",
        {
        OPTION(65, "Grab paper"),
        OPTION(63, "Keep walking around"),
        OPTION(64, "Get out of room")
        }
    );

    EVENT(63, "Just boxes and more boxes.",
        {
        OPTION(61, "Keep walking around"),
        OPTION(63, "Keep walking around"),
        OPTION(64, "Get out of room")
        }
    );

    EVENT(64, "You are back in the corridor.",
        {
        OPTION(60, "Go back into the room"),
        OPTION(48, "Check window"),
        OPTION(49, "Go right"),
        OPTION(50, "Go left")
        }
    );

    EVENT(65, "You unpin the paper and put it in your pocket.",
        {
        OPTION(63, "Keep walking around"),
        OPTION(64, "Get out of room")
        }
    );

    EVENT(66, "You hear noise inside the surgical room. The person you heard earlier must have come back to it.",
        {
        OPTION(98, "Enter room on the left"),
        OPTION(67, "Go back to the right"),
        OPTION(38, "Keep walking ahead")
        }
    );

    EVENT(67, "The day is a little less bright outside the window.",
        {
        OPTION(56, "Keep going right"),
        OPTION(68, "Go back to corner")
        }
    );

    EVENT(68, "You are at the corner again.",
        {
        OPTION(98, "Enter room on the left"),
        OPTION(40, "Enter room on the left"),
        OPTION(38, "Go up again"),
        OPTION(67, "Go right")
        }
    );

    EVENT(69, "You try the door again, but it is locked. You see the digital lock.",
        {
        OPTION(70, "Try \"4321\""),
        OPTION(72, "See the paper you found on the bulletin board"),
        OPTION(22, "Check door on the right"),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(70, "Wrong password.",
        {
        OPTION(71, "Try \"6789\""),
        OPTION(72, "See the paper you found on the bulletin board"),
        OPTION(22, "Check door on the right"),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(71, "Wrong password.",
        {
        OPTION(72, "See the damn paper you found on the bulletin board"),
        OPTION(22, "Check door on the right"),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(72, "In the paper, you read \"3109\"",
        {
        OPTION(73, "Try \"3109\""),
        OPTION(22, "Check door on the right"),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(73, "Here you go. The door is unlocked.",
        {
        OPTION(74, "Enter room"),
        OPTION(22, "Check door on the right"),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(74, "You enter the room. There is a cabinet to your right and a sink to your left. You also see a few white freezers.",
        {
        OPTION(35, "Get out of room"),
        OPTION(75, "Check cabinet"),
        OPTION(76, "Check sink"),
        OPTION(77, "Check sink"),
        OPTION(78, "Check freezers")
        }
    );

    EVENT(75, "One of the cabinet drawers are open. You see a lot of files inside it, organized by date.",
        {
        OPTION(35, "Get out of room"),
        OPTION(76, "Check sink"),
        OPTION(77, "Check sink"),
        OPTION(78, "Check freezers")
        }
    );

    EVENT(76, "There is a little bit of blood on it. Your eyes catch the glimpse of something on the floor, behind the sink.",
        {
        OPTION(79, "Inspect object"),
        OPTION(35, "Get out of room"),
        OPTION(75, "Check cabinet"),
        OPTION(78, "Check freezers")
        }
    );

    EVENT(77, "It is still the same sink.",
        {
        OPTION(35, "Get out of room"),
        OPTION(75, "Check cabinet"),
        OPTION(78, "Check freezers")
        }
    );

    EVENT(78, "You go to one of the freezers and open it.\n"
              "Deep down, you already knew what you would find inside it.\n"
              "Organs.\n"
              "Human Organs.\n"
              "Heart, lung, livers, bones…",
        {
        OPTION(35, "Get out of the room NOW"),
        OPTION(75, "Check cabinet"),
        OPTION(76, "Check sink"),
        OPTION(77, "Check sink")
        }
    );

    EVENT(79, "You go down and see that the object is a flashlight.",
        {
        OPTION(80, "Grab flashlight"),
        OPTION(35, "Get out of room"),
        OPTION(75, "Check cabinet"),
        OPTION(78, "Check freezers")
        }
    );

    EVENT(80, "You stand up, with the flashlight in your hand and try to turn it ON...\n"
              "It works.\n"
              "You take the flashlight.",
        {
        OPTION(35, "Get out of room"),
        OPTION(75, "Check cabinet"),
        OPTION(78, "Check freezers")
        }
    );

    EVENT(81, "There is a lot of blood stains on the sink. Ew.",
        {
        OPTION(92, "Get out of room"),
        OPTION(93, "Get out of room"),
        OPTION(43, "Check desk"),
        OPTION(52, "Check desk"),
        OPTION(44, "Check stretcher"),
        OPTION(45, "Check table"),
        OPTION(46, "Check trash cans"),
        }
    );

    EVENT(82, "It is too dark to see anything.",
        {
        OPTION(82, "Walk around in the dark"),
        OPTION(83, "Use the flashlight"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(83, "You turn the flashlight ON. You see just a table and chairs. Moving a little further into the room, you see something on the floor at the back.",
        {
        OPTION(84, "Check table"),
        OPTION(85, "Check back of the room"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(84, "Dust. That is the best word to describe the table and the chairs around it. They seem new, but are covered in dust.",
        {
        OPTION(85, "Check back of the room"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(85, "As you get closer to the back wall, you identity the things on the floor as rubbish."
              "You move the light to the wall and it seems to move a little. Weird.",
        {
        OPTION(86, "Inspect wall"),
        OPTION(84, "Check table"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(86, "You touch the wall. That does not feel like a wall. It is softer and it feels like plastic.\n"
              "You aim the light up and down the down.\n"
              "It is a tarpaulin!\n"
              "The original wall must have broken and they use it to cover the hole. Based on the amount of debris on the floor, it is not a small hole.",
        {
        OPTION(87, "Try to rip tarp"),
        OPTION(84, "Check table"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(87, "Nothing. The tarp is too thick to rip it with your bare hands.",
        {
        OPTION(88, "Use scalpel"),
        OPTION(84, "Check table"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(88, "You remember the scalpel in your pocket. You grab it, cutting your finger in the process.\n"
              "You stick it in the tarp. The scalpel easily slide through it, creating an opening.",
        {
        OPTION(89, "Try to pass through the hole"),
        OPTION(84, "Check table"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(89, "It is not big enough yet.",
        {
        OPTION(90, "Use scalpel"),
        OPTION(84, "Check table"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(90, "You cut more of the tarp.",
        {
        OPTION(91, "Try to pass through the hole"),
        OPTION(84, "Check table"),
        OPTION(35, "Get out of room")
        }
    );

    EVENT(91, "Now you got it. You are in a courtyard. You see what broke the wall: a fallen tree.\n"
              "You look around and see no one.\n"
              "You remember the car park.\n"
              "You know how to hotwire a car.\n"
              "Run, Forest, RUN!\n\n"
              "YOU WON", {}
    );

    EVENT(92, "You are back at the corner of the corridor.",
        {
        OPTION(40, "Enter room again"),
        OPTION(38, "Go up on the corridor"),
        OPTION(39, "Walk to the right")
        }
    );

    EVENT(93, "A man appears right in front of you on the corridor.",
        {
        OPTION(94, "Fight him"),
        OPTION(95, "Run"),
        OPTION(96, "Use pipe"),
        OPTION(97, "Use scalpel")
        }
    );

    EVENT(94, "He is way bigger than you.\n"
              "He punches you in the face.\n"
              "The world turns to black.\n\n"
              "YOU LOST", {}
    );

    EVENT(95, "You try to scape but he catches you.\n"
              "The world turns to black.\n\n"
              "YOU LOST", {}
    );

    EVENT(96, "You quickly hit him in the head with the pipe. He falls down in front of you.\n"
              "Well done.",
        {
        OPTION(40, "Enter room again"),
        OPTION(38, "Go up on the corridor"),
        OPTION(39, "Walk to the right")
        }
    );

    EVENT(97, "You strike him with the scalpel, but it gets stuck on him. Now he is really mad.\n"
              "He punches you in the face.\n"
              "The world turns to black.\n\n"
              "YOU LOST", {}
    );

    EVENT(98, "When you reach for the door, the door suddenly opens. There is a man in a bloody apron in front of you.",
        {
        OPTION(94, "Fight him"),
        OPTION(95, "Run to the corridor"),
        OPTION(96, "Use pipe"),
        OPTION(97, "Use scalpel")
        }
    );

    EVENT(99, "You need both hands to move the boxes, so you lower the pipe.\n"
              "You make a way between the boxes and gets close to the board.\n"
              "There is a paper pinned on it with four numbers written on it.\n",
        {
        OPTION(65, "Grab paper"),
        OPTION(63, "Keep walking around"),
        OPTION(64, "Get out of room")
        }
    );

    EVENT(100, "Better now.",
        {
        OPTION(3, "Check the window"),
        OPTION(5, "Check the bars"),
        OPTION(7, "Check the bed")
        }
    );
}

void ZorkFlee::createItems(){
    items["pipe"] = new Item(0, "Pipe", "old broken pipe", QRect(9,5,30,3), "pipe.png");
    items["key"] = new Item(1, "Key", "", QRect(322,247,12,12), "key.png");
    items["scalpel"] = new Item(2, "Scalpel", "", QRect(70,177,13,3), "scalpel.png");
    items["passcode"] = new Item(3, "Passcode", "piece of paper with 4 numbers", QRect(170,5,15,3), "passcode.png");
    items["flashlight"] = new Item(4, "Flashlight", "", QRect(109,307,7,8), "flashlight.png");

    *CORR(1) << items["pipe"];
    *ROOM(5) << items["key"];
    *ROOM(5) << items["scalpel"];
    *ROOM(6) << items["passcode"];
    *ROOM(4) << items["flashlight"];
}

// Show the window that runs the game
void ZorkFlee::play() {
    show();
}

void ZorkFlee::changeRoom(Gateway *gateway) {
    Room* nextRoom = gateway->getOtherRoom(currentRoom);

    if (nextRoom != NULL) {
        destRoom = nextRoom;
    } else {
        cerr << "Could not change room: " << currentRoom->getName() << " using " << gateway->toString() << endl;
    }
}

void ZorkFlee::changeRoom(Gateway* gateway, string currentRoomPosId, string nextPositionId) {

    Room* nextRoom = gateway->getOtherRoom(currentRoom);

    if (nextRoom != NULL) {
        destRoom = nextRoom;
        if (currentRoomPosId != "") {
            player.addAnimation(currentRoom->getPosition(currentRoomPosId), 1000);
            player.addAnimation(destRoom->getPosition(nextPositionId), 1000);
        } else {
            player.addAnimation(destRoom->getPosition(nextPositionId), 1500);
        }
    } else {
        cerr << "Could not change room: " << currentRoom->getName() << " using " << gateway->toString() << endl;
    }
}

// Sets an animation for character, given the next position and the duration of the animation
inline void ZorkFlee::runAnimation(Character& character, QPoint nextPosition, int timeMs) {
    character.addAnimation(nextPosition, timeMs);
}

void ZorkFlee::performOption(Event::Option* option) {
    QPoint pointTemp;
    switch (option->id) {
        case 3:
            runAnimation(player, currentRoom->getPosition("window"));
            break;
        case 4:
            runAnimation(player, currentRoom->getPosition("toilet"));
            break;
        case 5:
            runAnimation(player, currentRoom->getPosition("bars"));
            break;
        case 7:
            runAnimation(player, currentRoom->getPosition("bed"));
            break;
        case 11:
            gateways[0]->setLocked(false);
            changeRoom(gateways[0], "", "initial");
            break;
        case 12:
            runAnimation(player, currentRoom->getPosition("water"));
            break;
        case 13:
            runAnimation(player, currentRoom->getPosition("table"));
            break;
        case 14:
            runAnimation(player, currentRoom->getPosition("table"));
            break;
        case 15:
            changeRoom(gateways[1], "door", "initial");
            if (player.hasItem(items["pipe"])){
                events[15]->disableOption(1);
                events[15]->enableOption(2);
            }
            else{
                events[15]->enableOption(1);
                events[15]->disableOption(2);
            }
            break;
        case 16:
            runAnimation(player, currentRoom->getPosition("plant"));
            if (player.hasItem(items["pipe"]) || player.hasItem(items["passcode"])){
                events[16]->disableOption(0);
                events[16]->enableOption(1);
            }
            else{
                events[16]->enableOption(0);
                events[16]->disableOption(1);
            }
            break;
        case 17:
            runAnimation(player, currentRoom->getPosition("plant"));
            break;
        case 18:
            changeRoom(gateways[1], "initial", "door");
            break;
        case 19:
            if (enemy.isOnRoom4()){
                events[19]->disableOption(1);
                events[19]->enableOption(2);
                events[19]->disableOption(3);
            }
            else if (!player.hasItem(items["passcode"])){
                events[19]->enableOption(1);
                events[19]->disableOption(2);
                events[19]->disableOption(3);
            } else {
                events[19]->disableOption(1);
                events[19]->disableOption(2);
                events[19]->enableOption(3);
            }
            if (enemy.isDown() || enemy.isOnRoom5()){
                events[19]->disableOption(5);
                events[19]->disableOption(6);
                events[19]->enableOption(7);
            } else if (enemy.isOnRoom4()){
                events[19]->disableOption(5);
                events[19]->enableOption(6);
                events[19]->disableOption(7);
            } else {
                events[19]->enableOption(5);
                events[19]->disableOption(6);
                events[19]->disableOption(7);
            }
            changeRoom(gateways[2], "", "initial");
            break;
        case 20:
            player << items["pipe"];
            *CORR(1) >> items["pipe"];
            break;
        case 21:
            if (currentRoom == ROOM(2))
                changeRoom(gateways[1], "door", "initial");
            else if (currentRoom == CORR(2))
                changeRoom(gateways[2], "", "default");
            if (player.hasItem(items["pipe"]) || player.hasItem(items["passcode"])){
                events[21]->disableOption(1);
                events[21]->enableOption(2);
            } else {
                events[21]->enableOption(1);
                events[21]->disableOption(2);
            }
            break;
        case 22:
            runAnimation(player, currentRoom->getPosition("rightdoor"));
            if (player.hasItem(items["flashlight"])){
                events[22]->disableOption(0);
                events[22]->enableOption(1);
            } else {
                events[22]->enableOption(0);
                events[22]->disableOption(1);
            }
            if (enemy.isOnRoom4()){
                events[22]->disableOption(2);
                events[22]->enableOption(3);
                events[22]->disableOption(4);
            }
            else if (!player.hasItem(items["passcode"])){
                events[22]->enableOption(2);
                events[22]->disableOption(3);
                events[22]->disableOption(4);
            } else {
                events[22]->disableOption(2);
                events[22]->disableOption(3);
                events[22]->enableOption(4);
            }
            if (enemy.isOnRoom4() || enemy.isOnRoom5() || enemy.isDown()){
                events[22]->disableOption(6);
                events[22]->enableOption(7);
            } else {
                events[22]->enableOption(6);
                events[22]->disableOption(7);
            }
            break;
        case 23:
            runAnimation(player, currentRoom->getPosition("leftdoor"));
            break;
        case 24:
            runAnimation(player, currentRoom->getPosition("plant"));
            break;
        case 25:
            player.addAnimation(ROOM(3)->getPosition("middle"), 1250);
            player.addAnimation(currentRoom->getPosition("rightdoor"), 1000);
            if (!player.hasItem(items["flashlight"])){
                events[25]->disableOption(0);
            } else {
                events[25]->enableOption(0);
            }
            if (enemy.isOnRoom4()){
                events[25]->disableOption(1);
                events[25]->enableOption(2);
                events[25]->disableOption(3);
            }
            else if (!player.hasItem(items["passcode"])){
                events[25]->enableOption(1);
                events[25]->disableOption(2);
                events[25]->disableOption(3);
            } else {
                events[25]->disableOption(1);
                events[25]->disableOption(2);
                events[25]->enableOption(3);
            }
            if (enemy.isOnRoom4() || enemy.isOnRoom5() || enemy.isDown()){
                events[25]->disableOption(5);
                events[25]->enableOption(6);
            } else {
                events[25]->enableOption(5);
                events[25]->disableOption(6);
            }
            break;
        case 26:
            changeRoom(gateways[6], "", "initial");
            if (player.hasItem(items["pipe"])){
                events[26]->disableOption(0);
                events[26]->enableOption(1);
            } else {
                events[26]->enableOption(0);
                events[26]->disableOption(1);
            }

            break;
        case 27:
            gameOver = true;
            enemy.addAnimation(enemy.getPosition("playerstays1"), 750);
            enemy.addAnimation(enemy.getPosition("playerstays2"), 1000);
            enemy.addAnimation(enemy.getPosition("playerstays3"), 1000);
            QTimer::singleShot(1750, [&]{runAnimation(player, CORR(3)->getRect().topLeft() + QPoint(10, 25), 1000);});
            break;
        case 28:
            enemy.addAnimation(enemy.getPosition("playerhides1"), 1250);
            enemy.addAnimation(enemy.getPosition("playerhides2"), 1000);
            enemy.addAnimation(enemy.getPosition("playerhides3"), 3000);
            enemy.addAnimation(enemy.getPosition("playerhides4"), 1000);
            player.addAnimation(CORR(2)->getPosition("rightdoor"), 1000);
            player.addAnimation(ROOM(3)->getPosition("initial"), 500, [&]{currentRoom = ROOM(3); destRoom = 0;});
            player.addSleepAnimation(4500, [&]{destRoom = CORR(2);});
            player.addAnimation(CORR(2)->getPosition("rightdoor"), 1250, [&]{currentRoom = CORR(2); destRoom = 0;});
            enemy.setEnemyOnRoom4(true);
            break;
        case 29:
            runAnimation(enemy, enemy.getPosition("playerstays1"), 500);
            runAnimation(enemy, enemy.getPosition("playerstays2"), 1000);
            break;
        case 30:
            runAnimation(player, currentRoom->getPosition("leftdoor"));
            break;
        case 31:
            changeRoom(gateways[6], "", "window");
            break;
        case 32:
            runAnimation(player, enemy.getPosition("playerstaysrun"), 2250);
            runAnimation(enemy, enemy.getPosition("playerstaysrun"), 2220);
            gameOver = true;
            break;
        case 33:
            runAnimation(player, enemy.getPosition("playerstaysfight"), 1000);
            runAnimation(enemy, enemy.getPosition("playerstaysfight"), 1000);
            gameOver = true;
            break;
        case 34:
            runAnimation(player, enemy.getPosition("playerstayspipe"), 1000);
            runAnimation(enemy, enemy.getPosition("playerstayspipe"), 1000);
            runAnimation(enemy, enemy.getPosition("playerstayspipe") + QPoint(10, 10), 750);
            enemy.setEnemyDown(true);
            break;
        case 35:
            if (currentRoom == ROOM(4)){
                changeRoom(gateways[5], "initial", "leftdoor");
                gateways[5]->setLocked(true);
            }
            else if (currentRoom == ROOM(3)){
                changeRoom(gateways[3]);
                player.addAnimation(ROOM(3)->getPosition("initial"), 1000);
                player.addAnimation(CORR(2)->getPosition("rightdoor"), 750, [&]{ROOM(3)->setVisible(false);});
            }
            else if (currentRoom == CORR(3))
                changeRoom(gateways[6], "",  "initial");
            if (enemy.isOnRoom4()){
                events[35]->disableOption(1);
                events[35]->enableOption(2);
                events[35]->disableOption(3);
            }
            else if (!player.hasItem(items["passcode"])){
                events[35]->enableOption(1);
                events[35]->disableOption(2);
                events[35]->disableOption(3);
            } else {
                events[35]->disableOption(1);
                events[35]->disableOption(2);
                events[35]->enableOption(3);
            }
            break;
        case 36:
            changeRoom(gateways[7], "", "initial");
            player.setReachedCorner(true);
            break;
        case 37:
            runAnimation(player, currentRoom->getPosition("door"));
            break;
        case 38:
            if (currentRoom == CORR(2))
                changeRoom(gateways[6], "", "window");
            else if (currentRoom == CORR(4))
                changeRoom(gateways[7], "", "window");
            if (!player.hasReachedCorner()){
                events[38]->enableOption(1);
                events[38]->disableOption(2);
            } else {
                events[38]->disableOption(1);
                events[38]->enableOption(2);
            }
            break;
        case 39:
            changeRoom(gateways[9], "corner", "initial");
            break;
        case 40:
            changeRoom(gateways[8], "door", "initial");
            if (player.hasItem(items["key"])){
                events[40]->disableOption(2);
                events[40]->enableOption(3);
            } else {
                events[40]->enableOption(2);
                events[40]->disableOption(3);
            }
            if (enemy.hasReturned()){
                events[40]->disableOption(0);
                events[40]->enableOption(1);
            } else {
                events[40]->enableOption(0);
                events[40]->disableOption(1);
            }
            break;
        case 41:
            changeRoom(gateways[10], "", "initial");
            break;
        case 42:
            changeRoom(gateways[9], "", "corner");
            break;
        case 43:
            runAnimation(player, currentRoom->getPosition("desk"));
            if (enemy.hasReturned()){
                events[43]->disableOption(1);
                events[43]->enableOption(2);
            } else {
                events[43]->enableOption(1);
                events[43]->disableOption(2);
            }
            break;
        case 44:
            runAnimation(player, currentRoom->getPosition("stretcher"));
            if (player.hasItem(items["key"])){
                events[44]->disableOption(3);
                events[44]->enableOption(4);
            } else {
                events[44]->enableOption(3);
                events[44]->disableOption(4);
            }
            if (enemy.hasReturned()){
                events[44]->disableOption(1);
                events[44]->enableOption(2);
            } else {
                events[44]->enableOption(1);
                events[44]->disableOption(2);
            }
            break;
        case 45:
            runAnimation(player, currentRoom->getPosition("table"));
            if (player.hasItem(items["scalpel"]))
                events[45]->disableOption(0);
            if (player.hasItem(items["key"])){
                events[45]->disableOption(3);
                events[45]->enableOption(4);
            } else {
                events[45]->enableOption(3);
                events[45]->disableOption(4);
            }
            if (enemy.hasReturned()){
                events[45]->disableOption(1);
                events[45]->enableOption(2);
            } else {
                events[45]->enableOption(1);
                events[45]->disableOption(2);
            }
            break;
        case 46:
            runAnimation(player, currentRoom->getPosition("garbage"));
            if (player.hasItem(items["key"])){
                events[46]->disableOption(2);
                events[46]->enableOption(3);
            } else {
                events[46]->enableOption(2);
                events[46]->disableOption(3);
            }
            if (enemy.hasReturned()){
                events[46]->disableOption(0);
                events[46]->enableOption(1);
            } else {
                events[46]->enableOption(0);
                events[46]->disableOption(1);
            }
            break;
        case 47:
            runAnimation(player, currentRoom->getPosition("door"));
            if (!player.hasItem(items["key"])){
                if (!enemy.isDown()) enemy.setEnemyReturn(true);
                events[47]->disableOption(0);
            } else {
                events[47]->enableOption(0);
            }

            break;
        case 48:
            runAnimation(player, currentRoom->getPosition("window"));
            if (gateways[12]->isLocked()){
                events[48]->enableOption(0);
                events[48]->disableOption(1);
            } else {
                events[48]->disableOption(0);
                events[48]->enableOption(1);
            }
            break;
        case 49:
            changeRoom(gateways[11], "", "initial");
            break;
        case 50:
            changeRoom(gateways[10], "", "default");
            if (enemy.isDown()){
                events[50]->enableOption(1);
                events[50]->disableOption(2);
                events[50]->disableOption(3);
            } else if (!gateways[12]->isLocked()){
                events[50]->disableOption(1);
                events[50]->enableOption(2);
                events[50]->disableOption(3);
            } else {
                events[50]->disableOption(1);
                events[50]->disableOption(2);
                events[50]->enableOption(3);
            }
            break;
        case 51:
            player << items["key"];
            *ROOM(5) >> items["key"];
            if (enemy.hasReturned()){
                events[51]->disableOption(0);
                events[51]->enableOption(1);
            } else {
                events[51]->enableOption(0);
                events[51]->disableOption(1);
            }
            break;
        case 52:
            runAnimation(player, currentRoom->getPosition("desk"));
            if (enemy.hasReturned()){
                events[52]->disableOption(0);
                events[52]->enableOption(1);
            } else {
                events[52]->enableOption(0);
                events[52]->disableOption(1);
            }
            break;
        case 53:
            if (player.hasItem(items["key"])){
                events[53]->disableOption(3);
                events[53]->enableOption(4);
            } else {
                events[53]->enableOption(3);
                events[53]->disableOption(4);
            }
            if (enemy.hasReturned()){
                events[53]->disableOption(1);
                events[53]->enableOption(2);
            } else {
                events[53]->enableOption(1);
                events[53]->disableOption(2);
            }
            break;
        case 54:
            player << items["scalpel"];
            *ROOM(5) >> items["scalpel"];
            if (player.hasItem(items["key"])){
                events[54]->disableOption(2);
                events[54]->enableOption(3);
            } else {
                events[54]->enableOption(2);
                events[54]->disableOption(3);
            }
            if (enemy.hasReturned()){
                events[54]->disableOption(0);
                events[54]->enableOption(1);
            } else {
                events[54]->enableOption(0);
                events[54]->disableOption(1);
            }
            break;
        case 55:
            gateways[12]->setLocked(false);
            break;
        case 56:
            if (currentRoom == CORR(5))
                changeRoom(gateways[10], "", "initial");
            else if (currentRoom == CORR(7))
                changeRoom(gateways[11], "", "initial");
            if (gateways[12]->isLocked()){
                events[56]->enableOption(0);
                events[56]->disableOption(1);
            } else {
                events[56]->disableOption(0);
                events[56]->enableOption(1);
            }
            break;
        case 58:
            if (player.hasItem(items["key"])){
                events[58]->disableOption(3);
                events[58]->enableOption(4);
            } else {
                events[58]->enableOption(3);
                events[58]->disableOption(4);
            }
            if (enemy.hasReturned()){
                events[58]->disableOption(1);
                events[58]->enableOption(2);
            } else {
                events[58]->enableOption(1);
                events[58]->disableOption(2);
            }
            break;
         case 59:
            changeRoom(gateways[12], "door", "initial");
            break;
        case 60:
            if (currentRoom == CORR(6))
                changeRoom(gateways[12], "door", "initial");
            else
                runAnimation(player, currentRoom->getPosition("walkaround1"));
            if (player.hasItem(items["passcode"])){
                events[60]->disableOption(0);
                events[60]->enableOption(1);
            } else {
                events[60]->enableOption(0);
                events[60]->disableOption(1);
            }
            break;
        case 61:
            runAnimation(player, currentRoom->getPosition("bulletinboard"));
            if (player.hasItem(items["pipe"])){
                events[61]->disableOption(0);
                events[61]->enableOption(1);
            } else {
                events[61]->enableOption(0);
                events[61]->disableOption(1);
            }
            break;
        case 62:
            runAnimation(player, currentRoom->getPosition("passcode"));
            break;
        case 63:
            if (player.hasItem(items["passcode"])){
                events[63]->disableOption(0);
                events[63]->enableOption(1);
                if (player.getRect().topLeft() == currentRoom->getPosition("walkaround2"))
                    runAnimation(player, currentRoom->getPosition("walkaround1"));
                else if (player.getRect().topLeft() == currentRoom->getPosition("walkaround1"))
                    runAnimation(player, currentRoom->getPosition("bulletinboard"));
                else
                    runAnimation(player, currentRoom->getPosition("walkaround2"));
            } else {
                events[63]->enableOption(0);
                events[63]->disableOption(1);
                runAnimation(player, currentRoom->getPosition("walkaround2"));
            }
            break;
        case 64:
           changeRoom(gateways[12], "initial", "door");
           break;
        case 65:
            player << items["passcode"];
            *ROOM(6) >> items["passcode"];
            break;
        case 66:
            enemy.setPosition("initial");
            enemy.setEnemyOnRoom5(true);
            enemy.setEnemyOnRoom4(false);
            changeRoom(gateways[9], "", "corner");
            break;
        case 67:
            changeRoom(gateways[9], "", "initial");
            break;
        case 68:
            if (currentRoom == CORR(5))
                changeRoom(gateways[9], "", "corner");
            else if (currentRoom == CORR(3))
                changeRoom(gateways[7], "", "corner");
            if (enemy.isOnRoom5()){
                events[68]->enableOption(0);
                events[68]->disableOption(1);
            } else {
                events[68]->disableOption(0);
                events[68]->enableOption(1);
            }
            break;
        case 69:
            runAnimation(player, currentRoom->getPosition("leftdoor"));
            break;
        case 74:
            gateways[5]->setLocked(false);
            changeRoom(gateways[5], "", "initial");
            if (player.hasItem(items["flashlight"])){
                events[74]->disableOption(2);
                events[74]->enableOption(3);
            } else {
                events[74]->enableOption(2);
                events[74]->disableOption(3);
            }
            break;
        case 75:
            runAnimation(player, currentRoom->getPosition("cabinet"));
            if (player.hasItem(items["flashlight"])){
                events[75]->disableOption(1);
                events[75]->enableOption(2);
            } else {
                events[75]->enableOption(1);
                events[75]->disableOption(2);
            }
            break;
        case 76:
            runAnimation(player, currentRoom->getPosition("sink"));
            break;
        case 77:
            runAnimation(player, currentRoom->getPosition("sink"));
            break;
        case 78:
            runAnimation(player, currentRoom->getPosition("freezer"));
            if (player.hasItem(items["flashlight"])){
                events[78]->disableOption(2);
                events[78]->enableOption(3);
            } else {
                events[78]->enableOption(2);
                events[78]->disableOption(3);
            }
            break;
        case 79:
            runAnimation(player, currentRoom->getPosition("flashlight"));
            break;
        case 80:
            player << items["flashlight"];
            *ROOM(4) >> items["flashlight"];
            break;
        case 81:
            runAnimation(player, currentRoom->getPosition("sink"));
            if (player.hasItem(items["key"])){
                events[81]->disableOption(2);
                events[81]->enableOption(3);
            } else {
                events[81]->enableOption(2);
                events[81]->disableOption(3);
            }
            if (enemy.hasReturned()){
                events[81]->disableOption(0);
                events[81]->enableOption(1);
            } else {
                events[81]->enableOption(0);
                events[81]->disableOption(1);
            }
            break;
        case 82:
            if (currentRoom != ROOM(3))
                changeRoom(gateways[3], "", "initial");
            else {
                if (player.getRect().topLeft() == currentRoom->getPosition("initial"))
                    runAnimation(player, currentRoom->getPosition("p1"));
                else if (player.getRect().topLeft() == currentRoom->getPosition("p1"))
                    runAnimation(player, currentRoom->getPosition("p2"));
                else
                    runAnimation(player, currentRoom->getPosition("initial"));
            }
            break;
        case 83:
            ROOM(3)->setVisible(true);
            break;
        case 84:
            runAnimation(player, currentRoom->getPosition("table"));
            break;
        case 85:
            runAnimation(player, currentRoom->getPosition("debris"));
            break;
        case 86:
            runAnimation(player, currentRoom->getPosition("tarp"));
            break;
        case 87:
            if (!player.hasItem(items["scalpel"]))
                events[87]->disableOption(0);
            else
                events[87]->enableOption(0);
            break;
        case 90:
            gateways[4]->setLocked(false);
            break;
        case 91:
            changeRoom(gateways[4], "", "initial");
            runAnimation(player, ROOM(7)->getPosition("p1"));
            runAnimation(player, ROOM(7)->getPosition("p2"), 2500);
            gameOver = true;
            break;
        case 92:
            changeRoom(gateways[8], "initial", "door");
            runAnimation(player, CORR(4)->getPosition("corner"));
            break;
        case 93:
            changeRoom(gateways[8], "initial", "door");
            enemy.setPosition("playerinroom5");
            enemy.setEnemyOnRoom4(false);
            enemy.setEnemyOnRoom5(false);
            if (!player.hasItem(items["pipe"]))
                events[93]->disableOption(2);
            else
                events[93]->enableOption(2);
            if (!player.hasItem(items["scalpel"]))
                events[93]->disableOption(3);
            else
                events[93]->enableOption(3);
            break;
        case 94:
            runAnimation(enemy, currentRoom->getPosition("door"), 500);
            gameOver = true;
            break;
        case 95:
            runAnimation(enemy, currentRoom->getPosition("corner"), 1000);
            runAnimation(player, currentRoom->getPosition("corner"), 980);
            gameOver = true;
            break;
        case 96:
            if (showingEvent == events[98]) {
                pointTemp.setX(enemy.getRect().left() - 5);
                pointTemp.setY(enemy.getRect().top() + 10);
                runAnimation(enemy, pointTemp, 500);
            } else {
                runAnimation(enemy, enemy.getPosition("playerinroom5") + QPoint(-10, -5), 500);
            }
            enemy.setEnemyDown(true);
            enemy.setEnemyReturn(false);
            break;
        case 97:
            runAnimation(enemy, currentRoom->getPosition("door"), 500);
            runAnimation(player, currentRoom->getPosition("door") + QPoint(0, 5));
            gameOver = true;
            break;
        case 98:
            enemy.setPosition(ROOM(5)->getPosition("initial"));
            runAnimation(player, currentRoom->getPosition("door"), 750);
            if (!player.hasItem(items["pipe"]))
                events[98]->disableOption(2);
            else
                events[98]->enableOption(2);
            if (!player.hasItem(items["scalpel"]))
                events[98]->disableOption(3);
            else
                events[98]->enableOption(3);
            break;
        case 99:
            runAnimation(player, currentRoom->getPosition("passcode"));
            player >> items["pipe"];
            break;
        default: break;
    }
    _SE events[option->id]; // Links to the next event
}

inline void ZorkFlee::createGateway(int id, Room* r1, Room* r2, bool locked) {
    Gateway* g = new Gateway(id, r1, r2, locked);
    gateways.push_back(g);
    r1->addGateway(g);
    r2->addGateway(g);
}

inline void ZorkFlee::drawItems(QPainter& painter, Room *room) {
    QPoint roomPos = room->getRect().topLeft();
    for (Item* i : room->getItems()) {
        QRect rect = i->getRect();
        rect.translate(roomPos);
        painter.drawImage(rect, i->getImage());
    }
}

// Used to simplify the creation of events and make it more readable
inline void ZorkFlee::EVENT(int id, string message, initializer_list<Event::Option*> list) {
    Event *e = new Event(id, message);
    for (auto i : list)
        e->addOption(i);
    events[id] = e;
}

// Used to simplify the creation of options and make it more readable
inline Event::Option* ZorkFlee::OPTION(int id, string message) {
    return new Event::Option(id, message);
}

// This manages the visual aspects of the program
void ZorkFlee::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter painter(this);

    painter.drawImage(gameLogo.rect(), gameLogo);

    // Draw all the rooms
    for (Room* room : rooms) {
        painter.drawImage(room->getRect(), room->getImage());
        drawItems(painter, room);
    }

    if (gameOver) // Sets the enemy to be above the player
        painter.drawImage(player.getRect(), player.getImage());
    // Draw enemy
    painter.drawImage(enemy.getRect(), enemy.getImage());

    // Draw the overlays
    for (Room* room : rooms) { // The separate loop is to draw items below all overlays
        // Exclusion rules at the beginning
        if ((room == currentRoom || room == destRoom) && room == ROOM(3) && !ROOM(3)->isVisible()) {
            static const QPixmap overlay(ASSET((string)"overlay.png"));
            painter.drawPixmap(room->getRect(), overlay);
        }
        if (room == currentRoom || room == destRoom) continue;
        vector<Room*> vRooms = currentRoom->getViewableRooms();
        bool isVR = false;
        for (auto r = vRooms.begin(); r != vRooms.end(); r++) {
            if (*r == room) isVR = true;
        }
        if (isVR) continue;

        // At this point, an overlay is draw
        if (room->isVisible()) {
            static const QPixmap overlay(ASSET((string) "light-overlay.png"));
            painter.drawPixmap(room->getRect(), overlay);
        } else {
            static const QPixmap overlay(ASSET((string)"overlay.png"));
            painter.drawPixmap(room->getRect(), overlay);
        }
    }

    // Draw player
    if (!gameOver)
        painter.drawImage(player.getRect(), player.getImage());


    // If not in movement, draw the text (except when the game ends)
    if (!player.isMoving() || gameOver) {
        QFont font = painter.font();
        font.setPixelSize(20);
        painter.setFont(font);
        painter.setPen(QColor::fromRgb(255,255,204));
        QRect tRect(810, 20, 280, 350);
        string m = showingEvent->getMessage();
        painter.drawText(tRect, Qt::AlignHCenter | Qt::TextWordWrap, QString::fromStdString(m));

        if (!gameOver) {
            painter.setPen(QColor::fromRgb(204,255,255));
            tRect.translate(0, 370);
            auto options = showingEvent->getEnabledOptions();
            string s;
            for (unsigned int i=0; i < options.size(); i++){
                s += to_string(i+1) + ". " + options[i]->label + "\n";
            }
            painter.drawText(tRect, Qt::TextWordWrap, QString::fromStdString(s));
        } else {
            tRect.translate(0, 370);
            tRect.setHeight(100);
            QPushButton* button = new QPushButton("RESTART", this);
            button->setGeometry(tRect);
            QFont font = button->font();
            font.setPixelSize(36);
            button->setFont(font);
            button->setStyleSheet("color: #BEFFFF");
            connect(button, &QPushButton::clicked, [&]() {
                qApp->exit(EXIT_CODE_RESTART);
            });
            button->show();
        }
    }

#ifdef CONSOLE_OUTPUT
    cout << m << endl;
    cout << s << endl;
#endif

}

void ZorkFlee::mouseReleaseEvent(QMouseEvent* e) {
    cout << "Button:" << e->button() << "  x:" << e->x() << "  y:" << e->y() << endl;
}

void ZorkFlee::keyPressEvent(QKeyEvent *e) {
    if (!player.isMoving() && !gameOver) { // Accepts events when an animation is not running and the game is not over
        vector<Event::Option*> options = showingEvent->getEnabledOptions();
        if ((e->key() > Qt::Key_0) && (e->key() < (int) (Qt::Key_1 + options.size()))) {
            Event::Option* option = options[e->key() - Qt::Key_1];
            performOption(option);
            repaint();
        } else {
            cout << "key is not an option" << endl;
        }
    }
}

void ZorkFlee::animate() { // Start of the game loop, where the positions and rooms are updated
    enemy.update();
    bool finished = player.update();
    if (finished) {
        if (destRoom) {
            if (destRoom != ROOM(3))
                destRoom->setVisible(true);
            for (auto r : destRoom->getViewableRooms()) {
                r->setVisible(true);
            }
            currentRoom = destRoom;
            destRoom = 0;
        }
    }
    repaint();
}

#undef ROOM
#undef CORR
#undef _SE
