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

# Define the source directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src/GBEmu)
set(INCLUDE_DIR ${SRC_DIR}/include)

# Specify source and header files
set(SOURCES
    ${SRC_DIR}/Cartridge.cpp 
    ${SRC_DIR}/Clock.cpp
    ${SRC_DIR}/CPU.cpp
    ${SRC_DIR}/CPU_OpcodeFuncs.cpp
    ${SRC_DIR}/Instruction.cpp
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Memory.cpp
    ${SRC_DIR}/SerialDebug.cpp
)

set(HEADERS
    ${INCLUDE_DIR}/Cartridge.h
    ${INCLUDE_DIR}/Clock.h
    ${INCLUDE_DIR}/CPU.h
    ${INCLUDE_DIR}/Globals.h
    ${INCLUDE_DIR}/Graphics.h
    ${INCLUDE_DIR}/Instruction.h
    ${INCLUDE_DIR}/Memory.h
    ${INCLUDE_DIR}/Registers.h
    ${INCLUDE_DIR}/SerialDebug.h
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

# Force GLFW to build as a static library
set(GLFW_BUILD_SHARED OFF CACHE BOOL "Build GLFW as a static library" FORCE)

# Add GLFW as a subdirectory to the build process
add_subdirectory(vendor/glfw)

# Define the executable
add_executable(GBEmu ${SOURCES} ${HEADERS})

# Link GLFW to GBEmu as a static library
target_link_libraries(GBEmu PRIVATE glfw)

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

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GBEmu)
