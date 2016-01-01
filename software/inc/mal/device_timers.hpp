/*
 * device_timers.hpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#pragma once

#include <mal/device_defines.hpp>

namespace MAL {
namespace F3C {

/* Advanced Control Timers
 * Created: 26/11/2015 James Telfer
 */
struct ADV_TIMER_t
{
	REGISTER
			v16t CEN :1;
			v16t UDIS :1;
			v16t URS :1;
			v16t OPM :1;
			v16t DIR :1;
			v16t CMS :2;
			v16t ARPE :1;
			v16t CKD :2;
			v16t :1;
			v16t UIFRE_MAP :1;
			v16t :4;
		NAMED_16
	CR1;

	REGISTER
			v32t CCPC :1;
			v32t :1;
			v32t CCUS :1;
			v32t CCDS :1;
			v32t MMS :3;
			v32t TI1S :1;
			v32t OIS1 :1;
			v32t OIS1N :1;
			v32t OIS2 :1;
			v32t OIS2N :1;
			v32t OIS3 :1;
			v32t OIS3N :1;
			v32t OIS4 :1;
			v32t :1;
			v32t OIS5 :1;
			v32t :1;
			v32t OIS6 :1;
			v32t :1;
			v32t MMS2 :4;
			v32t :8;
		NAMED
	CR2;

	REGISTER
			v32t SMS :3;
			v32t OCCS :1;
			v32t TS :3;
			v32t MSM :1;
			v32t ETF :4;
			v32t ETPS :2;
			v32t ECE :1;
			v32t ETP :1;
			v32t SMS3 :1;
			v32t :15;
		NAMED
	SMCR;

	REGISTER
			v16t UIE :3;
			v16t CC1IE :1;
			v16t CC2IE :1;
			v16t CC3IE :1;
			v16t CC4IE :1;
			v16t COMIE :1;
			v16t TIE :1;
			v16t BIE :1;
			v16t UDE :1;
			v16t CC1DE :1;
			v16t CC2DE :1;
			v16t CC3DE :1;
			v16t CC4DE :1;
			v16t COMDE :1;
			v16t TDE :1;
			v16t :1;
		NAMED_16
	DIER;

	REGISTER
			v32t UIF :3;
			v32t CC1IF :1;
			v32t CC2IF :1;
			v32t CC3IF :1;
			v32t CC4IF :1;
			v32t COMIF :1;
			v32t TIF :1;
			v32t BIF :1;
			v32t B2IF :1;
			v32t CC1OF :1;
			v32t CC2OF :1;
			v32t CC3OF :1;
			v32t CC4OF :1;
			v32t :3;
			v32t C5IF :1;
			v32t C6IF :1;
			v32t :14;
		NAMED
	SR;

	REGISTER
			v16t UG :3;
			v16t CC1G :1;
			v16t CC2G :1;
			v16t CC3G :1;
			v16t CC4G :1;
			v16t COMG :1;
			v16t TTG :1;
			v16t BG :1;
			v16t B2G :1;
			v16t :7;
		NAMED_16
	EGR;

	union
	{
		struct
		{
			v32t CC1S :2;
			v32t IC1PSC :2;
			v32t IC1F :4;
			v32t CC2S :2;
			v32t IC2PSC :2;
			v32t IC2F :4;
			v32t :16;
		} IB;
		struct
		{
			v32t CC1S :2;
			v32t OC1FE :1;
			v32t OC1PE :1;
			v32t OC1M :3;
			v32t OC1CE :1;
			v32t CC2S :2;
			v32t OC2FE :1;
			v32t OC2PE :1;
			v32t OC2M :3;
			v32t OC2CE :1;
			v32t OC1M3 :1;
			v32t :7;
			v32t OC2M3 :1;
			v32t :7;
		} OB;
		v32t R;
	} CCMR1;

	union
	{
		struct
		{
			v32t CC3S :2;
			v32t IC3PSC :2;
			v32t IC3F :4;
			v32t CC4S :2;
			v32t IC4PSC :2;
			v32t IC4F :4;
			v32t :16;
		} IB;
		struct
		{
			v32t CC3S :2;
			v32t OC3FE :1;
			v32t OC3PE :1;
			v32t OC3M :3;
			v32t OC3CE :1;
			v32t CC4S :2;
			v32t OC4FE :1;
			v32t OC4PE :1;
			v32t OC4M :3;
			v32t OC4CE :1;
			v32t OC3M3 :1;
			v32t :7;
			v32t OC4M3 :1;
			v32t :7;
		} OB;
		v32t R;
	} CCMR2;

