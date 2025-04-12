
# GBEmu

A gameboy DMG-01 emulator written in C++ using SDL2 and SPDLog for logging.




## Dependencies
- Cmake (Version 3.28.3 or higher)
- SDL2
- SPDLog

All dependencies are added to the project as git submodules and compile to static libraries. After cloning the repository, run the following command to add the repos to the project.
```bash
    git submodule update --init --recursive
```

## Installing
Verify that after cloning the repository you have added the dependency submodules (see: [Dependencies](#Dependencies))
### Ubuntu/Debian based distros
Enter the GBEmu root directory and run the following command to install:
```bash
    cmake CMakeLists.txt
```
### Windows
First download and install the latest version of [CMake](https://cmake.org/download/) for your system,
then run the following command in the GBEmu root directory:
```cmd
    cmake CMakeLists.txt
```
    