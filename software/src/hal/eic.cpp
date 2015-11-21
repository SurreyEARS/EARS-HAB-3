/*
 * eic.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: James
 */

extern "C" {
	void HAL_EIC_DefaultInterruptHandler()
	{

	}

	void HAL_EIC_NMI_Handler(void)
	{

	}

	void HAL_EIC_HardFault_Handler(void)
	{
	  /* Go to infinite loop when Hard Fault exception occurs */
	  while (1)
	  {
	  }
	}

	void HAL_EIC_MemManage_Handler(void)
	{
	  /* Go to infinite loop when Memory Manage exception occurs */
	  while (1)
	  {
	  }
	}

	void HAL_EIC_BusFault_Handler(void)
	{
	  /* Go to infinite loop when Bus Fault exception occurs */
	  while (1)
	  {
	  }
	}

	void HAL_EIC_UsageFault_Handler(void)
	{
	  /* Go to infinite loop when Usage Fault exception occurs */
	  while (1)
	  {
	  }
	}

	void HAL_EIC_SVC_Handler(void)
	{
	}

	void HAL_EIC_DebugMon_Handler(void)
	{
	}

	void HAL_EIC_PendSV_Handler(void)
	{
	}
}
