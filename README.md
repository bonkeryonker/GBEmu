
# GBEmu

A gameboy DMG-01 emulator written in C++ using GLFW and imGUI.




## Dependencies
- Cmake (Version 3.28.3 or higher)
- GLFW
- SPDLog

All dependencies are added to the project as git submodules and compile to static libraries. After cloning the repository, run the following command to add the repos to the project.
```bash
    git submodule update --init --recursive
```

### Ubuntu/Debian based distros
GLFW requires both the Wayland and xkbcommon dev packages installed. If the project fails to build, install these with the following command below (see: [Compiling GLFW](https://www.glfw.org/docs/3.3/compile.html))
```bash
  sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules
```

## Installing
Verify that after cloning the repository you have added the dependency submodules (see: [Dependencies](#Dependencies))
### Ubuntu/Debian based distros
Enter the GBEmu root directory and run the following command to install:
```bash
    cmake CMakeLists.txt
```
### Windows
Enter the GBEmu root directory and run the following command to install:
```cmd
    cmake CMakeLists.txt
```
    