	REGISTER
			v32t CC1E :1;
			v32t CC1P :1;
			v32t CC1NE :1;
			v32t CC1NP :1;
			v32t CC2E :1;
			v32t CC2P :1;
			v32t CC2NE :1;
			v32t CC2NP :1;
			v32t CC3E :1;
			v32t CC3P :1;
			v32t CC3NE :1;
			v32t CC3NP :1;
			v32t CC4E :1;
			v32t CC4P :1;
			v32t :1;
			v32t CC4NP :1;
			v32t CC5E :1;
			v32t CC5P :1;
			v32t :2;
			v32t CC6E :1;
			v32t CC6P :1;
			v32t :10;
		NAMED
	CCER;

	REGISTER
			v32t CNT :16;
			v32t :15;
			v32t UIFCPY :1;
		NAMED
	CNT;

	v16t PSC;
	v16t ARR;
	v16t RCR;
	v16t CCR1;
	v16t CCR2;
	v16t CCR3;
	v16t CCR4;

	REGISTER
			v32t DTG :8;
			v32t LOCK :2;
			v32t OSSI :1;
			v32t OSSR :1;
			v32t BKE :1;
			v32t BKP :1;
			v32t AOE :1;
			v32t MOE :1;
			v32t BKF :4;
			v32t BK2F :4;
			v32t BK2E :1;
			v32t BK2P :1;
			v32t :6;
		NAMED
	BDTR;

	REGISTER
			v16t DBA :5;
			v16t :3;
			v16t DBL :5;
			v16t :3;
		NAMED_16
	DCR;

	v16t DMAR;

	REGISTER
			v32t CCR5 :16;
			v32t :13;
			v32t GC5C1 :1;
			v32t GC5C2 :1;
			v32t GC5C3 :1;
		NAMED
	CCR5;

	v16t CCR6;

	REGISTER
			v32t TIM_ADC_RMP_OR :2;
			v32t TIM_ADC_RMP_OR2 :2;
			v32t :24;
		NAMED
	OR;
};

struct GP32_TIMER_t
{
	REGISTER
			v16t CEN :1;
			v16t UDIS :1;
			v16t URS :1;
			v16t OPM :1;
			v16t DIR :1;
			v16t CMS :2;
			v16t ARPE :1;
			v16t CKD :2;
			v16t :1;
			v16t UIFRE_MAP :1;
			v16t :4;
		NAMED_16
	CR1;

	REGISTER
			v16t :3;
			v16t CCDS :1;
			v16t MMS :3;
			v16t TI1S :1;
			v16t :8;
		NAMED_16
	CR2;

	REGISTER
			v32t SMS :3;
			v32t OCCS :1;
			v32t TS :3;
			v32t MSM :1;
			v32t ETF :4;
			v32t ETPS :2;
			v32t ECE :1;
			v32t ETP :1;
			v32t SMS3 :1;
			v32t :15;
		NAMED
	SMCR;

	REGISTER
			v16t UIE :3;
			v16t CC1IE :1;
			v16t CC2IE :1;
			v16t CC3IE :1;
			v16t CC4IE :1;
			v16t :1;
			v16t TIE :1;
			v16t :1;
			v16t UDE :1;
			v16t CC1DE :1;
			v16t CC2DE :1;
			v16t CC3DE :1;
			v16t CC4DE :1;
			v16t :1;
			v16t TDE :1;
			v16t :1;
		NAMED_16
	DIER;

	REGISTER
			v16t UIF :3;
			v16t CC1IF :1;
			v16t CC2IF :1;
			v16t CC3IF :1;
			v16t CC4IF :1;
			v16t :1;
			v16t TIF :1;
			v16t :1;
			v16t :1;
			v16t CC1OF :1;
			v16t CC2OF :1;
			v16t CC3OF :1;
			v16t CC4OF :1;
			v16t :3;
		NAMED_16
	SR;

	REGISTER
			v16t UG :1;
			v16t CC1G :1;
			v16t CC2G :1;
			v16t CC3G :1;
			v16t CC4G :1;
			v16t :1;
			v16t TG :1;
			v16t :9;
		NAMED_16
	EGR;

