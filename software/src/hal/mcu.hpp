/*
 * mcu.hpp
 *
 *  Created on: Nov 19, 2015
 *      Author: James
 */

namespace HAL {
namespace MCU {

void init();
uint32_t getTicks(void);
void delayTicks(uint32_t delay);
void SuspendTick(void);
void ResumeTick(void);

}
}
