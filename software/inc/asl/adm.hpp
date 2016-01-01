/*
 * adm.hpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#pragma once

#include <Hal/adc.hpp>

//TODO remove
typedef int ADCNum;

namespace ASL
{
namespace ADM
{

enum Operation
{
	Raw, Filter, Debounce
};

class Channel
{
public:
	const ADCNum module;
	const uint32_t channel;

	Channel(ADCNum module, uint32_t channel);

	void configure(Operation op, uint32_t multiplier = 1, int32_t constant = 0);
	Operation getOperation();
	uint32_t getMultiplier();
	int32_t getConstant();

	void setEnable(bool enable);
	bool getEnable();

	uint32_t getValue();

private:
	uint32_t value;
	bool enabled;

	uint32_t rawValue;
	Operation op;
	uint32_t multiplier;
	int32_t constant;

	uint32_t previousRawValues[10];

	friend void setSample(Channel& ch, uint32_t newRaw);
};

struct InitStruct
{

};

void configure(const InitStruct& config);
Channel& getChannelRef(uint32_t module, uint32_t channel);
void sampleAll();

}
}
