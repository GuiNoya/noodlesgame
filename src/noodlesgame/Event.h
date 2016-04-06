#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

// Represents an Event in the game
// the game is all linked by events
class Event {

    public:
        // struct to store an option
        struct Option {
            int id;
            string label;
            bool enabled = true;
            Option(int id, string label) : id(id), label(label) {}
        };

        Event(int id, string message);
        ~Event();
        int getId() const;
        string getMessage() const;
        vector<Option*> getOptions() const;
        void setMessage(string s);
        void addOption(Option *option);
        void disableOption(int i);
        void enableOption(int i);
        vector<Option*> getEnabledOptions() const;

    private:
        int id;
        string message;
        vector<Option*> options;
};

#endif // EVENT_H
