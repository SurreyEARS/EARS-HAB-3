/*
 * rop.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#include <asl/rop.hpp>

#include <hal/gio.hpp>
#include <hal/mcu.hpp>
#include <hal/crc.hpp>
#include <hal/dac.hpp>

#include <cstring>
#include <cstdio>

sconst HAL::GIO::Port txEnPort = HAL::GIO::Port::PORTA;
sconst HAL::GIO::Port txDataPort = HAL::GIO::Port::PORTA;
sconst uint32_t txEnPin = 3;
sconst uint32_t txDataPin = 4;

sconst char* radioDataFormatString = "%s,%d,%d:%d:%d,%f,%f,%f";
sconst char* radioFinalFormatString = "         \n$$%s*0x%x\n";

sconst uint16_t outputLow = 0xC1F;
sconst uint16_t outputHigh = 0xD55;

sconst uint32_t maxRadioStringLength = 150U;
static char outputIntermediateBuffer[maxRadioStringLength];
static char outputBuffer[maxRadioStringLength];

static char currentOutput;
static uint32_t outputCounter;

namespace ASL
{
namespace ROP
{

void enable()
{
	memset(outputBuffer, 0, maxRadioStringLength);
	outputCounter = 0;
	currentOutput = '\0';

	HAL::GIO::set(txEnPort, txEnPin);
	HAL::GIO::set(HAL::GIO::Port::PORTE, 10);

	HAL::DAC::configure(HAL::DAC::Trigger::HARDWARE, false, true);
	HAL::DAC::SINGLE::enable();
	HAL::DAC::SINGLE::setData(outputHigh);

	//TODO Don't block
	HAL::MCU::delayTicks(100);
}

void startTransmit(RadioOutputData_t& data)
{
	int32_t error = sprintf(outputIntermediateBuffer, radioDataFormatString,
			data.callsign.c_str(), data.sentenceId, data.time.hour,
			data.time.minute, data.time.second, data.latitude, data.longitude,
			data.altitude);

	if (error > 0 && error <= (int32_t) maxRadioStringLength)
	{
		// Success!

		uint16_t checksum = HAL::CRC::crc(HAL::CRC::DefaultPolynomial::CRC16_CCITT, outputIntermediateBuffer, strlen(outputIntermediateBuffer));

		sprintf(outputBuffer, radioFinalFormatString, outputIntermediateBuffer,
				checksum);

		//TODO Use a scheduler, don't block
		while (transmitNext())
			;

		HAL::GIO::reset(txEnPort, txEnPin);
		HAL::GIO::reset(HAL::GIO::Port::PORTE, 10);
	}

	//TODO Error handling!
}

bool transmitNext()
{
	if ((outputCounter++) == maxRadioStringLength)
	{
		return false;
	}

	currentOutput = outputBuffer[outputCounter];

	if ('\0' == currentOutput)
	{
		return false;
	}

	HAL::DAC::SINGLE::setData(outputLow);
	HAL::MCU::delayTicks(10);

	for (uint32_t bit = 0; bit < 7; ++bit)
	{
		if (0U != (currentOutput & 1U))
		{
			HAL::DAC::SINGLE::setData(outputHigh);
		}
		else
		{
			HAL::DAC::SINGLE::setData(outputLow);
		}

		currentOutput = currentOutput >> 1;
		HAL::MCU::delayTicks(10);
	}

	HAL::DAC::SINGLE::setData(outputHigh);
	HAL::MCU::delayTicks(10);
	HAL::MCU::delayTicks(10);

	return true;
}

bool test()
{
	RadioOutputData_t data = {
			"UASRTTYTEST",
			117,
			{ 15, 34, 17 },
			45.756f,
			-10.04f,
			100.5f
	};

	enable();
	startTransmit (data);

	return true;
}

}
}

