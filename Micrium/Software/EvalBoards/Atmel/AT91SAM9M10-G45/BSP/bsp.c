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

