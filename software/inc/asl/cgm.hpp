/*
 * cgm.hpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#pragma once
#include <hal/generics.hpp>

#include <asl/nvm.hpp>
#include <hal/crc.hpp>
#include <hal/dma.hpp>
#include <hal/gio.hpp>

namespace ASL
{
namespace CGM
{

struct InitStruct
{
	HAL::CRC::InitStruct initCRC;
	HAL::DMA::InitStruct initDMA;
	HAL::GIO::InitStruct initGIO;
};

void configure(const InitStruct& config);
// NO TEST FUNCTION

}
}
