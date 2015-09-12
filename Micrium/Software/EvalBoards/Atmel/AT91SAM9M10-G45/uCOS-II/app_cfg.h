/*
*********************************************************************************************************
*                                              EXAMPLE CODE
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
*                                     APPLICATION CONFIGURATION
*
*                                         ATMEL AT91SAM9M10
*                                               on the
*                                AT91SAM9M10-G45-EK DEVELOPMENT BOARD
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : JM
*********************************************************************************************************
*/

#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                          2u

#define  OS_TASK_TMR_PRIO               (OS_LOWEST_PRIO - 2u)


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/



#endif
