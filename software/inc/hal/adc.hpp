/*
 * adc.hpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#pragma once

namespace HAL
{
namespace ADC
{

enum ADCNum
{
	ADC1, ADC2, ADC3, ADC4
};

void enableChannel(ADCNum module, uint32_t channel);

struct InitStruct
{

};

void configure(const InitStruct& config);
bool test();

}
}
