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
*                                            EXAMPLE CODE
*
*                                         ATMEL AT91SAM9M10
*                                               on the
*                                AT91SAM9M10-G45-EK DEVELOPMENT BOARD
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : JM
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                         LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_TaskStart    (void *p_arg);
static  void  App_ObjCreate    (void);
static  void  App_TaskCreate   (void);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is the standard entry point for C code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

int  main (void)
{
                                           /* Start multitasking (i.e. give control to uC/OS-II)       */
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  void  App_TaskStart (void *p_arg)
{
    
}


/*
*********************************************************************************************************
*                                      App_ObjCreate()
*
* Description : Create applications objects.
*
* Argument(s) : none.
*
* Return(s)   : None.
*
* Caller(s)   : App_TaskStart().
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  void  App_ObjCreate (void)
{

}

/*
*********************************************************************************************************
*                                      App_TaskCreate()
*
* Description : Create application Tasks.
*
* Argument(s) : None.
*
* Return(s)   : None.
*
* Caller(s)   : App_TaskStart()
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  void  App_TaskCreate (void)
{

}