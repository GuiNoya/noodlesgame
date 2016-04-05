#ifndef QTHGAME_CONFIG
#define QTHGAME_CONFIG

#undef CONSOLE_OUTPUT

#define ASSET_LOCATION "../../assets/"
#define ASSET(x) (ASSET_LOCATION + x).c_str()
#define ANIMATION_DELAY 33
#define FINDREMOVE(v, i) for (auto j = v.begin(); j != v.end(); j++) {if (*j == i) {v.erase(j); break;}}

#endif // QTHGAME_CONFIG
