#ifndef QTHGAME_CONFIG
#define QTHGAME_CONFIG

#define ASSET(x) ("../../assets/" + x).c_str()
#define FINDREMOVE(v, i) for (auto j = v.begin(); j != v.end(); j++) {if (*j == i) {v.erase(j); break;}}

#endif // QTHGAME_CONFIG
