/*
 * device_defines.hpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#pragma once

#include <stdint.h>

typedef volatile uint32_t v32t;
typedef volatile uint16_t v16t;
typedef volatile uint8_t v8t;

#define REGISTER union { struct {
#define NAMED } B; v32t R; }
#define NAMED_16 } B; v16t R; }
#define NAMED_8 } B; v8t R; }
