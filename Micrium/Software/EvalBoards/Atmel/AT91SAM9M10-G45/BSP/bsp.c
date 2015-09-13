/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*
*                                      BOARD SUPPORT PACKAGE (BSP)
*
*                                         ATMEL AT91SAM9M10
*                                               on the
*                                AT91SAM9M10-G45-EK DEVELOPMENT BOARD
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : FT
*                 JM
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   BSP_MODULE

#include  <bsp.h>
#include  <os_cpu.h>


void OS_CPU_ExceptHndlr(INT32U except_type)
{
    
}


/*
*********************************************************************************************************
*                                             REGISTER & BIT DEFINES
*********************************************************************************************************
*/

#define  BSP_PMC_MOR                            (*(CPU_REG32 *)(0xFFFFFC20))
#define  BSP_PMC_SR                             (*(CPU_REG32 *)(0xFFFFFC68))
#define  BSP_PMC_PLLA                           (*(CPU_REG32 *)(0xFFFFFC28))
#define  BSP_PMC_MCKR                           (*(CPU_REG32 *)(0xFFFFFC30))
#define  BSP_WDTC_WDMR                          (*(CPU_REG32 *)(0xFFFFFD44))
#define  BSP_MATRIX_MRCR                        (*(CPU_REG32 *)(0xFFFFEB00))


/*
*********************************************************************************************************
*                                             GPIO DEFINES
*********************************************************************************************************
*/

#define  BSP_GPIO_PORTD_LED_01                  DEF_BIT_00
#define  BSP_GPIO_PORTD_LED_02                  DEF_BIT_31
#define  BSP_GPIO_PORTD_LED_03                  DEF_BIT_30
#define  BSP_GPIO_PORTD_LED_GRP                (BSP_GPIO_PORTD_LED_01 | \
                                                BSP_GPIO_PORTD_LED_02 | \
                                                BSP_GPIO_PORTD_LED_03)

#define  BSP_GPIO_PORTB_JOY_UP                  DEF_BIT_16
#define  BSP_GPIO_PORTB_JOY_DOWN                DEF_BIT_17
#define  BSP_GPIO_PORTB_JOY_LEFT                DEF_BIT_14
#define  BSP_GPIO_PORTB_JOY_RIGHT               DEF_BIT_15
#define  BSP_GPIO_PORTB_JOY_CENTER              DEF_BIT_18

#define  BSP_GPIO_PORTB_JOY_GRP                (BSP_GPIO_PORTB_JOY_UP     | \
                                                BSP_GPIO_PORTB_JOY_DOWN   | \
                                                BSP_GPIO_PORTB_JOY_LEFT   | \
                                                BSP_GPIO_PORTB_JOY_RIGHT  | \
                                                BSP_GPIO_PORTB_JOY_CENTER)

#define  BSP_GPIO_PORTB_PB_00                   DEF_BIT_06
#define  BSP_GPIO_PORTB_PB_01                   DEF_BIT_07
#define  BSP_GPIO_PORTB_PB_GRP                 (BSP_GPIO_PORTB_PB_00 | \
                                                BSP_GPIO_PORTB_PB_01)


/*
*********************************************************************************************************
*                                             BSP CONSTANS VALUES
*********************************************************************************************************
*/
                                                                /* Maximum register timeout                            */
#define  BSP_VAL_MAX_TO                         (CPU_INT16U)(0xFFFF)


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_LowLevelInit()
*
* Description : System Low Level Init (PLLs, External Memories, Boot loaders, etc).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Startup Code.
* 
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LowLevelInit (void)
{

}


/*
*********************************************************************************************************
*                                             BSP_PreInit()
*
* Description : System Pre-Initialization. Initializes all peripherals that don't require OS services (LEDs, PBs)
*               or modules than need to be initialized before the OS (External memories).
*
* Argument(s) : main().
*
* Return(s)   : none.
*
* Note(s)     : (1) Clocks initialization should be ONLY perform when code is NOT executed from DDRAM.
*
*               (2) This funtions configure the clocks as:
*                       
*                       (a) CPU clock    @ 400Mhz.
*                       (b) Master clock @ 133Mhz.
*********************************************************************************************************
*/

