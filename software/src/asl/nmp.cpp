/**
 * \brief NMEA Parsing Helper
 *
 * This module parses incoming NMEA strings and turns them into slightly more useful GPS data.
 *
 * \author James Telfer
 */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 1 INCLUDES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* This file's header: */
#include <asl/nmp.hpp>
/* APL/ASL/HAL files, sorted alphabetically */
#include <hal/mcu.hpp>
/* MAL, EXT and standard library files */
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace ASL
{
namespace NMP
{

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 2 CONSTANTS AND DEFINED DATA
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static constexpr const uint32_t maxStringLength = 150;
static constexpr const uint32_t maxDoubleLength = 15;

static GpsData data;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 3 INTERNAL CLASSES, STRUCTS, TYPEDEFS, DEFINES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 4 INTERNAL FUNCTION PROTOTYPES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static inline double fastPow10(int power);
static void copyReplaceDelimeters(char* destination, const char* source);
static double stringToDouble(const char* input);
static uint8_t nmeaXorChecksum(const char* target);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 5 MODULE FUNCTIONS
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

GpsData& getReference()
{
	return data;
}

GpsData get()
{
	return data;
}

bool decode(const char* input)
{
	bool validMessage = true;

	/* Copy to a buffer */
	uint32_t length = strlen(input);
	if (length > maxStringLength)
	{
		return false;
	}

	char* s2 = new char[length];
	copyReplaceDelimeters(s2, input);

	uint32_t timeUtc;
	char latitudeString[maxDoubleLength];
	char longitudeString[maxDoubleLength];
	char altitudeString[maxDoubleLength];
	char geoidString[maxDoubleLength];
	char checksumStr[maxDoubleLength];
	double latitude, longitude, altitude, geoid;
	char northSouth = 0, eastWest;
	uint32_t checksum;

	/* IMPROVE This scanf currently takes 400us, the better part of the 600uS spent decoding.
	 * As we do pretty much all of the parsing ourselves, this could probably be gutted. */
	int32_t numberArgs =
			sscanf(s2,
					"$GPGGA %lu%*3c %15s %c %15s %c %*d %*d %*15s %15s M %s M %*15s %*d %15s",
					&timeUtc, (char*) &latitudeString, &northSouth,
					(char*) &longitudeString, &eastWest,
					(char*) &altitudeString, (char*) &geoidString,
					(char*) &checksumStr);

	if (8 != numberArgs)
	{
		validMessage = false;
	}

	if (altitudeString[0] == '-')
	{
		altitudeString[0] = '0';
		validMessage = false;
	}

	if (validMessage)
	{
		/* When optimising do not look here;
		 * These calls execute in 5us each */
		latitude = stringToDouble(latitudeString);
		longitude = stringToDouble(longitudeString);

		altitude = stringToDouble(altitudeString);
		geoid = stringToDouble(geoidString);

		checksum = (uint32_t) strtol(checksumStr, nullptr, 16);

		if (northSouth == 'S')
		{
			latitude = -latitude;
		}

		if (eastWest == 'W')
		{
			longitude = -longitude;
		}

		uint8_t checksumCheck = nmeaXorChecksum(input);

		if (checksumCheck != checksum)
		{
			validMessage = false;
		}
	}

	if (validMessage)
	{
		data.dirty = true;
		data.altitudeMsl = altitude;
		data.geiodSeparation = geoid;
		data.latitude = latitude;
		data.longitude = longitude;
		data.timeUtc = timeUtc;
		data.dirty = false;
	}

	delete s2;
	return validMessage;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 6 OPERATIONAL FUNCTIONS
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void configure(InitStruct& cfg)
{

	data.dirty = false;
}

bool test()
{
	return decode(
			"$GPGGA,181908.00,3404.7041778,N,07044.3966270,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*5F");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 7 INTERNAL FUNCTIONS
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static inline double fastPow10(int power)
{
	static const constexpr double powersOfTen[] =
	{ 0.0000001, 0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 0, 1, 10, 100,
			1000, 10000, 100000, 1000000 };
	return powersOfTen[power + 7];
}

static void copyReplaceDelimeters(char* destination, const char* source)
{
	size_t length = strlen(source);

	for (size_t i = 0; source[i] != '\0' && i < length; ++i)
	{
		if (source[i] == ',' || source[i] == '*')
		{
			destination[i] = ' ';
		}
		else
		{
			destination[i] = source[i];
		}
	}
}

static double stringToDouble(const char* input)
{
	double val = 0.0f;
	size_t decimalPosition = 0;
	size_t length = strlen(input);

	if (length > maxDoubleLength)
	{
		return 9999.99f;
	}

	/* Use strchr to locate the decimal point; return rubbish if we don't have a decimal point */
	char* decimalPtr = strchr(input, '.');
	if (nullptr != decimalPtr)
	{
		decimalPosition = size_t(decimalPtr - input);
	}
	else
	{
		return 9999.99f;
	}

	for (size_t position = 0, digit = 0; position < length; ++position)
	{
		if (input[position] == '.')
		{
			continue;
		}

		digit = input[position] - '0';
		val += double(digit) * fastPow10(decimalPosition - position);
	}

	return val;
}

static uint8_t nmeaXorChecksum(const char* target)
{
//	size_t length = strlen(target);
//	uint8_t checksumA = 0, checksumB = 0;
//
//	for (size_t i = 1; (i < length) && (target[i] != '*'); ++i)
//	{
//		checksumA = checksumA + target[i];
//		checksumB = checksumB + checksumA;
//	}

	uint8_t crc = 0;
	size_t length = strlen(target);

	/* Start at 1 to skip leading 0 */
	for (size_t i = 1; (i < length) && (target[i] != '*'); ++i)
	{
		crc ^= target[i];
	}

	return crc;
}

}
}

