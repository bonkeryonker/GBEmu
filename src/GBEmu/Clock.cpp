#include "Clock.h"

void Clock::tick(CPU& cpuRef)
{
	if (cpuRef.isHalted())
		return;

	// Start clock
	auto startTime = std::chrono::high_resolution_clock::now();

	// Run CPU.tick(), save the amount of t-cycles the operation requires
	unsigned short operationCycleCount = cpuRef.tick();

	// Stop the clock
	auto endTime = std::chrono::high_resolution_clock::now();

	// Calculate how long CPU.tick() took in nanoseconds
	std::chrono::nanoseconds elapsed = endTime - startTime;

	// Calculate remaining time to sleep
	auto sleepTime = (std::chrono::nanoseconds(static_cast<int>(M_CYCLE_NS)) * operationCycleCount) - elapsed;

#ifdef CLOCK_TRACE
	printf("Func took %lld ns, sleeping for the remaining %lld ns\n", elapsed.count(), sleepTime.count());
#endif
	if (sleepTime.count() > 0)
	{
		std::this_thread::sleep_for(sleepTime);
	}
	else
	{
#ifdef _DEBUG
		printf("Overran clock by %lld ns!\n(Took: %lld ns)\n", -1 * sleepTime.count(), elapsed.count());
#endif
	}
}