## Pacman-Reloaded

Pacman Reloaded is a remake of original Pacman game, created with intention of overall improvement of Arrowgance Studios (former xd-development) game-programming skills.

__Language:__ C++  
__2D Graphic Engine:__ Allegro 5.0.10

## Build

### CMake - Windows
_Building with CMake is currently only supported on Windows._

Supported compilers:
- Visual Studio 2019
- Visual Studio 2022

Building in both 32- and 64-bit mode should be supported, although the 32-bit build wasn't tested.

Requires CMake 3.15+. 
To obtain it, either:
- download it from official distributor [here](https://cmake.org/download/)
- install it using pip `pip install cmake` or `pip install --user cmake` if you don't have root privilages
- build and install from [sources](https://github.com/Kitware/CMake)

To build and install Pacman, run in root project folder following commands:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
Pacman will built to `build/bin` directory with necessary assets copied, ready to be launched.

### Debian/Ubuntu Linux:

```bash
apt-get install build-essential liballegro5-dev
make
./pacman
```

## Links
1. [Rules of Well-arranged code writing](RULES%20OF%20WELL-ARRANGED%20CODE%20WRITING.md)
2. [General Concept](GENERAL_CONCEPT.md)
