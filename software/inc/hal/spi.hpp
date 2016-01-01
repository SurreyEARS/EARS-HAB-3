/*
 * spi.hpp
 *
 *  Created on: Dec 27, 2015
 *      Author: James
 */

#pragma once

#include <mal/device_spi.hpp>

namespace HAL
{
namespace SPI
{

class SpiBase
{
	// GIO for CS
	// startup time
	// ideal polling frequency
};

class L3GD20: public SerialPeripheral
{
public:
	struct SpiL3GD20Init
	{
		uint8_t CTRL_REG1;
		uint8_t CTRL_REG2;
		uint8_t CTRL_REG3;
		uint8_t CTRL_REG4;
		uint8_t CTRL_REG5;
	};

	static void configure(SpiL3GD20Init& init);

protected:

private:

};

}
}
