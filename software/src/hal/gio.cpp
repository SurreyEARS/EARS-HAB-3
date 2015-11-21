/*
 * gio.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#include <hal/gio.hpp>
#include <ext/bitops.hpp>
#include <mal/stm32f303vc.hpp>

using namespace MAL::F3C;

static volatile GPIO_PORT_t* g_ports[] = {
		&GPIO_PORTA,
		&GPIO_PORTB,
		&GPIO_PORTC,
		&GPIO_PORTD,
		&GPIO_PORTE,
		&GPIO_PORTF
};

namespace HAL {
namespace GIO {

//enum class Pin {
//	PA0,
//	PA1,
//	PA2,
//	PA3,
//	PA4,
//	PA5,
//	PA6,
//	PA7,
//	PA8,
//	PA9,
//	PA10,
//	PA11,
//	PA12,
//	PA13,
//	PA14,
//	PA15,
//	PB0,
//	PB1,
//	PB2,
//	PB3,
//	PB4,
//	PB5,
//	PB6,
//	PB7,
//	PB8,
//	PB9,
//	PB10,
//	PB11,
//	PB12,
//	PB13,
//	PB14,
//	PB15,
//	PC0,
//	PC1,
//	PC2,
//	PC3,
//	PC4,
//	PC5,
//	PC6,
//	PC7,
//	PC8,
//	PC9,
//	PC10,
//	PC11,
//	PC12,
//	PC13,
//	PC14,
//	PC15,
//	PD0,
//	PD1,
//	PD2,
//	PD3,
//	PD4,
//	PD5,
//	PD6,
//	PD7,
//	PD8,
//	PD9,
//	PD10,
//	PD11,
//	PD12,
//	PD13,
//	PD14,
//	PD15,
//	PE0,
//	PE1,
//	PE2,
//	PE3,
//	PE4,
//	PE5,
//	PE6,
//	PE7,
//	PE8,
//	PE9,
//	PE10,
//	PE11,
//	PE12,
//	PE13,
//	PE14,
//	PE15,
//	PF0,
//	PF1,
//	PF2,
//	PF3,
//	PF4,
//	PF5,
//	PF6,
//	PF7,
//	PF8,
//	PF9,
//	PF10,
//	PF11,
//	PF12,
//	PF13,
//	PF14,
//	PF15,
//};
//
//PinPort getPort (Pin pin)
//{
//	PinPort retVal;
//
//	if (int(pin) > int(Pin::PF0))
//	{
//		retVal = { Port::PORTF, int(pin) - int(Pin::PF0) };
//	}
//	else if (int(pin) > int(Pin::PE0))
//	{
//		retVal = { Port::PORTE, int(pin) - int(Pin::PE0) };
//	}
//	else if (int(pin) > int(Pin::PE0))
//	{
//		retVal = { Port::PORTE, int(pin) - int(Pin::PE0) };
//	}
//	else if (int(pin) > int(Pin::PE0))
//	{
//		retVal = { Port::PORTE, int(pin) - int(Pin::PE0) };
//	}
//	else if (int(pin) > int(Pin::PE0))
//	{
//		retVal = { Port::PORTE, int(pin) - int(Pin::PE0) };
//	}
//	else
//	{
//		retVal = { Port::PORTA, int(pin) - int(Pin::PA0) };
//	}
//
//	return retVal;
//}

void set (Port port, uint32_t pin)
{
	set_bit((*g_ports[uint32_t(port)]).BSRR_S, pin, 1);
}

void reset (Port port, uint32_t pin)
{
	set_bit((*g_ports[uint32_t(port)]).BSRR_R, pin, 1);
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

void configurePin (Port port, uint32_t pin, Mode mode, Pullups pullups, Type type, Speed speed, uint32_t value)
{
	volatile GPIO_PORT_t& gpo = *g_ports[uint32_t(port)];
	set_bit2(gpo.MODER, pin, uint32_t(mode));
	set_bit(gpo.OTYPER, pin, uint32_t(type));
	set_bit2(gpo.OSPEEDR, pin, uint32_t(speed));
	set_bit2(gpo.PUPDR, pin, uint32_t(pullups));
	set_bit(gpo.ODR, pin, value);
}

void configurePin (Port port, uint32_t pin, Defaults config, uint32_t value)
{
	switch (config)
	{
	case Defaults::OUTPUT:
		configurePin(port, pin, Mode::OUTPUT, Pullups::NONE, Type::PUSH_PULL, Speed::MEDIUM, value);
		break;
	case Defaults::INPUT:
		configurePin(port, pin, Mode::INPUT, Pullups::NONE, Type::PUSH_PULL, Speed::MEDIUM, value);
		break;
	case Defaults::OUT_PUP:
		configurePin(port, pin, Mode::OUTPUT, Pullups::PULL_UP, Type::PUSH_PULL, Speed::MEDIUM, value);
		break;
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