void  BSP_PreInit (void)
{
#ifndef APP_CFG_DDRAM_EN
    CPU_INT32U  reg_to;
    CPU_INT32U  reg_val;
#endif
    
    
#ifndef APP_CFG_DDRAM_EN                                        /* See note #1.                                         */
    BSP_PMC_MOR = DEF_BIT_00                                    /* Enable main oscillator.                              */
                | (64u << 8u);

    reg_to  = BSP_VAL_MAX_TO;
    reg_val = BSP_PMC_SR;    
    while ((reg_to > 0u) &&
           (DEF_BIT_IS_CLR(reg_val, DEF_BIT_00))) {
        reg_to--;
        reg_val = BSP_PMC_SR;
    }

    if (reg_to == 0u) {
        return;
    }
                                                                /* Initialize PLLA  for 800 Mhz.                        */
    BSP_PMC_PLLA =  DEF_BIT_29                                  /* ... Bit 29 must always set to 1 CKGR_PLLAR           */
                 |  0x3F       << 8u                            /* ... Set the PLLA counter.                            */
                 | (200u - 1u) << 16u                           /* ... Set the PLL multiplier  = 200                    */
                 |  3u;                                         /* ... Set the PLL divider     = 3                      */
    
    reg_to  = BSP_VAL_MAX_TO;                                   /* ... Wait for the PLL setup.                          */
    reg_val = BSP_PMC_SR;    
    while ((reg_to > 0u) &&
           (DEF_BIT_IS_CLR(reg_val, DEF_BIT_01))) {
        reg_to--;
        reg_val = BSP_PMC_SR;
    }

    if (reg_to == 0u) {
        return;
    }

    reg_to  = BSP_VAL_MAX_TO;                                   /* Wait for master clock.                                */
    reg_val = BSP_PMC_SR;    
    while ((reg_to > 0u) &&
           (DEF_BIT_IS_CLR(reg_val, DEF_BIT_03))) {
        reg_to--;
        reg_val = BSP_PMC_SR;
    }

    if (reg_to == 0u) {
        return;
    }    
    
                                                                /* Switch to master clock.                              */
    BSP_PMC_MCKR = (3u  << 8u)                                  /* ... Mclk    = CPUclk  / 3                            */
                 | DEF_BIT_12;                                  /* ... PLLDIV2 = PLLA / 2                               */

    reg_to  = BSP_VAL_MAX_TO;                                   /* Wait for master clock.                               */
    reg_val = BSP_PMC_SR;    
    while ((reg_to > 0u) &&
           (DEF_BIT_IS_CLR(reg_val, DEF_BIT_03))) {
        reg_to--;
        reg_val = BSP_PMC_SR;
    }

    if (reg_to == 0u) {
        return;
    }    

    BSP_PMC_MCKR |= 2u;
    
    
    reg_to  = BSP_VAL_MAX_TO;                                   /* Wait for master clock.                               */
    reg_val = BSP_PMC_SR;    
    while ((reg_to > 0u) &&
           (DEF_BIT_IS_CLR(reg_val, DEF_BIT_03))) {
        reg_to--;
        reg_val = BSP_PMC_SR;
    }

    if (reg_to == 0u) {
        return;
    }    
#endif
    
    BSP_WDTC_WDMR   = DEF_BIT_15;                               /* Disable Watchdog timer.                              */
    BSP_MATRIX_MRCR = DEF_BIT_00                                /* Remamp Internal RAM.                                 */
                    | DEF_BIT_01;

    OS_CPU_InitExceptVect(); 
    CSP_IntInit();                                              /* Initialize interrupt controller module.              */
}


