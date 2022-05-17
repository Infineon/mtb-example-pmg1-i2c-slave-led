/******************************************************************************
 * File Name:   main.c
 *
 * Description: This is the source code for the I2C Slave LED Example
 *              for ModusToolbox.
 *
 * Related Document: See README.md
 *
 *******************************************************************************
 * Copyright 2022, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 *******************************************************************************/


/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "cy_pdl.h"
#include "cybsp.h"
#include "i2c_slave.h"


/*******************************************************************************
* Function Prototypes
********************************************************************************/
/* Function to handle the error */
static void handle_error(void);


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  System entrance point. This function performs
*  - initial setup of device
*  - configure the SCB block as I2C slave
*  - check the I2C buffer for commands
*       - update the LED status based on the command received from the I2C master
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;
    uint32_t status;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize and configure the I2C slave SCB*/
    status = InitI2CSlave();

    if(status == I2C_FAILURE)
    {
        /* NOTE: This function will block the CPU forever */
        handle_error();
    }

    /* Enable global interrupts */
    __enable_irq();

    /*
     * After the initialization is complete, keep processing the I2C slave buffer
     */
    for (;;)
    {
        /* Check I2C slave buffer for commands */
        CheckEzI2Cbuffer();
    }
}


/*******************************************************************************
* Function Name: handle_error
********************************************************************************
*
* Summary:
*  This is a blocking function. It disables the interrupt and waits
*  in an infinite loop. This function is called when an error is
*  encountered during initialization of the block
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void handle_error(void)
{
    /* Disable all interrupts. */
    __disable_irq();

    /* Infinite loop. */
    while(1u) {}
}

/* [] END OF FILE */