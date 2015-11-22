/* Includes ------------------------------------------------------------------*/
#include "apl/main.h"

#include "hal/mcu.hpp"
#include "hal/dma.hpp"
#include "hal/gio.hpp"
#include "hal/rcc.hpp"

int main(void)
{
	HAL::RCCM::initClocks();
	HAL::MCU::init();

	HAL::GIO::configurePin(HAL::GIO::Port::PORTE, 14, HAL::GIO::Mode::OUTPUT,
			HAL::GIO::Pullups::PULL_UP, HAL::GIO::Type::PUSH_PULL,
			HAL::GIO::Speed::FAST, 0);

	while (1)
	{
		toggle(HAL::GIO::Port::PORTE, 14);
		HAL::MCU::delayTicks(100);
	}
}
