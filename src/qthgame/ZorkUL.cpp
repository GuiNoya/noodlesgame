#include "ZorkUL.h"

#define ROOM(x) rooms[x-1]
#define CORR(x) rooms[7+x]
#define _SE showingEvent =

using namespace std;

ZorkUL::ZorkUL(QWidget *parent) : QMainWindow(parent), p("Main Character", 0, 0, "player.png"), changedRoom(true) {
    createGame();
    setWindowTitle(QString::fromUtf8("Horror/Action/Turn game written in C++ and Qt!!!"));
    setStyleSheet("background-color:black;");
    setFixedSize(1100, 600);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
}

ZorkUL::~ZorkUL() {
    for (vector<Room*>::iterator i = rooms.begin(); i != rooms.end(); i++) {
        delete (*i);
    }
    for (auto i = gateways.begin(); i != gateways.end(); i++) {
        delete (*i);
    }
    for (map<int, Event*>::iterator i = events.begin(); i != events.end(); i++) {
        delete i->second;
    }
    for (auto i = items.begin(); i != items.end(); i++) {
        delete (*i);
    }

    delete timer;
}

void ZorkUL::createGame() {
    Room *r1, *r2, *r3, *r4, *r5, *r6, *r7;
    Room *c1, *c2, *c3, *c4, *c5, *c6, *c7;

    r1 = new Room("Cell", QRect(548, 0, 103, 210), "R1.png", 30, 80);
    r2 = new Room("Cell office", QRect(400, 0, 148, 210), "R2.png", 70, 70);
    r3 = new Room("Dark Room", QRect(400, 210, 251, 115), "R3.png", 15, 85);
    r4 = new Room("Storage Room", QRect(129, 0, 222, 325), "R4.png", 150, 200);
    r5 = new Room("Surgical Room", QRect(0, 325, 351, 275), "R5.png", 285, 160);
    r6 = new Room("Boxes Room", QRect(400, 325, 400, 226), "R6.png", 185, 160);
    r7 = new Room("Courtyard", QRect(651, 0, 149, 325), "R7.png", 40, 240);
    c1 = new Room("Initial Corridor", QRect(351, 0, 49, 161), "C1.png", 15, 70);
    c2 = new Room("Second Corridor", QRect(351, 161, 49, 164), "C2.png", 15, 30);
    c3 = new Room("Third Corridor", QRect(351, 325, 49, 141), "C3.png", 15, 25);
    c4 = new Room("Corridor Corner", QRect(351, 466, 49, 134), "C4.png", 15, 15);
    c5 = new Room("First Corridor on the Right", QRect(400, 551, 141, 49), "C5.png", 15, 15);
    c6 = new Room("Middle Corridor on the Right", QRect(541, 551, 129, 49), "C6.png", 15, 15);
    c7 = new Room("Last Corridor", QRect(670, 551, 130, 49), "C7.png", 15, 15);

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

    createGateway(0, r1, r2);
    createGateway(1, r2, c1);
    createGateway(2, c1, c2);
    createGateway(3, c2, r3);
    createGateway(4, r3, r7);
    createGateway(5, c2, r4);
    createGateway(6, c2, c3);
    createGateway(7, c3, c4);
    createGateway(8, c4, r5);
    createGateway(9, c4, c5);
    createGateway(10, c5, c6);
    createGateway(11, c6, c7);
    createGateway(12, c6, r6);

    r1->addViewableRoom(r2);
    r2->addViewableRoom(r1);
    c1->addViewableRooms({c2, c3, c4});
    c2->addViewableRooms({c1, c3, c4});
    c3->addViewableRooms({c1, c2, c4});
    c4->addViewableRooms({c1, c2, c3, c5, c6, c7});
    c5->addViewableRooms({c4, c6, c7});
    c6->addViewableRooms({c4, c6, c7});

    createEvents();

    items.push_back(new Item(0, "i", "d"));

    currentRoom = r1;
    _SE events[1];
    p.setPosition(currentRoom->getPlayerPositionAbs());
}

