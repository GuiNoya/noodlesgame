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

    r1 = new Room("cell", "You're in a cell. There is a door in front of you.", QRect(548, 0, 103, 210), "R1.png", 30, 80);
    r2 = new Room("cell room", "You are in the cell room. There is a desk on your side, and a door in front of you.", QRect(400, 0, 148, 210), "R2.png", 70, 70);
    r3 = new Room("", "", QRect(400, 210, 251, 115), "R3.png", 15, 85);
    r4 = new Room("", "", QRect(129, 0, 222, 325), "R4.png", 150, 200);
    r5 = new Room("", "", QRect(0, 325, 351, 275), "R5.png", 285, 160);
    r6 = new Room("", "", QRect(400, 325, 400, 226), "R6.png", 185, 160);
    r7 = new Room("", "", QRect(651, 0, 149, 325), "R7.png", 40, 240);
    c1 = new Room("corridor east", "You are in an end of a corridor. There is a plant on your right, with a door beside it, and the cell room on your left.", QRect(351, 0, 49, 161), "C1.png", 15, 70);
    c2 = new Room("corridor middle", "You are in the middle of the corridor. There is a door in your right and another on your left.", QRect(351, 161, 49, 164), "C2.png", 15, 30);
    c3 = new Room("", "", QRect(351, 325, 49, 141), "C3.png", 15, 25);
    c4 = new Room("", "", QRect(351, 466, 49, 134), "C4.png", 15, 15);
    c5 = new Room("", "", QRect(400, 551, 141, 49), "C5.png", 15, 15);
    c6 = new Room("", "", QRect(541, 551, 129, 49), "C6.png", 15, 15);
    c7 = new Room("", "", QRect(670, 551, 130, 49), "C7.png", 15, 15);

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
    _SE 0;
    p.setPosition(currentRoom->getPlayerPositionAbs());
}

void ZorkUL::createEvents() {
    Event *e = new Event(0, "Cela");
    e->addOption(new Event::Option(0, "Pass through door"));
    events[0] = e;

    e = new Event(1, "Salinha");
    e->addOption(new Event::Option(1, "Go to the cell"));
    e->addOption(new Event::Option(2, "Go through the other door"));
    events[1] = e;

    e = new Event(2, "Corredor 1");
    e->addOption(new Event::Option(3, "Check the plant"));
    e->addOption(new Event::Option(4, "Go back to the cell room"));
    e->addOption(new Event::Option(5, "Go through the door on your right"));
    e->addOption(new Event::Option(6, "Continue in the corridor"));
    events[2] = e;

    e = new Event(3, "Corredor 2");
    e->addOption(new Event::Option(7, "Go to the door on your left"));
    e->addOption(new Event::Option(8, "Go to the door on your right"));
    e->addOption(new Event::Option(9, "Go back in the corridor"));
    events[3] = e;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
    printWelcome();
    _SE events[0];
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

string ZorkUL::getMessage() {
    string m = currentRoom->getDescription();
    return m;
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

    string m = getMessage();

    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(Qt::lightGray);
    QRect tRect(810, 20, 280, 200);
    m += "\n\n";
    m += showingEvent->getMessage();
    painter.drawText(tRect, Qt::AlignJustify | Qt::TextWordWrap, QString::fromStdString(m));

    tRect.translate(0, 280);
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
