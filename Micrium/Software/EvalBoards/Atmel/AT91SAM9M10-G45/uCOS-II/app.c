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

static  OS_STK  App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];


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
#if (OS_TASK_NAME_EN == DEF_ENABLED)
    CPU_INT08U	os_err;
#endif    
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR     cpu_err;
#endif
    
    
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_NameSet((CPU_CHAR *)"AT91SAM9M10 CU-ES2",
                (CPU_ERR  *)&cpu_err);
#endif    

    BSP_PreInit();                                              /* System pre-initialization.                               */

    CPU_Init();
    Mem_Init();
    
    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt((void (*)(void *)) App_TaskStart,           /* Create the start task                                    */
                    (void           *) 0,
                    (OS_STK         *)&App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_START_PRIO,
                    (INT16U          ) APP_CFG_TASK_START_PRIO,
                    (OS_STK         *)&App_TaskStartStk[0],
                    (INT32U          ) APP_CFG_TASK_START_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN == DEF_ENABLED)
    OSTaskNameSet((INT8U  )APP_CFG_TASK_START_PRIO,
                  (INT8U *)"Start Task",
                  (INT8U *)&os_err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)       */
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
    CPU_INT08U  i;
    
    
    (void)p_arg;

    BSP_PostInit();                                             /* Initialize BSP functions                                 */

    OS_CSP_TickInit();
            
#if OS_TASK_STAT_EN > 0u
    OSStatInit();                                               /* Determine CPU capacity                                   */
#endif

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
    App_SerialInit();
#endif
            
    App_ObjCreate();                                            /* Create application objects                               */
    App_TaskCreate();                                           /* Create application tasks                                 */
    
    BSP_LED_Off(0);
    
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.           */
        for (i = 1; i<=3; i++) {
            BSP_LED_On(i);
            OSTimeDlyHMSM(0, 0, 0, 250);
            BSP_LED_Off(i);
        }
        
        OSTimeDlyHMSM(0, 0, 1, 0);
        
        for (i = 4; i>=1; i--) {
            BSP_LED_Toggle(0);
            OSTimeDlyHMSM(0, 0, 0, 250);
        }
    }
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