	union
	{
		struct
		{
			v32t CC1S :2;
			v32t IC1PSC :2;
			v32t IC1F :4;
			v32t CC2S :2;
			v32t IC2PSC :2;
			v32t IC2F :4;
			v32t :16;
		} IB;
		struct
		{
			v32t CC1S :2;
			v32t OC1FE :1;
			v32t OC1PE :1;
			v32t OC1M :3;
			v32t OC1CE :1;
			v32t CC2S :2;
			v32t OC2FE :1;
			v32t OC2PE :1;
			v32t OC2M :3;
			v32t OC2CE :1;
			v32t OC1M3 :1;
			v32t :7;
			v32t OC2M3 :1;
			v32t :7;
		} OB;
		v32t R;
	} CCMR1;

	union
	{
		struct
		{
			v32t CC3S :2;
			v32t IC3PSC :2;
			v32t IC3F :4;
			v32t CC4S :2;
			v32t IC4PSC :2;
			v32t IC4F :4;
			v32t :16;
		} IB;
		struct
		{
			v32t CC3S :2;
			v32t OC3FE :1;
			v32t OC3PE :1;
			v32t OC3M :3;
			v32t OC3CE :1;
			v32t CC4S :2;
			v32t OC4FE :1;
			v32t OC4PE :1;
			v32t OC4M :3;
			v32t OC4CE :1;
			v32t OC3M3 :1;
			v32t :7;
			v32t OC4M3 :1;
			v32t :7;
		} OB;
		v32t R;
	} CCMR2;

	REGISTER
			v16t CC1E :1;
			v16t CC1P :1;
			v16t :1;
			v16t CC1NP :1;
			v16t CC2E :1;
			v16t CC2P :1;
			v16t :1;
			v16t CC2NP :1;
			v16t CC3E :1;
			v16t CC3P :1;
			v16t :1;
			v16t CC3NP :1;
			v16t CC4E :1;
			v16t CC4P :1;
			v16t :1;
			v16t CC4NP :1;
		NAMED_16
	CCER;

	REGISTER
			v32t CNT :31;
			v32t UIFCPY :1;
		NAMED
	CNT;

	v16t PSC;
	v32t ARR;
	v32t CCR1;
	v32t CCR2;
	v32t CCR3;
	v32t CCR4;

	REGISTER
			v16t DBA :5;
			v16t :3;
			v16t DBL :5;
			v16t :3;
		NAMED_16
	DCR;

	v16t DMAR;
};

struct GP16_TIMER_t
{
	REGISTER
			v16t CEN :1;
			v16t UDIS :1;
			v16t URS :1;
			v16t OPM :1;
			v16t :3;
			v16t ARPE :1;
			v16t CKD :2;
			v16t :1;
			v16t UIFRE_MAP :1;
			v16t :4;
		NAMED_16
	CR1;

	REGISTER
			v16t CCPC :1;
			v16t :1;
			v16t CCUS :1;
			v16t CCDS :1;
			v16t MMS :3;
			v16t TI1S :1;
			v16t OIS1 :1;
			v16t OIS1N :1;
			v16t OIS2 :1;
			v16t :5;
		NAMED_16
	CR2;

	REGISTER
			v32t SMS :3;
			v32t OCCS :1;
			v32t TS :3;
			v32t MSM :1;
			v32t ETF :4;
			v32t ETPS :2;
			v32t ECE :1;
			v32t ETP :1;
			v32t SMS3 :1;
			v32t :15;
		NAMED
	SMCR;

	REGISTER
			v16t UIE :3;
			v16t CC1IE :1;
			v16t CC2IE :1;
			v16t CC3IE :1;
			v16t CC4IE :1;
			v16t :1;
			v16t TIE :1;
			v16t :1;
			v16t UDE :1;
			v16t CC1DE :1;
			v16t CC2DE :1;
			v16t CC3DE :1;
			v16t CC4DE :1;
			v16t :1;
			v16t TDE :1;
			v16t :1;
		NAMED_16
	DIER;

	REGISTER
			v16t UIF :3;
			v16t CC1IF :1;
			v16t CC2IF :1;
			v16t CC3IF :1;
			v16t CC4IF :1;
			v16t :1;
			v16t TIF :1;
			v16t :1;
			v16t :1;
			v16t CC1OF :1;
			v16t CC2OF :1;
			v16t CC3OF :1;
			v16t CC4OF :1;
			v16t :3;
		NAMED_16
	SR;

