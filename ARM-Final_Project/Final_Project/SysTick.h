/******************************************************************************
 *
 * Module: SysTick
 *
 * File Name: SysTick.h
 *
 * Description: Header file for the ARM Cortex M4 SysTick driver
 *
 * Author: Yousouf Soliman
 *
 *******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                           Pre-Processor Macros                              *
 *******************************************************************************/
#define F_CPU 16000000UL


/*******************************************************************************
 *                                Function Prototypes                          *
 *******************************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds);
/*Description: Initialize the SysTick timer with the specified time in milliseconds
using interrupts. This function is used to setup the timer to generate periodic
interrupts every specified time in milliseconds.*/

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
/*Description: Initialize the SysTick timer with the specified time in milliseconds
using polling or busy-wait technique. The function should exit when the time is
elapsed and stops the timer at the end.*/

void SysTick_Handler(void);
/*Description: Handler for SysTick interrupt use to call the call-back function.*/

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
/*Description: Function to setup the SysTick Timer call back to be executed in
SysTick Handler.*/

void SysTick_Stop(void);
/*Description: Stop the SysTick timer.*/

void SysTick_Start(void);
/*Description: Start/Resume the SysTick timer.*/

void SysTick_DeInit(void);
/*Description: Function to De-initialize the SysTick Timer.*/

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/

#endif /* SYSTICK_H_ */
