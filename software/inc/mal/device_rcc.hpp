/*
 * device_rcc.hpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#pragma once

#include <mal/device_defines.hpp>

namespace MAL
{
namespace F3C
{

struct RCC_BASE_t
{
	REGISTER
			v32t HSION :1;
			v32t HSIRDY :1;
			v32t :1;
			v32t HSITRIM :5; /* Can be set to adjust clock in 40kHz increments */
			v32t HSICAL :8; /* Set automagically by startup */
			v32t HSEON :1;
			v32t HSERDY :1;
			v32t HSEBYP :1;
			v32t CSSON :1;
			v32t :4;
			v32t PLLON :1;
			v32t PLLRDY :1;
			v32t :6;
		NAMED
	CR;

	REGISTER
			v32t SW :2;
			v32t SWS :2;
			v32t HPRE :4;
			v32t PPRE1 :3; /* Can be set to adjust clock in 40kHz increments */
			v32t PPRE2 :3; /* Set automagically by startup */
			v32t :1;
			v32t :1; /* This bit is PLLSRC on 303xD/E chips only */
			v32t PLLSRC :1;
			v32t PLLXTPRE :1;
			v32t PLLMUL :4;
			v32t USBPRES :1;
			v32t I2SSRC :1;
			v32t MCO :3;
			v32t :1;
			v32t MCOPRE :3;
			v32t PLLNODIV :1;
		NAMED
	CFGR;

	REGISTER
			v32t LSI_RDF :1;
			v32t LSE_RDF :1;
			v32t HSI_RDF :1;
			v32t HSE_RDF :1;
			v32t PLL_RDF :1;
			v32t :2;
			v32t CSSF :1;
			v32t LSI_RDE :1;
			v32t LSE_RDE :1;
			v32t HSI_RDE :1;
			v32t HSE_RDE :1;
			v32t PLL_RDE :1;
			v32t :3;
			v32t LSI_RDC :1;
			v32t LSE_RDC :1;
			v32t HSI_RDC :1;
			v32t HSE_RDC :1;
			v32t PLL_RDC :1;
			v32t :2;
			v32t CSSC :1;
			v32t :8;
		NAMED
	CIR;

	REGISTER
			v32t SYSCFG_RST :1;
			v32t :10;
			v32t USART1_RST :1;
			v32t TIM8_RST :1;
			v32t SPI1_RST :1;
			v32t TIM1_RST :1;
			v32t TIM15_RST :1;
			v32t TIM16_RST :1;
			v32t TIM17_RST :1;
			v32t :13;
		NAMED
	APB2_RESET;

	REGISTER
			v32t TIM2_RST :1;
			v32t TIM3_RST :1;
			v32t TIM4_RST :1;
			v32t :1;
			v32t TIM6_RST :1;
			v32t TIM7_RST :1;
			v32t :5;
			v32t WWDG_RST :1;
			v32t :2;
			v32t SPI2_RST :1;
			v32t SPI3_RST :1;
			v32t :1;
			v32t USART2_RST :1;
			v32t USART3_RST :1;
			v32t USART4_RST :1;
			v32t USART5_RST :1;
			v32t I2C1_RST :1;
			v32t I2C2_RST :1;
			v32t USB_RST :1;
			v32t :1;
			v32t CAN_RST :1;
			v32t DAC2_RST :1;
			v32t :1;
			v32t PWR_RST :1;
			v32t DAC1_RST :1;
			v32t :1; /* I2C3 on D/E devices */
			v32t :1;
		NAMED
	APB1_RESET;

	REGISTER
			v32t DMA1_EN :1;
			v32t DMA2_EN :1;
			v32t SRAM_EN :1;
			v32t :1;
			v32t FLITF_EN :1;
			v32t :1;
			v32t CRC_EN :1;
			v32t :9;
			v32t :1; /* D/E IOPH */
			v32t IOPA_EN :1;
			v32t IOPB_EN :1;
			v32t IOPC_EN :1;
			v32t IOPD_EN :1;
			v32t IOPE_EN :1;
			v32t IOPF_EN :1;
			v32t :1; /* D/E IOPG */
			v32t TSC_EN :1;
			v32t :3;
			v32t ADC1_2_EN :1;
			v32t ADC3_4_EN :1;
			v32t :2;
		NAMED
	AHB_CLKEN;

	REGISTER
			v32t SYSCFG_EN :1;
			v32t :10;
			v32t TIM1_EN :1;
			v32t SPI1_EN :1;
			v32t TIM8_EN :1;
			v32t USART1_EN :1;
			v32t SPI4_EN :1;
			v32t TIM15_EN :1;
			v32t TIM16_EN :1;
			v32t TIM17_EN :1;
			v32t :1;
			v32t TIM20_EN :1;
			v32t :11;
		NAMED
	APB2_CLKEN;

	REGISTER
			v32t TIM2_EN :1;
			v32t TIM3_EN :1;
			v32t TIM4_EN :1;
			v32t :1;
			v32t TIM6_EN :1;
			v32t TIM7_EN :1;
			v32t :5;
			v32t WWDG_EN :1;
			v32t :2;
			v32t SPI2_EN :1;
			v32t SPI3_EN :1;
			v32t :1;
			v32t USART2_EN :1;
			v32t USART3_EN :1;
			v32t USART4_EN :1;
			v32t USART5_EN :1;
			v32t I2C1_EN :1;
			v32t I2C2_EN :1;
			v32t USB_EN :1;
			v32t :1;
			v32t CAN_EN :1;
			v32t DAC2_EN :1;
			v32t :1;
			v32t PWR_EN :1;
			v32t DAC1_EN :1;
			v32t :1; /* I2C3 on D/E devices */
			v32t :1;
		NAMED
	APB1_CLKEN;

	REGISTER
			v32t LSE_ON :1;
			v32t LSE_RDY :1;
			v32t LSE_BYP :1;
			v32t LSE_DRV :2;
			v32t :3;
			v32t RTC_SEL :2;
			v32t :5;
			v32t RTC_EN :1;
			v32t BD_RST :1;
			v32t :15;
		NAMED
	BDCR;

	REGISTER
			v32t LSI_ON :1;
			v32t LSI_RDY :1;
			v32t :21;
			v32t :1; /* D/E VREG_RSTF */
			v32t RMVF :1;
			v32t OBL_RSTF :1;
			v32t PIN_RSTF :1;
			v32t POR_RSTF :1;
			v32t SFT_RSTF :1;
			v32t IW_WDG_RSTF :1;
			v32t WWDG_RSTF :1;
			v32t LPWR_RSTF :1;
		NAMED
	CSR;

	REGISTER
			v32t :16;
			v32t :1; /* D/E IOPH */
			v32t IOPA_RST :1;
			v32t IOPB_RST :1;
			v32t IOPC_RST :1;
			v32t IOPD_RST :1;
			v32t IOPE_RST :1;
			v32t IOPF_RST :1;
			v32t :1; /* D/E IOPG */
			v32t TSC_RST :1;
			v32t :3;
			v32t ADC1_2_RST :1;
			v32t ADC3_4_RST :1;
			v32t :2;
		NAMED
	AHB_RESET;

	REGISTER
			v32t PREDIV :4;
			v32t ADC1_2PRES :5;
			v32t ADC3_4PRES :5;
			v32t :18;
		NAMED
	CFGR2;

	REGISTER
			v32t USART1_SW :2;
			v32t :2;
			v32t I2C1_SW :1;
			v32t I2C2_SW :1;
			v32t :1; /* D/E I2C3_SW */
			v32t TIM1_SW :1;
			v32t TIM8_SW :1;
			v32t :2; /* D/E TIM15/16 */
			v32t :1;
			v32t :1; /* D/E TIM17 */
			v32t :1;
			v32t :1; /* D/E TIM20 */
			v32t USART2_SW :2;
			v32t USART3_SW :2;
			v32t USART4_SW :2;
			v32t USART5_SW :2;
			v32t :2; /* D/E TIM2 and 34 */
			v32t :6;
		NAMED
	CFGR3;
};

extern volatile RCC_BASE_t& RCCMOD;

}
}
