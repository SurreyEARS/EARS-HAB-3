/*
 * device_usart.hpp
 *
 *  Created on: Dec 31, 2015
 *      Author: James
 */

#pragma once

#include <mal/device_defines.hpp>

namespace MAL
{
namespace F3C
{

struct USART_BASE_t
{
	REGISTER
			v32t UE :1;
			v32t UESM :1;
			v32t RE :1;
			v32t TE :1;
			v32t IDLEIE :1;
			v32t EXNEIE :1;
			v32t TCIE :1;
			v32t TXIE :1;
			v32t PEIE :1;
			v32t PS :1;
			v32t PCE :1;
			v32t WAKE :1;
			v32t M0 :1;
			v32t MME :1;
			v32t CMIE :1;
			v32t OVER8 :1;
			v32t DEDT :5;
			v32t DEAT :5;
			v32t RTOIE :1;
			v32t EOBIE :1;
			v32t M1 :1;
			v32t :3;
		NAMED
	CR1;

	REGISTER
			v32t :4;
			v32t ADDM7 :1;
			v32t LBDL :1;
			v32t LBDIE :1;
			v32t :1;
			v32t LBCL :1;
			v32t CPHA :1;
			v32t CPOL :1;
			v32t CLKEN :1;
			v32t STOP :2;
			v32t LINEN :1;
			v32t SWAP :1;
			v32t RXINV :1;
			v32t TXINV :1;
			v32t DATAINV :1;
			v32t MSBFIRST :1;
			v32t ABREN :1;
			v32t ABRMOD :2;
			v32t RTOEN :1;
			v32t ADD :8;
		NAMED
	CR2;

	REGISTER
			v32t EIE :1;
			v32t IREN :1;
			v32t IRLP :1;
			v32t HDSEL :1;
			v32t NACK :1;
			v32t SCEN :1;
			v32t DMAR :1;
			v32t DMAT :1;
			v32t RTSE :1;
			v32t CTSE :1;
			v32t CTSIE :1;
			v32t ONEBIT :1;
			v32t OVRDIS :1;
			v32t DDRE :1;
			v32t DEM :1;
			v32t DEP :1;
			v32t :1;
			v32t SCARCNT :3;
			v32t WUS :2;
			v32t WUFIE :1;
			v32t :9;
		NAMED
	CR3;

	v16t BRR;
	v16t :16;

	REGISTER
			v32t PSC :8;
			v32t GT :8;
			v32t :16;
		NAMED
	GTPR;

	REGISTER
			v32t RTO :24;
			v32t BLEN :8;
		NAMED
	RTOR;

	REGISTER
			v32t ABRRQ :1;
			v32t SBKRQ :1;
			v32t MMRQ :1;
			v32t RXFRQ :1;
			v32t TXFRQ :1;
			v32t :27;
		NAMED
	RQR;

	REGISTER
			v32t PE :1;
			v32t FE :1;
			v32t NF :1;
			v32t ORE :1;
			v32t IDLE :1;
			v32t RXNE :1;
			v32t TC :1;
			v32t TXE :1;
			v32t LBDF :1;
			v32t CTSIF :1;
			v32t CTS :1;
			v32t RTOF :1;
			v32t EOBF :1;
			v32t :1;
			v32t ABRE :1;
			v32t ABRF :1;
			v32t BUSY :1;
			v32t CMF :1;
			v32t SBKF :1;
			v32t RWU :1;
			v32t WUF :1;
			v32t TEACK :1;
			v32t REACK :1;
			v32t :9;
		NAMED
	ISR;

	REGISTER
			v32t PECF :1;
			v32t FECF :1;
			v32t NCF :1;
			v32t ORECF :1;
			v32t IDLECF :1;
			v32t :1;
			v32t TCCF :1;
			v32t :1;
			v32t LBDFCF :1;
			v32t CTSCF :1;
			v32t :1;
			v32t RTOCF :1;
			v32t EOBCF :1;
			v32t :4;
			v32t CMCF :1;
			v32t :2;
			v32t WUCF :1;
			v32t :11;
		NAMED
	ICR;

	uint8_t RDR;
	uint8_t :8;
	uint16_t :16;

	uint8_t TDR;
	uint8_t :8;
	uint16_t :16;
};

extern volatile USART_BASE_t& USART1;
extern volatile USART_BASE_t& USART2;
extern volatile USART_BASE_t& USART3;
extern volatile USART_BASE_t& USART4;
extern volatile USART_BASE_t& USART5;

}
}
