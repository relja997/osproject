/*
 * Other.h
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#ifndef OS1VJEZB_OTHER_H_
#define OS1VJEZB_OTHER_H_
#include"PCB.h"
#include "IdleThrd.h";
#include "BlkQueue.h"
#include "SemList.h"

class PCB;

class Other {
	friend class Test;
	friend class Thread;
	friend class PCB;

private:
	volatile static int lockFlag;
	volatile static int context_on_demand;
public:
	static void lock();
	static void unlock();
	static void inicinterrupt();
	static void restoreinterrupt();
	volatile static PCB* idleThread;
	volatile static PCB* mainThread;
	volatile static PCB* running;
	volatile static SemList* semaphores_list;
	static void exit_thread();
};

#endif /* OS1VJEZB_OTHER_H_ */