	REGISTER
			v16t UG :1;
			v16t CC1G :1;
			v16t CC2G :1;
			v16t CC3G :1;
			v16t CC4G :1;
			v16t :1;
			v16t TG :1;
			v16t :9;
		NAMED_16
	EGR;

	union
	{
		struct
		{
			v32t CC1S :2;
			v32t IC1PSC :2;
			v32t IC1F :4;
			v32t CC2S :2;
			v32t IC2PSC :2;
			v32t IC2F :4;
			v32t :16;
		} IB;
		struct
		{
			v32t CC1S :2;
			v32t OC1FE :1;
			v32t OC1PE :1;
			v32t OC1M :3;
			v32t OC1CE :1;
			v32t CC2S :2;
			v32t OC2FE :1;
			v32t OC2PE :1;
			v32t OC2M :3;
			v32t OC2CE :1;
			v32t OC1M3 :1;
			v32t :7;
			v32t OC2M3 :1;
			v32t :7;
		} OB;
		v32t R;
	} CCMR1;

	union
	{
		struct
		{
			v32t CC3S :2;
			v32t IC3PSC :2;
			v32t IC3F :4;
			v32t CC4S :2;
			v32t IC4PSC :2;
			v32t IC4F :4;
			v32t :16;
		} IB;
		struct
		{
			v32t CC3S :2;
			v32t OC3FE :1;
			v32t OC3PE :1;
			v32t OC3M :3;
			v32t OC3CE :1;
			v32t CC4S :2;
			v32t OC4FE :1;
			v32t OC4PE :1;
			v32t OC4M :3;
			v32t OC4CE :1;
			v32t OC3M3 :1;
			v32t :7;
			v32t OC4M3 :1;
			v32t :7;
		} OB;
		v32t R;
	} CCMR2;

	REGISTER
			v16t CC1E :1;
			v16t CC1P :1;
			v16t :1;
			v16t CC1NP :1;
			v16t CC2E :1;
			v16t CC2P :1;
			v16t :1;
			v16t CC2NP :1;
			v16t CC3E :1;
			v16t CC3P :1;
			v16t :1;
			v16t CC3NP :1;
			v16t CC4E :1;
			v16t CC4P :1;
			v16t :1;
			v16t CC4NP :1;
		NAMED_16
	CCER;

	REGISTER
			v32t CNT :31;
			v32t UIFCPY :1;
		NAMED
	CNT;

	v16t PSC;
	v32t ARR;
	v32t CCR1;
	v32t CCR2;
	v32t CCR3;
	v32t CCR4;

	REGISTER
			v16t DBA :5;
			v16t :3;
			v16t DBL :5;
			v16t :3;
		NAMED_16
	DCR;

	v16t DMAR;
};

struct GPB_TIMER_t
{
	REGISTER
			v16t CEN :1;
			v16t UDIS :1;
			v16t URS :1;
			v16t OPM :1;
			v16t :3;
			v16t ARPE :1;
			v16t :3;
			v16t UIFRE_MAP :1;
			v16t :4;
		NAMED_16
	CR1;

	REGISTER
			v16t :4;
			v16t MMS :3;
			v16t :9;
		NAMED_16
	CR2;

	v32t :32;

	REGISTER
			v16t UIE :1;
			v16t :7;
			v16t UDE :1;
			v16t :7;
		NAMED_16
	DIER;

	REGISTER
			v16t UIF :1;
			v16t :15;
		NAMED_16
	SR;

	REGISTER
			v16t UG :1;
			v16t :15;
		NAMED_16
	EGR;

	v32t :32;
	v32t :32;
	v32t :32;

	REGISTER
			v32t CNT :16;
			v32t :15;
			v32t UIFCPY :1;
		NAMED
	CNT;

	v16t PSC;
	v16t ARR;
};

extern volatile ADV_TIMER_t& TIM1;
extern volatile ADV_TIMER_t& TIM8;

extern volatile GP32_TIMER_t& TIM2;

extern volatile GP16_TIMER_t& TIM15;
extern volatile GP16_TIMER_t& TIM16;
extern volatile GP16_TIMER_t& TIM17;

extern volatile GPB_TIMER_t& TIM6;

}
}
