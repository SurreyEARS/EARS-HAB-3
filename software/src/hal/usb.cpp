/*
 * usb.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#include <hal/usb.hpp>
#include <mal/device_usb.hpp>

#include <hal/mcu.hpp>

namespace HAL
{
namespace USB
{

void init()
{
	using MAL::F3C::USB;

	/* TODO Find out what the hell is going on with the USB... */

	USB.CNTR.B.PWDN = 0U;
	/* Required time for startup and settling is 1uS but let's be safe */
	HAL::MCU::delayMicroseconds(3U);
	USB.CNTR.B.FRES = 0U;

	USB.ISTR.R = 0b1000000001111111;

	HAL::MCU::delayTicks(50U);

	/* Enable the device */
	USB.DADDR.B.EF = 1U;

	USB.EP0R.R = 0b1011001000110000;

	/* Initialise Endpoint 0 as a control endpoint with address 0
	USB.EP0R.B.EPTYPE = 0x01U;
	USB.EP0R.B.EP_KIND = 0U;
	USB.EP0R.B.EA = 0x0U;
	USB.EP0R.B.STAT_RX = 0x3U; */
}

}
}
