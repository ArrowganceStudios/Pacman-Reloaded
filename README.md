## Pacman-Reloaded

Pacman Reloaded is a remake of original Pacman game, created with intention of overall improvement of Arrowgance Studios (former xd-development) game-programming skills.

__Language:__ C++  
__2D Graphic Engine:__ Allegro 5.0.10

## Build

### CMake
Requires CMake 3.14+. 
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
Pacman will then be built and installed to `PROJECT_ROOT/bin` directory and should be ready to be played.

#### Note for Windows users:
When running `cmake ..` command for generating build files, and you want to use MSVC to compile Pacman, 
you first have to run vcvarsall.bat ([see where to find it](https://social.msdn.microsoft.com/Forums/en-US/1071be0e-2a46-4c30-9546-ea9d7c4755fa/where-is-vcvarsallbat-file?forum=visualstudiogeneral)) in the shell you'll use and then choose one of the following generators using -G switch.
```bash
cmake -G"Visual Studio <VERSION> <RELEASE YEAR>" ..
cmake -G"NMake Makefiles" ..
cmake -G"NMake Makefiles JOM" .. // if you have jom build system installed
```
`"Visual Studio <VERSION> <RELEASE YEAR>"` can be for example `"Visual Studio 16 2019"`. To find out all generators available, type `cmake --help`.

### Debian/Ubuntu Linux:

```bash
apt-get install build-essential liballegro5-dev
make
./pacman
```

## Links
1. [Rules of Well-arranged code writing](RULES%20OF%20WELL-ARRANGED%20CODE%20WRITING.md)
2. [General Concept](GENERAL_CONCEPT.md)
