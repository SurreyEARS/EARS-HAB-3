/*
 * STM32F303VC.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#include <mal/stm32f303vc.hpp>

namespace MAL {
namespace CM4 {

volatile SystemTick_t& SYSTICK = *((SystemTick_t*)0xE000E010);

volatile SCB_t& SCB = *((SCB_t*)0xE000ED00);
volatile SCB_CPA_t& SCB_CPA = *((SCB_CPA_t*)0xE000ED88);
volatile SCB_FPU_t& SCB_FPU = *((SCB_FPU_t*)0xE000EF34);

}

namespace F3C {

volatile GPIO_PORT_t& GPIO_PORTA = *((GPIO_PORT_t*)0x48000000);
volatile GPIO_PORT_t& GPIO_PORTB = *((GPIO_PORT_t*)0x48000400);
volatile GPIO_PORT_t& GPIO_PORTC = *((GPIO_PORT_t*)0x48000800);
volatile GPIO_PORT_t& GPIO_PORTD = *((GPIO_PORT_t*)0x48000C00);
volatile GPIO_PORT_t& GPIO_PORTE = *((GPIO_PORT_t*)0x48001000);
volatile GPIO_PORT_t& GPIO_PORTF = *((GPIO_PORT_t*)0x48001400);

volatile DMA_CHANNEL_t* DMA_CHANNELS[12] = {
		&DMA1_CH1, &DMA1_CH2, &DMA1_CH3, &DMA1_CH4, &DMA1_CH5, &DMA1_CH6, &DMA1_CH7,
		&DMA2_CH1, &DMA2_CH2, &DMA2_CH3, &DMA2_CH4, &DMA2_CH5,
};

#define DMA1_BASE_ADDR 0x40020000
volatile DMA_BASE_t& DMA1 = *((DMA_BASE_t*)DMA1_BASE_ADDR);
volatile DMA_CHANNEL_t& DMA1_CH1 = *((DMA_CHANNEL_t*)(DMA1_BASE_ADDR + 0x08));
volatile DMA_CHANNEL_t& DMA1_CH2 = *((DMA_CHANNEL_t*)(DMA1_BASE_ADDR + 0x1C));
volatile DMA_CHANNEL_t& DMA1_CH3 = *((DMA_CHANNEL_t*)(DMA1_BASE_ADDR + 0x30));
volatile DMA_CHANNEL_t& DMA1_CH4 = *((DMA_CHANNEL_t*)(DMA1_BASE_ADDR + 0x44));
volatile DMA_CHANNEL_t& DMA1_CH5 = *((DMA_CHANNEL_t*)(DMA1_BASE_ADDR + 0x58));
volatile DMA_CHANNEL_t& DMA1_CH6 = *((DMA_CHANNEL_t*)(DMA1_BASE_ADDR + 0x6C));
volatile DMA_CHANNEL_t& DMA1_CH7 = *((DMA_CHANNEL_t*)(DMA1_BASE_ADDR + 0x80));

#define DMA2_BASE_ADDR 0x40020400
volatile DMA_BASE_t& DMA2 = *((DMA_BASE_t*)DMA2_BASE_ADDR);
volatile DMA_CHANNEL_t& DMA2_CH1 = *((DMA_CHANNEL_t*)(DMA2_BASE_ADDR + 0x08));
volatile DMA_CHANNEL_t& DMA2_CH2 = *((DMA_CHANNEL_t*)(DMA2_BASE_ADDR + 0x1C));
volatile DMA_CHANNEL_t& DMA2_CH3 = *((DMA_CHANNEL_t*)(DMA2_BASE_ADDR + 0x30));
volatile DMA_CHANNEL_t& DMA2_CH4 = *((DMA_CHANNEL_t*)(DMA2_BASE_ADDR + 0x44));
volatile DMA_CHANNEL_t& DMA2_CH5 = *((DMA_CHANNEL_t*)(DMA2_BASE_ADDR + 0x58));

volatile RCC_BASE_t& RCCMOD = *((RCC_BASE_t*)0x40021000);

volatile FLASH_t& FLASH = *((FLASH_t*)0x40022000);
}
}
