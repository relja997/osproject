/*
 * PCB.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#include "PCB.h"
#include<dos.h>
#include "SCHEDULE.H"
#include "Other.h"
#include "List.h"

#define max_stack_size 65535

volatile static unsigned tss;
volatile static unsigned tsp;
volatile static unsigned tbp;
volatile unsigned PCB::counter = 20;
static ID startID = -1;
ThrdLst *PCB::thread_list = new ThrdLst();
extern void tick() ;

class Other;
class List;

PCB::PCB(StackSize stackSize_, Time timeSlice_, Thread* thr) {
	if (stackSize > max_stack_size)
		stackSize_ = max_stack_size;
	ss = sp = bp = 0;
	timeSlice = timeSlice_;
	stackSize = stackSize_;
	myThread = thr;
	state = CREATED;
	ID_ = ++startID;
	blkFlag = 1;
	stack = new unsigned[stackSize];
	wtclist = new List();
	thread_list->put(myThread);
}


void PCB::load_context() {

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 1] = FP_SEG(myThread);
	stack[stackSize - 2] = FP_OFF(myThread);
	// -3 i -4 su segment i ofset funkcije callback
	stack[stackSize - 5] = 0x200;// PSW sa aktivnim I-bitom
	stack[stackSize - 6] = FP_SEG(wrapper);
	stack[stackSize - 7] = FP_OFF(wrapper);

	ss = FP_SEG(stack + stackSize - 16);//stavljamo SP da pokazuje na slobodno mjesto u steku
	sp = FP_OFF(stack + stackSize - 16);// -||-
	bp = sp;//stavljamo BP na SP zbog moguce promjene vrijednosti SP-registra

	this->state = READY;
	if(this != Other::idleThread) {
		Scheduler::put(this);
	}

#endif
}

void PCB::dispatch() {
#ifndef BCC_BLOCK_IGNORE
	asm cli
	Other::context_on_demand = 1;
	timer();
	asm sti
#endif
}

void interrupt PCB::timer() {
	if(!Other::context_on_demand){
		tick();
		Other::semaphores_list->semListDecrement();
		if(PCB::counter > 0)
			if (((PCB *)Other::running)->timeSlice!=0)
						PCB::counter--;
	}


	if ((PCB::counter == 0 && Other::running->timeSlice != 0)
			|| Other::context_on_demand) {
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tss, ss
			mov tsp, sp
			mov tbp, bp
		}
#endif
		Other::running->ss = tss;
		Other::running->sp = tsp;
		Other::running->bp = tbp;

		if (Other::running->state == PCB::READY
				&& (PCB*) Other::running != (PCB*) Other::idleThread)
			Scheduler::put((PCB*) Other::running);

		Other::running = Scheduler::get();

		if (Other::running == 0)
			Other::running = Other::idleThread;

		tss = Other::running->ss;
		tsp = Other::running->sp;
		tbp = Other::running->bp;

		PCB::counter = ((PCB*) Other::running)->timeSlice;
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov ss, tss
			mov sp, tsp
			mov bp, tbp
		}
#endif
	}
	if (!Other::context_on_demand)
#ifndef BCC_BLOCK_IGNORE
		asm int 60h;
#endif

		Other::context_on_demand = 0;

}

void PCB::wrapper() {
	Other::running->myThread->run();
#ifndef BCC_BLOCK_IGNORE
	Other::running->clear_waitlist();
#endif
	Other::exit_thread();
}

PCB::~PCB() {
	this->myThread->myPCB = 0;
	this->myThread = 0;
	delete[] stack;
	stack = 0;
}

void PCB::clear_waitlist() {
	if (wtclist->head != 0) {
		for (List::Elem *tek = wtclist->head; tek != 0; tek = tek->next) {
			Other::lock();
			tek->pcb->state = PCB::READY;
			Scheduler::put(tek->pcb);
			Other::unlock();
		}
	}
	delete wtclist;
}

