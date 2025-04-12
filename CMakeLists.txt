cmake_minimum_required(VERSION 3.28.3)
project(GBEmu)

# Disable predefined targets like ALL_BUILD and INSTALL
set(CMAKE_DISABLE_PREDEFINED_TARGETS TRUE)

# Visual Studio specific: Set GBEmu as the startup project
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                 PROPERTY VS_STARTUP_PROJECT GBEmu)
endif()

# Set the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Define the source directory paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src/GBEmu)
set(INCLUDE_DIR ${SRC_DIR}/include)
set(CORE ${SRC_DIR}/core)
set(GB ${SRC_DIR}/gb)

# Specify source and header files
set(SOURCES
    ${GB}/Cartridge.cpp 
    ${GB}/Clock.cpp
    ${GB}/CPU.cpp
    ${GB}/CPU_OpcodeFuncs.cpp
    ${GB}/Instruction.cpp
    ${GB}/Memory.cpp
    ${GB}/SerialDebug.cpp
    ${GB}/Gameboy.cpp
    ${GB}/PPU.cpp
    ${CORE}/Log.cpp
    ${CORE}/Window.cpp
    ${CORE}/Application.cpp
    ${SRC_DIR}/main.cpp

)

set(HEADERS
    ${INCLUDE_DIR}/Cartridge.h
    ${INCLUDE_DIR}/Clock.h
    ${INCLUDE_DIR}/CPU.h
    ${INCLUDE_DIR}/Globals.h
    ${INCLUDE_DIR}/Window.h
    ${INCLUDE_DIR}/Instruction.h
    ${INCLUDE_DIR}/Memory.h
    ${INCLUDE_DIR}/Registers.h
    ${INCLUDE_DIR}/SerialDebug.h
    ${INCLUDE_DIR}/Log.h
    ${INCLUDE_DIR}/Graphics.h
    ${INCLUDE_DIR}/Gameboy.h
    ${INCLUDE_DIR}/Application.h
    ${INCLUDE_DIR}/PPU.h
)

# Include the header directory
include_directories(${INCLUDE_DIR})

# Set platform-specific settings
if(WIN32)
    message(STATUS "Building for windows")
    set(PLATFORM_DIR "windows")
elseif(UNIX)
    message(STATUS "Building for linux")
    set(PLATFORM_DIR "linux")
endif()

# Define the executable
add_executable(GBEmu ${SOURCES} ${HEADERS})

### SDL2
# Configure
set(SDL2_BUILD_TESTS OFF CACHE BOOL "Disabling SDL2 tests" FORCE)
set(SDL2_BUILD_EXAMPLES OFF CACHE BOOL "Disabling SDL2 examples" FORCE)
set(SDL2_DISABLE_INSTALL TRUE CACHE BOOL "Disabling SDL2 install target" FORCE)
set(SDL2_DISABLE_TEST TRUE CACHE BOOL "Disabling SDL2 test project" FORCE)
set(SDL2_BUILD_SHARED OFF CACHE BOOL "Disabling SDL2 shared library" FORCE)
set(SDL2_BUILD_STATIC ON CACHE BOOL "Enabling SDL2 static library" FORCE)
# Add subdirectory
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
# Link to project
target_link_libraries(GBEmu PRIVATE SDL2::SDL2main)
target_link_libraries(GBEmu PRIVATE SDL2::SDL2-static)

### SPDLog
add_subdirectory(vendor/spdlog)
target_link_libraries(GBEmu PRIVATE spdlog)

# Set output directories for the executable
set_target_properties(GBEmu PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/builds/${PLATFORM_DIR}/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/builds/${PLATFORM_DIR}/release
    COMPILE_PDB_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/builds/${PLATFORM_DIR}/debug/obj
    COMPILE_PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/builds/${PLATFORM_DIR}/release/obj
    OBJECT_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/builds/${PLATFORM_DIR}/debug/obj
)

# Set build-specific settings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
    set(BUILD_TYPE_DIR "debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
    set(BUILD_TYPE_DIR "release")
else()
    set(BUILD_TYPE_DIR "unknown")
endif()

#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GBEmu)
