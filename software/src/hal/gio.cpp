/*
 * gio.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#include <hal/gio.hpp>

#include <hal/generics.hpp>
#include <ext/bitops.hpp>
#include <mal/device.hpp>

using namespace MAL::F3C;

namespace HAL {
namespace GIO {

sconst uint8_t numPorts = 6U;

static volatile GPIO_PORT_t* g_ports[] = {
		&GPIO_PORTA,
		&GPIO_PORTB,
		&GPIO_PORTC,
		&GPIO_PORTD,
		&GPIO_PORTE,
		&GPIO_PORTF
};

uint32_t get (Port port, uint32_t pin)
{
	return get_bit((*g_ports[uint32_t(port)]).IDR, pin);
}

void set (Port port, uint32_t pin)
{
	set_bit((*g_ports[uint32_t(port)]).BSRR_R, pin, 1);
	set_bit((*g_ports[uint32_t(port)]).BSRR_S, pin, 0);
}

void reset (Port port, uint32_t pin)
{
	set_bit((*g_ports[uint32_t(port)]).BSRR_R, pin, 0);
	set_bit((*g_ports[uint32_t(port)]).BSRR_S, pin, 1);
}

void toggle (Port port, uint32_t pin)
{
	volatile GPIO_PORT_t& gpo = *g_ports[uint32_t(port)];
	set_bit(gpo.ODR, pin, (~(gpo.ODR >> pin) & 1));
}

void setPort (Port port, uint16_t pins)
{
	(*g_ports[uint32_t(port)]).BSRR_S = pins;
	(*g_ports[uint32_t(port)]).BSRR_R = ~pins;
}

void configure(const InitStruct& str)
{
	GPIO_PORTA.MODER = str.MODER[0];

	for (uint32_t port = 0U; port < numPorts; ++port)
	{
		volatile GPIO_PORT_t& gpo = *g_ports[port];
		gpo.MODER = str.MODER[port];
		gpo.OTYPER = str.OTYPER[port];
		gpo.OSPEEDR = str.OSPEEDR[port];
		gpo.PUPDR = str.PUPDR[port];
		gpo.ODR = str.ODR[port];
		gpo.AFR[0] = str.AFRL[port];
		gpo.AFR[1] = str.AFRH[port];
	}
}

}
}

extern "C" {

void HAL_EIC_EXTI0_Handler()
{
	while(1);
}

}
