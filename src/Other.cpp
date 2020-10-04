/*
 * Other.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#include "Other.h"
#include<dos.h>

volatile int Other::lockFlag = 0;
volatile int Other::context_on_demand = 0;
volatile PCB* Other::idleThread = 0;
volatile PCB* Other::mainThread = 0;
volatile PCB* Other::running = 0;
volatile SemList* Other::semaphores_list = new SemList();

typedef void interrupt (*pInterrupt)(...);

static pInterrupt oldInterrupt;

void Other::exit_thread(){
	Other::running->state = PCB::FINISHED;
	PCB::dispatch();
}

void Other::inicinterrupt(){
	Other::lock();
#ifndef BCC_BLOCK_IGNORE
	oldInterrupt = getvect(0x8);
	setvect(0x8, (pInterrupt) PCB::timer);
	setvect(0x60, oldInterrupt);
#endif
	Other::idleThread = (new IdleThrd(300,2))->myPCB;
	Other::idleThread->myThread->start();
	Other::mainThread = (new Thread(0,2))->myPCB;
	mainThread->state = PCB::READY;
	running = mainThread;
	PCB::counter = running->timeSlice;
	Other::unlock();
}

void Other::restoreinterrupt(){
	Other::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8, oldInterrupt);
#endif
	Other::unlock();
}

void Other::lock(){
	Other::lockFlag = 1;
}

void Other::unlock(){
	lockFlag = 0;
	if(context_on_demand)
		dispatch();
}

