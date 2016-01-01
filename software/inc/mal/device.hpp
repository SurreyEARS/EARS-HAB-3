/*
 * STM32F303VC.h
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#pragma once

#include <mal/device_defines.hpp>

#include <mal/device_usb.hpp>
#include <mal/device_timers.hpp>
#include <mal/device_dma.hpp>
#include <mal/device_rcc.hpp>
#include <mal/device_usart.hpp>

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

/* Processor-side Interrupt Control
 * Created: 21/11/2015 James Telfer
 */

/* Cyclic Redundancy Check Engine
 * Created: 22/12/2015 James Telfer
 */
struct CRC_BASE_t
{
	v32t DR;

	REGISTER
			v32t IDR :8;
			v32t :24;
		NAMED
	IDR;

	REGISTER
			v32t RESET :1;
			v32t :2;
			v32t POLYSIZE :2;
			v32t REV_IN :2;
			v32t REV_OUT :1;
			v32t :24;
		NAMED
	CR;

	v32t :32;
	v32t INIT;
	v32t POL;
};

extern volatile CRC_BASE_t& CRC;

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
	//TODO additional space required between registers here
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
