/*
 * rop.hpp
 *
 * Radio Output Processing
 *
 * This module communicates with an NTX2B via RTTY, in standard UKHAS mode.
 * It uses the DAC to achieve the required shifts.
 *
 *  Created on: Dec 22, 2015
 *      Author: James
 */

#pragma once

#include <string>

namespace ASL
{
namespace ROP
{

struct Time_t
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
};

struct RadioOutputData_t
{
	std::string callsign;
	uint16_t sentenceId;
	Time_t time;
	float latitude;
	float longitude;
	float altitude;
};

void enable();
void startTransmit(RadioOutputData_t& data);
bool transmitNext();

struct InitStruct
{

};

void configure(const InitStruct& config);
bool test();

}
}
