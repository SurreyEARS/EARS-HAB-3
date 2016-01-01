/*
 * device_dma.hpp
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

}
}
