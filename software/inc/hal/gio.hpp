/*
 * gio.hpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#pragma once

#include <hal/generics.hpp>

namespace HAL {
namespace GIO {

enum class Port {
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF
};

enum class Mode {
	INPUT,
	OUTPUT,
	ALTERNATE,
	INOUT
};

enum class Pullups {
	NONE,
	PULL_UP,
	PULL_DOWN,
};

enum class Type {
	PUSH_PULL,
	OPEN_DRAIN
};

enum class Speed {
	SLOW,
	MEDIUM,
	FAST
};

enum class Defaults {
	OUTPUT,
	INPUT,
	OUT_PUP
};

typedef void (*EIC_INT_Handler)(Port port, uint32_t pin);

void set (Port port, uint32_t pin);
void reset (Port port, uint32_t pin);
void toggle (Port port, uint32_t pin);
void setPort (Port port, uint16_t pins);

void configurePin (Port port, uint32_t pin, Mode mode, Pullups pullups, Type type, Speed speed, uint32_t value);
void configurePin (Port port, uint32_t pin, Defaults config, uint32_t value);

}
}

