#include <stdio.h>
#include <memory>
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"

int main()
{
	std::shared_ptr<RAM> ram_ptr = std::make_shared<RAM>();
	CPU c(ram_ptr);
	return 0;
}