/*
*********************************************************************************************************
*                                             BSP_PostInit()
*
* Description : Initialize all the peripherals that required OS services (OS initialized)
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_PostInit (void)
{   
    CSP_PM_PerClkEn(CSP_PM_PER_CLK_NBR_GPIO_B);
    CSP_PM_PerClkEn(CSP_PM_PER_CLK_NBR_GPIO_D);    
                                                                /* ------------------ LEDs GPIO INIT ------------------ */
    CSP_GPIO_Cfg(CSP_GPIO_PORT_NBR_D,         
                 BSP_GPIO_PORTD_LED_GRP,
                 CSP_GPIO_DIR_OUT,
                 CSP_GPIO_FLAG_MODE_NONE,
                 DEF_NO,
                 DEF_BIT_NONE,
                 CSP_GPIO_FNCT_00);
                                                                /* ------------------- PBs GPIO INIT ------------------ */
    CSP_GPIO_Cfg(CSP_GPIO_PORT_NBR_B,
                 BSP_GPIO_PORTB_PB_GRP,
                 CSP_GPIO_DIR_IN,
                 CSP_GPIO_FLAG_MODE_NONE,
                 DEF_NO,
                 DEF_BIT_NONE,
                 CSP_GPIO_FNCT_00);
                                                                /* ---------------- JOYSTICK GPIO INIT ---------------- */
    CSP_GPIO_Cfg(CSP_GPIO_PORT_NBR_B,
                 BSP_GPIO_PORTB_JOY_GRP,
                 CSP_GPIO_DIR_IN,
                 CSP_GPIO_FLAG_MODE_NONE,
                 DEF_NO,
                 DEF_BIT_NONE,
                 CSP_GPIO_FNCT_00);    
}


