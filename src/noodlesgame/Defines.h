#ifndef DEFINES_H
#define DEFINES_H

#include <vector>

#undef CONSOLE_OUTPUT

#define ASSET_LOCATION "../../assets/"
#define ASSET(x) (ASSET_LOCATION + x).c_str()
#define ANIMATION_DELAY 30

template<typename T>
inline void FINDREMOVE(std::vector<T>& v, T& i) {
    for (typename std::vector<T>::iterator j = v.begin(); j != v.end(); j++) {
        if (*j == i) {
            v.erase(j);
            break;
        }
    }
}

#endif // DEFINES_H
