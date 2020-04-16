# Project 2048

A remake of the popular "2048" mobile game to the good old command line interface.

Windows and DOS versions available.

This DOS version is designed to be used with DSx86 DOS emulator on Nintendo(R) DS.

# Build

Please use Borland(R) Turbo C++ 3.0 to build this.

# Features

* Self-explanatory "2048" game
* Good old command line interface
* ~~Selectable grid sizes from 3x3 to 8x8~~ It's now fixed size 4x4 'cause the NDS screen is small
* Save datas in RAM and file

# Notice

* The delay of "Loading" "Saving" is just time delay. It doesn't do anything that requires such a long time but, well, modern computers are just TOO fast for such a game so we need a bit compensate right?
* There is a critical bug in the gameplay. If you have [8 2 2 2] and you press left, would it become [8 4 2 -] or [8 2 4 -]? I didn't know (in fact I even don't know after the years), so it seems that it will become [8 4 - 2] in this program, which is obviously wrong. Well, who cares, nobody plays it anyway. Maybe I'll fix it up if I remember.

# License
WTFPLv2

SaltfishAmi 2014/12/17
