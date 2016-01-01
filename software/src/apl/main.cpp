/* Includes ------------------------------------------------------------------*/
#include "apl/main.hpp"

#include <apl/cfg.hpp>

#include "hal/dac.hpp"
#include "hal/mcu.hpp"
#include "hal/dma.hpp"
#include "hal/gio.hpp"
#include "hal/rcc.hpp"
#include "hal/crc.hpp"

#include <apl/ssm.hpp>

#include <asl/nmp.hpp>
#include <asl/cgm.hpp>
#include <asl/rop.hpp>
#include <asl/nvm.hpp>

#include <hal/nvc.hpp>
#include <hal/usb.hpp>

#include <vector>

int main(void)
{
	/* STAGE A: Mandatory initialisation
	 * Load as little as possible config data using CGM
	 * Change the system clock source to the PLL
	 * Initialise SysTick. */
	APL::SSM::init();
	HAL::RCCM::initClocks();
	HAL::MCU::init();

	/* STAGE B: Secondary initialisation
	 * Load config data using CGM
	 * Configure various module settings */

	ASL::CGM::configure(APL::CFG::initLib);

	/* STAGE C: External status check
	 * Decide whether to start hot or cold */
	APL::SSM::checkHotStart();

	/* STAGE D: Safety system tests
	 * Confirms that all internally testable modules are working.
	 * COLD START ONLY. Hot start omits this section for speed. */
	bool initSuccess = true;
	if (APL::SSM::State::COLD_START == APL::SSM::getState())
	{
		if (!HAL::CRC::test())
		{
			initSuccess = false;
		}

		if (!HAL::NVC::test())
		{
			initSuccess = false;
		}

		if (!HAL::DMA::test())
		{
			initSuccess = false;
		}

		//if (!ASL::ROP::test())
		{
			//initSuccess = false;
		}

		if (!ASL::NMP::test())
		{
			initSuccess = false;
		}
	}

	if (initSuccess)
	{
		APL::SSM::clearCondition(APL::SSM::Fault::PROCESSOR_INIT);
	}

	//TODO Implement this!
	APL::SSM::clearCondition(APL::SSM::Fault::WATCHDOG);

	/* STAGE E: Infinite loop
	 * Main application execution. */
	while (true)
	{
		toggle(HAL::GIO::Port::PORTE, 14);
		HAL::MCU::delayTicks(250);
	}
}
