/*
 * usi.hpp
 *
 *  Created on: Jan 1, 2016
 *      Author: James
 */

#pragma once
#include <mal/device_usart.hpp>

namespace HAL
{
namespace USI
{

struct InitStruct
{

};

void configure(const InitStruct& init);

class UartModule
{
public:

	static void configureModules(const InitStruct& init);

private:
	UartModule();

};

}
}
