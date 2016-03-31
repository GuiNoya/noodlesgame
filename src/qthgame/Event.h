#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Event {

    public:
        // This can be changed to use callback functions, a little more tricky
        struct Option {
            int id;
            string label;
            Option(int id, string label) : id(id), label(label) {}
        };

        Event(int id, string message);
        ~Event();
        string getId();
        string getMessage();
        vector<Option*> getOptions();
        void setMessage(string s);
        void addOption(Option *option);
        void disableOption(int o);
        void disableOption(Option* o);
        void reenableOption(int o);
        void reenableOption(Option* o);

    private:
        int id;
        string message;
        vector<Option*> options;
        map<int, Option*> disabledOptions;

};

#endif // ACTION_H
