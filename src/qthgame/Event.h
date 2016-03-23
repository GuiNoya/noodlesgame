#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>

using namespace std;

class Event {

    public:
        // This can be changed to use callback functions, a little more tricky
        struct Option {
            int id;
            string label;
            Option(int id, string label) : id(id), label(label) {}
        };

        Event(string message);
        ~Event();
        string getMessage();
        vector<Option*> getOptions();
        void addOption(Option *option);

    private:
        string message;
        vector<Option*> options;

};

#endif // ACTION_H
