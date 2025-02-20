#ifndef CLK_H
#define CLK_H
#include <chrono>
#include <thread>
#include <iostream>
#include "Globals.h"
#include "CPU.h"
#define _TEST

constexpr double T_CYCLE_HZ = 4194304.0; //4.194304 MHz
constexpr double T_CYCLE_NS = (1.0 / T_CYCLE_HZ) * 1e9; //238.418 ns per cycle
constexpr double M_CYCLE_NS = 4.0 * T_CYCLE_NS;

class Clock
{
public:
	// Takes an std::function pointer to cpu's tick() function
	static void tick();
};

#endif