/*
 * STM32F303VC.h
 *
 *  Created on: Nov 20, 2015
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

namespace MAL
{
namespace CM4
{

/* System Tick Interrupt Control
 * Created: 21/11/2015 James Telfer
 */
struct SystemTick_t
{
	REGISTER
			v32t enable :1;
			v32t interrupt :1;
			v32t clockSource :1;
			v32t :13;
			v32t countFlag :1;
			v32t :15;
		NAMED
	CTRL;

	REGISTER
			v32t reload :24;
			v32t interupt :8;
		NAMED
	RELOAD;

	v32t VAL;

	REGISTER
			v32t TENMS :24;
			v32t :6;
			v32t SKEW :1;
			v32t NOREF :1;
		NAMED
	CALIB;
};
extern volatile SystemTick_t& SYSTICK;

/* Core System Control Block
 * Created: 22/11/2015 James Telfer
 */
struct SCB_t
{
	REGISTER
			v32t REVISION :4;
			v32t PARTNO :12;
			v32t :4;
			v32t VARIANT :4;
			v32t IMPLEMENTER :8;
		NAMED
	CPUID;

	REGISTER
			v32t VECTACTIVE :9;
			v32t :2;
			v32t RETTOBASE :1;
			v32t VECTPENDING :9;
			v32t :1;
			v32t ISRPENDING :1;
			v32t ISRPREEMPT :1;
			v32t :1;
			v32t PENDSTCLR :1;
			v32t PENDSTSET :1;
			v32t PENDSVCLR :1;
			v32t PENDSVSET :1;
			v32t :2;
			v32t NMIPENDSET :1;
		NAMED
	ICSR;

	/* When writing to VTOR, write the full address to the R value,
	 * or bit shift out the lower 7 bits and assign to TBLOFF. */
	REGISTER
			v32t :7;
			v32t TBLOFF :25; /* This contains the upper 25 bits of address. */
		NAMED
	VTOR;

	REGISTER
			v32t VECTRESET :1;
			v32t VECTCLRACTIVE :1;
			v32t SYSRESETREQ :1;
			v32t :5;
			v32t PRIGROUP :3;
			v32t :4;
			v32t ENDIANNESS :1;
			v32t VECTKEY_STAT :16;
		NAMED
	AIRCR;

	REGISTER
			v32t :1;
			v32t SLEEPONEXIT :1;
			v32t SLEEPDEEP :1;
			v32t :1;
			v32t SEVONPEND :1;
			v32t :27;
		NAMED
	SCR;

	REGISTER
			v32t NONBASETHDENA :1;
			v32t USERSETMPEND :1;
			v32t :1;
			v32t UNALIGN_TRP :1;
			v32t DIV_0_TRP :1;
			v32t :1;
			v32t BFHFNMIGN :1;
			v32t STKALIGN :1;
			v32t :22;
		NAMED
	CCR;

	REGISTER
			v32t PRI_4 :8;
			v32t PRI_5 :8;
			v32t PRI_6 :8;
			v32t PRI_7 :8;
		NAMED
	SHPR1;

	REGISTER
			v32t PRI_8 :8;
			v32t PRI_9 :8;
			v32t PRI_10 :8;
			v32t PRI_11 :8;
		NAMED
	SHPR2;

	REGISTER
			v32t PRI_12 :8;
			v32t PRI_13 :8;
			v32t PRI_14 :8;
			v32t PRI_15 :8;
		NAMED
	SHPR3;

	REGISTER
			v32t MEMFAULTACT :1;
			v32t BUSFAULTACT :1;
			v32t :1;
			v32t USGFAULTACT :1;
			v32t :3;
			v32t SVCALLACT :1;
			v32t MONITORACT :1;
			v32t :1;
			v32t PENDSVACT :1;
			v32t SYSTICKACT :1;
			v32t USGFAULTPENDED :1;
			v32t MEMFAULTPENDED :1;
			v32t BUSFAULTPENDED :1;
			v32t SVCALLPENDED :1;
			v32t MEMFAULTENA :1;
			v32t BUSFAULTENA :1;
			v32t USGFAULTENA :1;
			v32t :13;
		NAMED
	SHCSR;

