/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.c
 *
 * Description: Source file for the ARM Cortex M4 NVIC driver
 *
 * Author: Yousouf Soliman
 *
 *******************************************************************************/

#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"

/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
 **********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num <= 136)
    {
        (*((volatile uint32*) (0xE000E100 + ((IRQ_Num >> 5) << 2)))) |= (1
                << (IRQ_Num - ((IRQ_Num >> 5) << 5)));
    }
}

/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
 **********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num <= 136)
    {
        (*((volatile uint32*) (0xE000E100 + ((IRQ_Num >> 5) << 2)))) &= ~(1
                << (IRQ_Num - ((IRQ_Num >> 5) << 5)));
    }
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 *                   IRQ_Priority - The required priority of this specific IRQ
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for specific IRQ.
 **********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,
                         NVIC_IRQPriorityType IRQ_Priority)
{
    if (IRQ_Num <= 136)
    {
        if (!(IRQ_Num >> 2))
        {
            (*((volatile uint32*) (0xE000E100 + ((IRQ_Num >> 2) << 2)))) =
                    ((*((volatile uint32*) (0xE000E100 + ((IRQ_Num >> 2) << 2))))
                            & (~(0x7 << (IRQ_Num * 8 + 5))))
                            | (IRQ_Priority << (IRQ_Num * 8 + 5));
        }
        else
        {
            (*((volatile uint32*) (0xE000E100 + ((IRQ_Num >> 2) << 2)))) =
                    ((*((volatile uint32*) (0xE000E100 + ((IRQ_Num >> 2) << 2))))
                            & (~(0x7 << ((IRQ_Num % 4) * 8 + 5))))
                            | (IRQ_Priority << ((IRQ_Num % 4) * 8 + 5));
        }
    }

}

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable specific ARM system or fault exceptions.
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE
            || Exception_Num == EXCEPTION_BUS_FAULT_TYPE
            || Exception_Num == EXCEPTION_USAGE_FAULT_TYPE

            )
    {
        NVIC_SYSTEM_SYSHNDCTRL |= (1 << (Exception_Num + 12));
    }
}

/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable specific ARM system or fault exceptions.
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE
            || Exception_Num == EXCEPTION_BUS_FAULT_TYPE
            || Exception_Num == EXCEPTION_USAGE_FAULT_TYPE

            )
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << (Exception_Num + 12));
    }
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 *                   Exception_Priority - The required priority of this specific Exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for specific ARM system or fault
 * exceptions.
 **********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num,
                               NVIC_ExceptionPriorityType Exception_Priority)
{
    if (Exception_Num <= 15)
    {
        (*((volatile uint32*) (0xE000ED14 + ((Exception_Num >> 2) << 2)))) =
                ((*((volatile uint32*) (0xE000ED14 + ((Exception_Num >> 2) << 2))))
                        & (~(0x7 << ((Exception_Num % 4) * 8 + 5))))
                        | (Exception_Priority << ((Exception_Num % 4) * 8 + 5));
    }
}
