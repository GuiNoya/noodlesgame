#ifndef DEFINES_H
#define DEFINES_H

#include <vector>

#undef CONSOLE_OUTPUT // Used to print the event and option to the standard output

#define ASSET_LOCATION "../../assets/"
#define ASSET(x) (ASSET_LOCATION + x).c_str() // Used to load assets
#define ANIMATION_DELAY 30 // Delay in ms to run the main loop

// Inline funtion to find and remove an item in a vector
template<typename T>
inline void FINDREMOVE(std::vector<T>& v, T& i) {
    for (typename std::vector<T>::iterator j = v.begin(); j != v.end(); ++j) {
        if (*j == i) {
            v.erase(j);
            break;
        }
    }
}

#endif // DEFINES_H
