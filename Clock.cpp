#include "Clock.h"

void Clock::tick()
{
	// Start clock
	auto startTime = std::chrono::high_resolution_clock::now();

	// Run CPU.tick(), save the amount of t-cycles the operation requires
	u8 operationCycleCount = 1;// = cpu.tick();

	// Stop the clock
	auto endTime = std::chrono::high_resolution_clock::now();

	// Calculate how long CPU.tick() took in nanoseconds
	std::chrono::nanoseconds elapsed = endTime - startTime;

	// Calculate remaining time to sleep
	auto sleepTime = (std::chrono::nanoseconds(static_cast<int>(M_CYCLE_NS)) * operationCycleCount) - elapsed;

#if defined _DEBUG || defined _TEST
	printf("Func took %lld ns, sleeping for the remaining %lld ns\n", elapsed.count(), sleepTime.count());
#endif
	if (sleepTime.count() > 0)
	{
		std::this_thread::sleep_for(sleepTime);
	}
}