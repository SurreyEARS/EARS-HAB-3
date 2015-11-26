/* Includes ------------------------------------------------------------------*/
#include "apl/main.h"

#include "hal/dac.hpp"
#include "hal/mcu.hpp"
#include "hal/dma.hpp"
#include "hal/gio.hpp"
#include "hal/rcc.hpp"

uint16_t dacValues[] = {
		0x0,
		0x4,
		0x8,
		0xC,
		0x10,
		0x14,
		0x18,
		0x1C,
		0x20,
		0x24,
		0x28,
		0x2C,
		0x30,
};

int main(void)
{
	HAL::RCCM::initClocks();
	HAL::MCU::init();

	HAL::GIO::configurePin(HAL::GIO::Port::PORTE, 14, HAL::GIO::Mode::OUTPUT,
			HAL::GIO::Pullups::PULL_UP, HAL::GIO::Type::PUSH_PULL,
			HAL::GIO::Speed::FAST, 0);

	HAL::DAC::configure(HAL::DAC::Trigger::SOFTWARE, false, true);
	HAL::DAC::SINGLE::startDMA(dacValues, 13);
	HAL::DAC::SINGLE::enable();

	HAL::DAC::SINGLE::setData(0xFFF);
	HAL::DAC::SINGLE::swTrigger();

	while (1)
	{
		toggle(HAL::GIO::Port::PORTE, 14);
		HAL::DAC::SINGLE::swTrigger();
		HAL::MCU::delayTicks(300);
	}
}