/*
*********************************************************************************************************
*                                                 BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led    The ID of the LED to control:
*
*                           0    turn OFF all LEDs on the board.
*                           1    turn OFF LED1.
*                           2    turn OFF LED2.
*                           3    turn OFF LED3. (Power LED).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U  led) 
{
    switch (led) {
        case 0u:
             CSP_GPIO_BitSet(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_01 | BSP_GPIO_PORTD_LED_02);

             CSP_GPIO_BitClr(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_03);             
             break;
    
        case 1u:
             CSP_GPIO_BitSet(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_01);
             break;

        case 2u:
             CSP_GPIO_BitSet(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_02);
             break;

        case 3u:
             CSP_GPIO_BitClr(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_03);
             break;

        default:
             break;

    }    
}


/*
*********************************************************************************************************
*                                                 BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*                           0    turn ON all LEDs on the board.
*                           1    turn ON LED1.
*                           2    turn ON LED2.
*                           3    turn ON LED3.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U  led) 
{
    switch (led) {
        case 0u:
             CSP_GPIO_BitClr(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_01 | BSP_GPIO_PORTD_LED_02);

             CSP_GPIO_BitSet(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_03);             
             break;
    
        case 1u:
             CSP_GPIO_BitClr(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_01);
             break;

        case 2u:
             CSP_GPIO_BitClr(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_02);
             break;

        case 3u:
             CSP_GPIO_BitSet(CSP_GPIO_PORT_NBR_D,
                             BSP_GPIO_PORTD_LED_03);
             break;

        default:
             break;

    }     
}


/*
*********************************************************************************************************
*                                                 BSP_LED_Toggle()
*
* Description : Toggles any or all the LEDs on the board.
*
* Argument(s) : led_id   The ID of the LED to control:
*
*                       0    toggle all LEDs on the board
*                       1    toggle LED1
*                       2    toggle LED2
*                       3    toggle LED3
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U  led) 
{
    switch (led) {
        case 0u:
             CSP_GPIO_BitToggle(CSP_GPIO_PORT_NBR_D,
                                BSP_GPIO_PORTD_LED_GRP);
             break;
    
        case 1u:
             CSP_GPIO_BitToggle(CSP_GPIO_PORT_NBR_D,
                                BSP_GPIO_PORTD_LED_01);
             break;

        case 2u:
             CSP_GPIO_BitToggle(CSP_GPIO_PORT_NBR_D,
                                BSP_GPIO_PORTD_LED_02);
             break;

        case 3u:
             CSP_GPIO_BitToggle(CSP_GPIO_PORT_NBR_D,
                                BSP_GPIO_PORTD_LED_03);
             break;

        default:
             break;

    }     
}


/*
*********************************************************************************************************
*                                           BSP_PB_StatusGet()
*
* Description : Get the status of the board's push buttons.
*
* Argument(s) : pb   Push button Identifier
*
*                       1  Left  button.
*                       2  Right button.
*
* Return(s)   : DEF_ON   If the push button is pressed
*               DEF_OFF, otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_StatusGet (CPU_INT08U pb)
{
    CSP_GPIO_MSK  port_val;
    CPU_BOOLEAN   status;
       

    status   = DEF_OFF;
    port_val = CSP_GPIO_Rd(CSP_GPIO_PORT_NBR_B);
    
    switch (pb) {
        case 0u:    
             if (DEF_BIT_IS_SET(port_val, BSP_GPIO_PORTB_PB_00)) {
                 status = DEF_ON;
             }
             break;

        case 1u:
             if (DEF_BIT_IS_SET(port_val, BSP_GPIO_PORTB_PB_00)) {
                 status = DEF_ON;
             }
             break;
             
        default:
             break;
    }
    
    return (status);
}


/*
*********************************************************************************************************
*                                         BSP_JoyPosGet()
*
* Description : Return the joystick position.
*
* Argument(s) : none
*
* Return(s)   : Joystick postition.
*
*                        BSP_JOY_POS_LEFT    If the joystick is toggled left.
*                        BSP_JOY_POS_RIGHT   If the joystick is toggled right.
*                        BSP_JOY_POS_UP      If the joystick is toggled up.
*                        BSP_JOY_POS_DOWN    If the joystick is toggled down.
*                        BSP_JOY_POS_CENTER  If the joystick is being pressed
*                        BSP_JOY_POS_NONE    If the joystick is not being pressed.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_JoyPosGet (void) 
{
    CSP_GPIO_MSK  port_val;
    
    
    port_val = CSP_GPIO_Rd(CSP_GPIO_PORT_NBR_B);
    
    if (DEF_BIT_IS_SET(port_val, BSP_GPIO_PORTB_JOY_LEFT)) {
        return (BSP_JOY_POS_LEFT);
    }
    
    if (DEF_BIT_IS_CLR(port_val, BSP_GPIO_PORTB_JOY_RIGHT)) {
        return (BSP_JOY_POS_RIGHT);
    }

    if (DEF_BIT_IS_CLR(port_val, BSP_GPIO_PORTB_JOY_UP)) {
        return (BSP_JOY_POS_UP);
    }

    if (DEF_BIT_IS_CLR(port_val, BSP_GPIO_PORTB_JOY_DOWN)) {
        return (BSP_JOY_POS_DOWN);
    }

    if (DEF_BIT_IS_CLR(port_val, BSP_GPIO_PORTB_JOY_CENTER)) {
        return (BSP_JOY_POS_CENTER);
    }
    
    return (BSP_JOY_POS_NONE);
}


/*
*********************************************************************************************************
*                                    OS_CSP_BSP_ExceptHandler()
*
* Description : Handles ARM exceptions.
*
* Argument(s) : Exception type.
*
*                   CPU_ARM_EXCEPT_RST              Reset exception.
*                   CPU_ARM_EXCEPT_UND              Undefined instruction.
*                   CPU_ARM_EXCEPT_SWI              Software interrupt.
*                   CPU_ARM_EXCEPT_ABORT_PREFETCH   Prefetch Abort.
*                   CPU_ARM_EXCEPT_ABORT_DATA       Data Abort.
*
* Return(s)   : none.
*
* Caller(s)   : OS_CPU_IntHandler().
*
* Note(s)     : (1) This exception handler is implemented with an infinite loop for 
*                   debugging porpuses only. 
*********************************************************************************************************
*/

void OS_CSP_BSP_ExceptHandler  (CPU_INT08U  except_type)
{
    switch (except_type) {
        case CPU_ARM_EXCEPT_RST:
        case CPU_ARM_EXCEPT_UND:
        case CPU_ARM_EXCEPT_SWI:
        case CPU_ARM_EXCEPT_ABORT_PREFETCH:
        case CPU_ARM_EXCEPT_ABORT_DATA:
             while (DEF_TRUE) {
                 ;
             }
    }
}
