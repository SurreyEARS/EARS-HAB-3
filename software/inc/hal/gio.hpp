/*
 * gio.hpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#pragma once

#include <hal/generics.hpp>

namespace HAL
{
namespace GIO
{

struct InitStruct
{
	uint32_t MODER[6];
	uint32_t OTYPER[6];
	uint32_t OSPEEDR[6];
	uint32_t PUPDR[6];
	uint32_t ODR[6];
	uint32_t AFRL[6];
	uint32_t AFRH[6];
};

enum class Port
{
	PORTA, PORTB, PORTC, PORTD, PORTE, PORTF
};

typedef void (*EIC_INT_Handler)(Port port, uint32_t pin);

uint32_t get(Port port, uint32_t pin);
void set(Port port, uint32_t pin);
void reset(Port port, uint32_t pin);
void toggle(Port port, uint32_t pin);
void setPort(Port port, uint16_t pins);

void configure(const InitStruct& config);
// NO TEST FUNCTION - Not internally testable

}
}