	REGISTER
	/* MemManage Fault Register */
			v32t IACCVIOL :1;
			v32t DACCVIOL :1;
			v32t :1;
			v32t MUNSTKER :1;
			v32t MSTKERR :1;
			v32t MLSPERR :1;
			v32t :1;
			v32t MMARVALID :1;
			/* Bus Fault Register */
			v32t IBUSERR :1;
			v32t PRECISERR :1;
			v32t IMPRECISERR :1;
			v32t UNSTKERR :1;
			v32t STKERR :1;
			v32t LSPERR :1;
			v32t :1;
			v32t BFARVALID :1;
			/* Usage Fault Register */
			v32t UNDEFINSTR :1;
			v32t INVSTATE :1;
			v32t INVPC :1;
			v32t NOCP :1;
			v32t :4;
			v32t UNALIGNED :1;
			v32t DIVBYZERO :1;
			v32t :6;
		NAMED
	CFSR;

	REGISTER
			v32t :1;
			v32t VECTTBL :4;
			v32t :28;
			v32t FORCED :1;
			v32t DEBUGEVT :1;
		NAMED
	HFSR;

	v32t MMFAR;
	v32t BFAR;

	v32t AFSR;
};

struct SCB_CPA_t
{
	REGISTER
			v32t CP0 :2;
			v32t CP1 :2;
			v32t CP2 :2;
			v32t CP3 :2;
			v32t CP4 :2;
			v32t CP5 :2;
			v32t CP6 :2;
			v32t CP7 :2;
			v32t :4;
			v32t CP10 :2;
			v32t CP11 :2;
			v32t :8;
		NAMED
	CPACR;
};

struct SCB_FPU_t
{
	REGISTER
			v32t LSPACT :1;
			v32t USER :1;
			v32t :1;
			v32t THREAD :1;
			v32t HFRDY :1;
			v32t MMRDY :1;
			v32t BFRDY :1;
			v32t :1;
			v32t MONDRY :1;
			v32t :20;
			v32t LSPEN :1;
			v32t ASPEN :1;
		NAMED
	FPCCR;

	REGISTER
			v32t :3;
			v32t ADDRESS :29;
		NAMED
	FPCAR;

	REGISTER
			v32t :22;
			v32t RMODE :2;
			v32t FZ :1;
			v32t DN :1;
			v32t AHP :1;
			v32t :5;
		NAMED
	FPDSCR;

	REGISTER
			v32t A_SIMD_REG :4;
			v32t SINGLE_PRES :4;
			v32t DOUBLE_PRES :4;
			v32t FP_EXCPT_TRAP :4;
			v32t DIVIDE :4;
			v32t SQRT :4;
			v32t SHORT_VEC :4;
			v32t FP_ROUND_MODES :4;
		NAMED
	MVFR1;

	REGISTER
			v32t FTZ_MODE :4;
			v32t D_NAN_MODE :4;
			v32t :16;
			v32t FP_HPFP :4;
			v32t PP_FUSED_MAC :4;
		NAMED
	MVFR2;
};

extern volatile SCB_t& SCB;
extern volatile SCB_CPA_t& SCB_CPA;
extern volatile SCB_FPU_t& SCB_FPU;

}

