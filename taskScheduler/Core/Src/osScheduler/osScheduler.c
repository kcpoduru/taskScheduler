/*
 * osScheduler.c
 *
 *  Created on: May 23, 2020
 *      Author: ko106n4
 */

#include "osScheduler.h"



uint32_t pspOfTasks[MAX_TASKS]  = {T1_STACK_START,T2_STACK_START,T3_STACK_START,T4_STACK_START};
uint32_t taskHandlerAdresses[MAX_TASKS] = {(uint32_t)task1_handler,(uint32_t)task2_handler,(uint32_t)task3_handler,(uint32_t)task4_handler};
uint8_t currentTask = 0;



void __attribute__((naked)) initSchedulerStack(uint32_t stackLocation)
{
  __asm volatile("MSR MSP, %0" : : "r"(stackLocation) :) ;
  __asm volatile("BX LR"); // we need to do this because naked functions does not create epilogue or prologue so we need to manually write the return address.

}


void initTaskStack(void)
{

	uint32_t *pPSP;

	for(int i = 0 ; i < MAX_TASKS ; i++)
	{
		pPSP = (uint32_t *)pspOfTasks[i];
		pPSP--;
		*pPSP = DUMMY_XPSR; //0x01000000 for enabling the T bit


		pPSP--; // PC
		*pPSP = taskHandlerAdresses[i];


		pPSP--; //LR
		*pPSP = 0xFFFFFFFD;//return address if you are using the PSP in thread mode...refer to ARM document


		for(int j = 0; j < 13 ; j++)
		{
			pPSP--;
			*pPSP = 0;
		}

		pspOfTasks[i] = (uint32_t)pPSP;

	}

}


void enableProcesorFaults(void)
{
	uint32_t *pSHCSR = (uint32_t *)0xE000ED24;
	*pSHCSR |= (1 << 16); //mem manage fault enable
	*pSHCSR |= (1 << 17); //bus fault
	*pSHCSR |= (1 << 18); //usage fault
}

uint32_t getCurrentPSPValue(void)
{
	return pspOfTasks[currentTask];
}


void __attribute__((naked))  switchSPToPSP(void)
{
//1. Initialize the PSP with the TASk1 stack START
	__asm volatile ("PUSH {LR}"); // because in the next instruction the linker value gets corrupted. So we nede to preserve this so that we can go back to the main function or where ever it is being called
	__asm volatile ("BL getCurrentPSPValue"); //we need to do BL because we want to do branch and link so that the function returns here instead of just B
	__asm volatile ("MSR PSP, R0"); // we are choosing R0 because as per the functional call standards the return argument of the above statement is stored in R0
	__asm volatile ("POP {LR}");
//2. Change SP to PSP using the control register
	__asm volatile ("MOV R0, 0x02");
	__asm volatile ("MSR CONTROL, R0");
	__asm volatile ("BX LR");

}


void savePSPValue(uint32_t currentTaskAddress)
{
	pspOfTasks[currentTask] = currentTaskAddress;
}

void updateNextTask(void)
{
	currentTask++;
	currentTask %= MAX_TASKS;
}


/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  /*
   * First save the context of current task
   */
  //1. Get the current running task PSP value
  __asm volatile("MRS R0, PSP");
  //2. Using the PSP value store SF2(r4 to r11)
  __asm volatile("STMDB R0!, {R4-R11}");
  //3. save the current value of PSP
  __asm volatile("BL savePSPValue");
  /*
   * retrieve the context of next task
   */
  //1. decide next task to run
  __asm volatile("BL updateNextTask");
  //2. get its past PSP value
  __asm volatile("BL  getCurrentPSPValue");
  //3. using that PSP value retrieve SF2(R4 to R11)
  __asm volatile("LDMIA R0!, {R4-R11}");
  //4. update PSP and exit
  __asm volatile("MSR PSP, R0");



  /* USER CODE END SysTick_IRQn 1 */
}



/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}


