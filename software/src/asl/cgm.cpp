/*
 * cgm.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#include <asl/cgm.hpp>

namespace ASL
{
namespace CGM
{

void configure (const InitStruct& lis)
{
	/* Configure GPIO */
	HAL::GIO::configure(lis.initGIO);
	HAL::CRC::configure(lis.initCRC);
	HAL::DMA::configure(lis.initDMA);
}

}
}