namespace F3C
{

/* General Purpose Input/Output.
 * Use the bitops.hpp/set_bit2 method to operate on these registers.
 * Created: 21/11/2015 James Telfer
 */
struct GPIO_PORT_t
{
	v32t MODER;
	v32t OTYPER;
	v32t OSPEEDR;
	v32t PUPDR;
	v32t IDR;
	v32t ODR;
	v16t BSRR_R;
	v16t BSRR_S;
	v32t LCKR;
	v32t AFR[2];
	v32t BRR;
};
extern volatile GPIO_PORT_t& GPIO_PORTA;
extern volatile GPIO_PORT_t& GPIO_PORTB;
extern volatile GPIO_PORT_t& GPIO_PORTC;
extern volatile GPIO_PORT_t& GPIO_PORTD;
extern volatile GPIO_PORT_t& GPIO_PORTE;
extern volatile GPIO_PORT_t& GPIO_PORTF;
extern volatile GPIO_PORT_t& GPIO_PORTH;

/* Direct Memory Access
 * Created: 21/11/2015 James Telfer
 */
struct DMA_BASE_t
{
	REGISTER
			v32t GIF1 :1;
			v32t TCIF1 :1;
			v32t HTIF1 :1;
			v32t TEIF1 :1;
			v32t GIF2 :1;
			v32t TCIF2 :1;
			v32t HTIF2 :1;
			v32t TEIF2 :1;
			v32t GIF3 :1;
			v32t TCIF3 :1;
			v32t HTIF3 :1;
			v32t TEIF3 :1;
			v32t GIF4 :1;
			v32t TCIF4 :1;
			v32t HTIF4 :1;
			v32t TEIF4 :1;
			v32t GIF5 :1;
			v32t TCIF5 :1;
			v32t HTIF5 :1;
			v32t TEIF5 :1;
			v32t GIF6 :1;
			v32t TCIF6 :1;
			v32t HTIF6 :1;
			v32t TEIF6 :1;
			v32t GIF7 :1;
			v32t TCIF7 :1;
			v32t HTIF7 :1;
			v32t TEIF7 :1;
			v32t :4;
		NAMED
	ISR;

	REGISTER
			v32t CGIF1 :1;
			v32t CTCIF1 :1;
			v32t CHTIF1 :1;
			v32t CTEIF1 :1;
			v32t CGIF2 :1;
			v32t CTCIF2 :1;
			v32t CHTIF2 :1;
			v32t CTEIF2 :1;
			v32t CGIF3 :1;
			v32t CTCIF3 :1;
			v32t CHTIF3 :1;
			v32t CTEIF3 :1;
			v32t CGIF4 :1;
			v32t CTCIF4 :1;
			v32t CHTIF4 :1;
			v32t CTEIF4 :1;
			v32t CGIF5 :1;
			v32t CTCIF5 :1;
			v32t CHTIF5 :1;
			v32t CTEIF5 :1;
			v32t CGIF6 :1;
			v32t CTCIF6 :1;
			v32t CHTIF6 :1;
			v32t CTEIF6 :1;
			v32t CGIF7 :1;
			v32t CTCIF7 :1;
			v32t CHTIF7 :1;
			v32t CTEIF7 :1;
			v32t :4;
		NAMED
	IFCR;
};

struct DMA_CHANNEL_t
{
	REGISTER
			v32t EN :1;
			v32t TCIE :1;
			v32t HTIE :1;
			v32t TEIE :1;
			v32t DIR :1;
			v32t CIRC :1;
			v32t PINC :1;
			v32t MINC :1;
			v32t PSIZE :2;
			v32t MSIZE :2;
			v32t PL :2;
			v32t MEM2MEM :1;
			v32t :17;
		NAMED
	CCR;

	REGISTER
			v32t NDT :15;
			v32t :15;
		NAMED
	CNDTR;

	v32t CPAR;
	v32t CMAR;
};

extern volatile DMA_CHANNEL_t* DMA_CHANNELS[12];

extern volatile DMA_BASE_t& DMA1;
extern volatile DMA_CHANNEL_t& DMA1_CH1;
extern volatile DMA_CHANNEL_t& DMA1_CH2;
extern volatile DMA_CHANNEL_t& DMA1_CH3;
extern volatile DMA_CHANNEL_t& DMA1_CH4;
extern volatile DMA_CHANNEL_t& DMA1_CH5;
extern volatile DMA_CHANNEL_t& DMA1_CH6;
extern volatile DMA_CHANNEL_t& DMA1_CH7;

extern volatile DMA_BASE_t& DMA2;
extern volatile DMA_CHANNEL_t& DMA2_CH1;
extern volatile DMA_CHANNEL_t& DMA2_CH2;
extern volatile DMA_CHANNEL_t& DMA2_CH3;
extern volatile DMA_CHANNEL_t& DMA2_CH4;
extern volatile DMA_CHANNEL_t& DMA2_CH5;

/* Processor-side Interrupt Control
 * Created: 21/11/2015 James Telfer
 */

/* Reset and Clock Configuration
 * Created: 21/11/2015 James Telfer
 */
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

/* Flash Memory Configuration
 * Created: 22/11/2015 James Telfer
 */

struct FLASH_t
{
	REGISTER
			v32t LATENCY :3;
			v32t HLF_CYA :1;
			v32t PRFTB_E :1;
			v32t PRFTB_S :1;
			v32t :26;
		NAMED
	ACR;

