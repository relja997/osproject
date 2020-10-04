/*
 * PCB.h
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#ifndef OS1VJEZB_PCB_H_
#define OS1VJEZB_PCB_H_
#include "List.h"
#include "Thread.h"
#include "ThrdLst.h"


class List;

class PCB {
public:
	friend class Other;
	friend class Thread;
	friend class List;
	friend class BlkQueue;
	friend class KernelSem;
	friend class KernelEv;
	
	static void dispatch();
	static void interrupt timer();
	volatile static unsigned int counter;
	int blkFlag;
	static ThrdLst* thread_list;


	~PCB();
	typedef enum State {CREATED, READY, BLOCKED, FINISHED} State;
private:
	unsigned *stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	ID ID_;
	Thread* myThread;
	Time timeSlice;
	StackSize stackSize;
	State state;
	List *wtclist;
	void clear_waitlist();

	PCB(StackSize stackSize_, Time timeSlice_, Thread* thr);
	void load_context();
	static void wrapper();
};

#endif /* OS1VJEZB_PCB_H_ */
