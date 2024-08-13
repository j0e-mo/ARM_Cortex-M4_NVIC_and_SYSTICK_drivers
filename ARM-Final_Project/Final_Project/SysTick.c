/******************************************************************************
 *
 * Module: SysTick
 *
 * File Name: SysTick.c
 *
 * Description: Source file for the ARM Cortex M4 SysTick driver
 *
 * Author: Yousouf Soliman
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/* Variable to store the address of the call-back function provided by the APP layer */

/*******************************************************************************
 *                               Function Definitions                          *
 *******************************************************************************/

/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): none
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Handler for SysTick interrupt use to call the call-back function.
**********************************************************************/
void SysTick_Handler(void)
{
    if (g_callBackPtr != NULL_PTR)
    {
        /* Call the Call Back function in the application after the edge is detected */
        (*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
    }
}

/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): *Ptr2Func - Pointer to a function that has a void return type and no parameters in.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler.
**********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void))
{
    /* Save the address of the Call back function in a global variable */
    g_callBackPtr = Ptr2Func;
}

/*********************************************************************
* Service Name: SysTick_Init
* Sync/Async: Asynchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - uint16 value that contains the required time to be counted
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the SysTick timer with the specified time in milliseconds
* using interrupts. This function is used to setup the timer to generate periodic
* interrupts every specified time in milliseconds.
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG = 0; /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG = (a_TimeInMilliSeconds * (F_CPU / 1000)) - 1; /* Set the Reload value with the required time in ms */
    SYSTICK_CURRENT_REG = 0; /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Disable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG |= 0x06;
    /* Enable the SysTick Timer (ENABLE = 1) */
    SysTick_Start();
}


/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - uint16 value that contains the required time to be counted
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the SysTick timer with the specified time in milliseconds
* using polling or busy-wait technique. The function should exit when the time is
* elapsed and stops the timer at the end.
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG = 0; /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG = (a_TimeInMilliSeconds * (F_CPU / 1000)) - 1; /* Set the Reload value with the required time in ms */
    SYSTICK_CURRENT_REG = 0; /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG |= 0x04;
    /* Enable the SysTick Timer (ENABLE = 1) */
    SysTick_Start();

    while(!(SYSTICK_CTRL_REG & (1<<16)));
    /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */
    SysTick_Stop();
    /* Stop the timer after time has elapsed */
}

/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): none
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stop the SysTick timer.
**********************************************************************/
void SysTick_Stop(void)
{
    /* Disable the SysTick Timer (ENABLE = 0)*/
    SYSTICK_CTRL_REG &= ~0x01;
}

/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): none
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Start the SysTick timer.
**********************************************************************/
void SysTick_Start(void)
{
    /* Enable the SysTick Timer (ENABLE = 1)*/
    SYSTICK_CTRL_REG |= 0x01;
}


/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): none
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to De-initialize the SysTick Timer.
**********************************************************************/
void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG = 0; /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG = 0; /* Clear the reload register */
    SYSTICK_CURRENT_REG = 0; /* Clear the Current Register value */
}

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