void ZorkUL::createEvents() {
    EVENT(1, "You feel your head pounding and slowly open your eyes.\n"
            "You sit up and look around. You were lying in a metal bed."
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
        OPTION(26, "Continue down the hall")
        }
    );

    EVENT(23, "You try the door, but it is locked."
              "On the wall, besides it, you see a digital lock. You try the passcode \"1234\", but it does not work.",
        {
        OPTION(22, "Check door on the right"),
        OPTION(21, "Go back on the corridor"),
        OPTION(26, "Continue down the hall")
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
        OPTION(25, "Enter room"),
        OPTION(82, "Enter room"),
        OPTION(23, "Check door on the left"),
        OPTION(21, "Go back on the corridor"),
        OPTION(26, "Continue down the hall")
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
              "The world turns to black.\n"
              "YOU LOST.", {}
    );

    EVENT(28, "You quickly enter the room and close the door. You hear steps approaching, and then some beeps and a door opening and closing.\n"
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
              "The world turns to black.\n"
              "YOU LOST.", {}
    );

    EVENT(33, "He is much stronger than you are.\n"
              "He hits you with the pipe that you should have used against him.\n"
              "The world turns to black.\n"
              "YOU LOST.", {}
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
        OPTION(21, "Go back"),
        OPTION(38, "Continue down the hall")
        }
    );

    EVENT(36, "You reaches the corner of the corridor. There is a door to your left and the corridor continues on your right.",
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
        OPTION(38, "Go to the corner of the corridor")
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
        OPTION(42, "Go towards the corner of the corridors"),
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

    EVENT(57, "You are between the door and the window again.",
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

    EVENT(66, "You hear noise inside the surgical room. The person you heard earlier must have come back to it",
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
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(70, "Wrong password.",
        {
        OPTION(70, "Try \"6789\""),
        OPTION(72, "See the paper you found on the bulletin board"),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(71, "Wrong password.",
        {
        OPTION(72, "See the paper you found on the bulletin board"),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(72, "In the paper, you read \"3109\"",
        {
        OPTION(70, "Try \"3109\""),
        OPTION(21, "Keep walking"),
        OPTION(38, "Turn around and go down the corridor")
        }
    );

    EVENT(73, "Here you go. The door is unlocked.",
        {
        OPTION(74, "Enter room"),
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
              "Run, Forest, RUN!\n"
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
        OPTION(95, "Go back into room"),
        OPTION(96, "Use pipe"),
        OPTION(97, "Use scalpel")
        }
    );

    EVENT(94, "He is way bigger than you.\n"
              "He punches you in the face.\n"
              "The world turns to black.\n"
              "YOU LOST", {}
    );

    EVENT(95, "You try to scape but he catches you.\n"
              "The world turns to black.\n"
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
              "The world turns to black.\n"
              "YOU LOST", {}
    );

    EVENT(98, "When you touches the knob, the door suddenly open. There is a man in a bloody apron in front of you.",
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

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
    printWelcome();
    show();
}

void ZorkUL::printWelcome() {
    cout << "start" << endl;
    cout << endl;
    cout << currentRoom->toString() << endl;
}

void ZorkUL::changeRoom(Gateway* gateway) {

    Room* nextRoom = gateway->getOtherRoom(currentRoom);

    if (nextRoom != NULL) {
        changedRoom = true;
        currentRoom = nextRoom;
        timer->start(ANIMATION_DELAY);
    }
}

void ZorkUL::performOption(Event::Option* option) {
    switch (option->id) {
        case 0:
            changeRoom(gateways[0]);
            _SE events[1];
            break;
        case 1:
            changeRoom(gateways[0]);
            _SE events[0];
            break;
        case 2:
            changeRoom(gateways[1]);
            _SE events[2];
            break;
        case 3:
            /*static bool status = false;
            if (!status) {
                cout << "You checked the plant, UHUUUUL!" << endl;
                p.addItem(new Item(0, "key", "old key"));
                p.addItem(new Item(1, "b key", "old b key"));
                status = true;
            } else {
                cout << "You already have the items" << endl;
            }*/
            cout << "Checked plant" << endl;
            p.addItem(items[0]);
            events[2]->disableOption(option);
            cout << p.toString() << endl;
            break;
        case 4:
            changeRoom(gateways[1]);
            _SE events[1];
            break;
        case 5:
            cout << "Door is locked." << endl;
            break;
        case 6:
            changeRoom(gateways[2]);
            _SE events[3];
            break;
        case 7:
            cout << "Door is locked." << endl;
            break;
        case 8:
            cout << "Door is locked." << endl;
            break;
        case 9:
            changeRoom(gateways[2]);
            _SE events[2];
            break;
        default:
            cout << "Shit happens..." << endl;
            break;
    }
}

inline void ZorkUL::createGateway(int id, Room* r1, Room* r2) {
    Gateway* g = new Gateway(id, r1, r2);
    gateways.push_back(g);
    r1->addGateway(g);
    r2->addGateway(g);
}

inline void ZorkUL::drawItems(QPainter& painter, vector<Item*> items) {
    for (Item* i : items) {
        painter.drawImage(i->getRect(), i->getImage());
    }
}

inline void ZorkUL::EVENT(int id, string message, initializer_list<Event::Option*> list) {
    Event *e = new Event(id, message);
    for (auto i : list)
        e->addOption(i);
    events[id] = e;
}

inline Event::Option* ZorkUL::OPTION(int id, string message) {
    return new Event::Option(id, message);
}

void ZorkUL::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter painter(this);

    vector<Room*> darkRooms = rooms;

    FINDREMOVE(darkRooms, currentRoom)
    painter.drawImage(currentRoom->getRect(), currentRoom->getImage());
    drawItems(painter, currentRoom->getItems());
    for (Room* room : currentRoom->getViewableRooms()) {
        painter.drawImage(room->getRect(), room->getImage());
        drawItems(painter, room->getItems());
        FINDREMOVE(darkRooms, room)
    }

    for (Room*& room : darkRooms) {
        QImage src = room->getImage();
        painter.drawImage(room->getRect(), src);
        drawItems(painter, room->getItems());
    }

    for (Room*& room : darkRooms) { // Separate loop to draw items below all the overlays correctly
        static const QPixmap origOverlay(ASSET((string)"overlay.png"));
        painter.drawPixmap(room->getRect(), origOverlay);
    }

    painter.drawImage(p.getRect(), p.getImage());

    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(QColor::fromRgb(255,255,204));
    QRect tRect(810, 20, 280, 350);
    string m = showingEvent->getMessage();
    painter.drawText(tRect, Qt::AlignHCenter | Qt::TextWordWrap, QString::fromStdString(m));

    painter.setPen(QColor::fromRgb(204,255,255));
    tRect.translate(0, 370);
    auto options = showingEvent->getOptions();
    string s;
    for (unsigned int i=0; i < options.size(); i++) {
        s += to_string(i + 1) + ". " + options[i]->label + "\n";
    }
    painter.drawText(tRect, Qt::AlignJustify | Qt::TextWordWrap, QString::fromStdString(s));

#ifdef CONSOLE_OUTPUT
    cout << m << endl;
    cout << s << endl;
#endif

}

void ZorkUL::mouseReleaseEvent(QMouseEvent* e) {
    cout << "Button:" << e->button() << "  x:" << e->x() << "  y:" << e->y() << endl;
}

void ZorkUL::keyPressEvent(QKeyEvent *e) {
    if (!p.isMoving()) {
        vector<Event::Option*> options = showingEvent->getOptions();
        if ((e->key() > Qt::Key_0) && (e->key() < (int) (Qt::Key_1 + options.size()))) {
            changedRoom = false;
            Event::Option* option = options[e->key() - Qt::Key_1];
            performOption(option);
            repaint();
        } else {
            cout << "key is not an option" << endl;
        }
    }
}

void ZorkUL::animate() {
    if (!p.isMoving()) {
        p.setAnimation(currentRoom->getPlayerPositionAbs(), ANIMATION_STEP);
    }
    bool finished = p.update();
    if (finished) {
        timer->stop();
    }
    repaint();
}

#undef ROOM
#undef CORR
#undef _SE