	v32t KEYR;
	v32t OPTKEYR;

	REGISTER
			v32t BSY :1;
			v32t :1;
			v32t PG_ERR :1;
			v32t :1;
			v32t WRPRT_ERR :1;
			v32t EOP :1;
			v32t :26;
		NAMED
	SR;

	REGISTER
			v32t PG :1;
			v32t PER :1;
			v32t MER :1;
			v32t :1;
			v32t OPT_PG :1;
			v32t OPT_ER :1;
			v32t STRT :1;
			v32t LOCK :1;
			v32t :1;
			v32t OPT_WRE :1;
			v32t ERR_IE :1;
			v32t :1;
			v32t EOP_IE :1;
			v32t OBL_LAUNCH :1;
			v32t :18;
		NAMED
	CR;

	v32t AR;

	REGISTER
			v32t OPTERR :1;
			v32t RDRPT :2;
			v32t :5;
			v32t WDG_SW :1;
			v32t nRST_STOP :1;
			v32t :1;
			v32t nBOOT1 :1;
			v32t :1;
			v32t VDDA_MONITOR :1;
			v32t SRAM_PE :1;
			v32t :1;
			v32t DATA0 :8;
			v32t DATA1 :8;
		NAMED
	OBR;

	v32t WRPR;
};

extern volatile FLASH_t& FLASH;

/* Digital to Analog Converter
 * Created: 25/11/2015 James Telfer
 */

struct DAC_t
{
	REGISTER
			v32t EN1 :1;
			v32t BOFF_OUTEN1 :1;
			v32t TEN1 :1;
			v32t TSEL1 :3;
			v32t WAVE1 :2;
			v32t MAMP1 :4;
			v32t DMA_EN1 :1;
			v32t DMAU_DRIE1 :1;
			v32t :2;
			v32t EN2 :1;
			v32t BOFF_OUTEN2 :1;
			v32t TEN2 :1;
			v32t TSEL2 :3;
			v32t WAVE2 :2;
			v32t MAMP2 :4;
			v32t DMA_EN2 :1;
			v32t DMAU_DRIE2 :1;
			v32t :2;
		NAMED
	CR;

	REGISTER
			v32t SWTRIG1 :1;
			v32t SWTRIG2 :1;
			v32t :30;
		NAMED
	SWTRIGR;

	REGISTER
			v32t DACC1DHR :12;
			v32t :20;
		NAMED
	DHR12R1;

	REGISTER
			v32t :4;
			v32t DACC1DHR :12;
			v32t :16;
		NAMED
	DHR12L1;

	REGISTER
			v32t DACC1DHR :8;
			v32t :24;
		NAMED
	DHR8R1;

	REGISTER
			v32t DACC2DHR :12;
			v32t :20;
		NAMED
	DHR12R2;

	REGISTER
			v32t :4;
			v32t DACC2DHR :12;
			v32t :16;
		NAMED
	DHR12L2;

	REGISTER
			v32t DACC2DHR :8;
			v32t :24;
		NAMED
	DHR8R2;

	REGISTER
			v32t DACC1DHR :12;
			v32t :4;
			v32t DACC2DHR :12;
			v32t :4;
		NAMED
	DHR12RD;

	REGISTER
			v32t :4;
			v32t DACC1DHR :12;
			v32t :4;
			v32t DACC2DHR :12;
		NAMED
	DHR12LD;

	REGISTER
			v32t DACC1DHR :8;
			v32t DACC2DHR :8;
			v32t :16;
		NAMED
	DHR8RD;

	REGISTER
			v32t DACC1DOR :12;
			v32t :20;
		NAMED
	DOR1;

	REGISTER
			v32t DACC2DOR :12;
			v32t :20;
		NAMED
	DOR2;

	REGISTER
			v32t :13;
			v32t DMAUDR1 :1;
			v32t :15;
			v32t DMAUDR2 :1;
			v32t :2;
		NAMED
	SR;
};

extern volatile DAC_t& DAC;

}
}
