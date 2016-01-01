/*
 * device_usb.hpp
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

struct USB_BASE_t
{
	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :2;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP0R;

	v16t :16;

	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :1;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP1R;

	v16t :16;

	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :1;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP2R;

	v16t :16;

	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :1;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP3R;

	v16t :16;

	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :1;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP4R;

	v16t :16;

	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :1;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP5R;

	v16t :16;

	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :1;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP6R;

	v16t :16;

	REGISTER
			v16t EA :4;
			v16t STAT_TX :2;
			v16t DTOG_TX :1;
			v16t CTR_TX :1;
			v16t EP_KIND :1;
			v16t EPTYPE :2;
			v16t SETUP :1;
			v16t STAT_RX :1;
			v16t DTOG_RX :1;
			v16t CTR_RX :1;
		NAMED_16
	EP7R;

	v32t :16;

	v32t :32;
	v32t :32;
	v32t :32;
	v32t :32;
	v32t :32;
	v32t :32;
	v32t :32;
	v32t :32;

	REGISTER
			v16t FRES :1;
			v16t PWDN :1;
			v16t LP_MODE :1;
			v16t FSUSP :1;
			v16t RESUME :1;
			v16t L1RESUME :1;
			v16t :1;
			v16t L1REQM :1;
			v16t ESOFM :1;
			v16t SOFM :1;
			v16t RESETM :1;
			v16t SUSPM :1;
			v16t WKUPM :1;
			v16t ERRM :1;
			v16t PMAOVRM :1;
			v16t CTRM :1;
		NAMED_16
	CNTR;

	v32t :16;

	REGISTER
			v16t EP_ID :4;
			v16t DIR :1;
			v16t :2;
			v16t L1REQ :1;
			v16t ESOF :1;
			v16t SOF :1;
			v16t RESET :1;
			v16t SUSP :1;
			v16t WKUP :1;
			v16t ERR :1;
			v16t PMAOVR :1;
			v16t CTR :1;
		NAMED_16
	ISTR;

	v32t :16;

	REGISTER
			v16t FN :11;
			v16t LSOF :2;
			v16t LCK :1;
			v16t RXDM :1;
			v16t RXDP :1;
		NAMED_16
	FNR;

	v32t :16;

	REGISTER
			v16t ADD :7;
			v16t EF :1;
			v16t :8;
		NAMED_16
	DADDR;

	v32t :16;

	REGISTER
			v16t :3;
			v16t BTABLE :13;
		NAMED_16
	BTABLE;

	v32t :32; // LPMCSR - reserved on this chip
};

extern volatile USB_BASE_t& USB;

}
}
