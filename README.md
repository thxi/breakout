# Breakout

![gameplay](https://i.imgur.com/aN8CFBs.png?1)

A simple [Atari Breakout](<https://en.wikipedia.org/wiki/Breakout_(video_game)>) clone written in C using [raylib](https://www.raylib.com/)

# TODO

make release and debug builds

# Install

TODO:
You can download the game on releases page

## Manual

To build the game manually:

- copy the repository and its submodules([raylib](https://github.com/raysan5/raylib))

```bash
git clone --recurse-submodules https://github.com/thxi/breakout
```

this might take some time

- make a `build` directory inside the project root and `cd` into it

```bash
cd breakout
mkdir build
cd build
```

- generate cmake build files

```bash
cmake ..
```

- build the project

```bash
make
```

- run the game

```bash
./breakout
```

`Note`: I also needed to install some dependencies on ubuntu:
(See `make` output for details)

```bash
sudo apt-get install xorg-dev
```
