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


#define MAX_TASKS							4
#define T1_STACK_START						(SRAM_END)
#define T2_STACK_START						(T1_STACK_START - SIZE_TASK_STACK)
#define T3_STACK_START						(T2_STACK_START - SIZE_TASK_STACK)
#define T4_STACK_START						(T3_STACK_START - SIZE_TASK_STACK)
#define SCHED_TASK_START					(T4_STACK_START - SIZE_TASK_STACK)

#define DUMMY_XPSR							0x01000000U




void initTaskStack(void);
void __attribute__((naked)) initSchedulerStack(uint32_t stackLocation);
void enableProcesorFaults(void);
void __attribute__((naked)) switchSPToPSP(void);

#endif /* SRC_OSSCHEDULER_OSSCHEDULER_H_ */
