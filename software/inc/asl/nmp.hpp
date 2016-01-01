/*
 * nmp.hpp
 *
 *  Created on: Dec 30, 2015
 *      Author: James
 */

#pragma once
#include <hal/generics.hpp>

namespace ASL
{
namespace NMP
{

struct GpsData
{
	bool dirty;
	uint32_t timeUtc;

	double latitude;
	double longitude;

	uint32_t altitudeMsl;
	uint32_t geiodSeparation;

	GpsData() :
			dirty(true)
	{
	}
};

bool decode(const char* input);
GpsData& getReference();
GpsData get();

struct InitStruct
{
};

void configure(const InitStruct& config);
bool test();

}
}
