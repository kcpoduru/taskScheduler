/*
 * osScheduler.h
 *
 *  Created on: May 23, 2020
 *      Author: ko106n4
 */

#ifndef SRC_OSSCHEDULER_OSSCHEDULER_H_
#define SRC_OSSCHEDULER_OSSCHEDULER_H_


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"


#define SIZE_TASK_STACK						1024U
#define SIZE_SCHED_STACK					1024U

#define SRAM_START							0x20000000U
#define SIZE_SRAM							(192U * 1024U)
#define SRAM_END							SRAM_START + SIZE_SRAM


#define MAX_TASKS							5
#define T1_STACK_START						(SRAM_END)
#define T2_STACK_START						(T1_STACK_START - SIZE_TASK_STACK)
#define T3_STACK_START						(T2_STACK_START - SIZE_TASK_STACK)
#define T4_STACK_START						(T3_STACK_START - SIZE_TASK_STACK)
#define IDLE_TASK_STACK_START				(T4_STACK_START - SIZE_TASK_STACK)
#define SCHED_TASK_START					(IDLE_TASK_STACK_START - SIZE_TASK_STACK)

#define DUMMY_XPSR							0x01000000U

#define TASK_READY_STATE					0x00
#define TASK_BLOCKED_STATE					0xFF

#define PENDSV_BIT_LOCATION					28

#define INTERRUPT_DISABLE   				do {__asm volatile("MOV R0,#0x01"); __asm volatile("MSR PRIMASK, R0"); } while(0);
#define INTERRUPT_ENABLE   					do {__asm volatile("MOV R0,#0x00"); __asm volatile("MSR PRIMASK, R0"); } while(0);

typedef struct{
	uint32_t pspValue;
	uint32_t blockCount;
	uint8_t currentState;
	void (*taskHandler)(void);
}TCB_t;




void initTaskStack(void);
void __attribute__((naked)) initSchedulerStack(uint32_t stackLocation);
void enableProcesorFaults(void);
void __attribute__((naked)) switchSPToPSP(void);
void taskDelay(uint32_t tickCount); //in milli seconds. This function cannot be used in the idle task
void idleTask_Handler(void);
void scheduleNextTask(void);

#endif /* SRC_OSSCHEDULER_OSSCHEDULER_H_ */
