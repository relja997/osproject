/*
 * KernSem.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: OS1
 */

#include "KernSem.h"
#include "Other.h"
#include "Schedule.h"


KernelSem::KernelSem(int value_, Semaphore* mySem_) {
	Other::lock();
	value = value_;
	mySem = mySem_;
	queue = new BlkQueue();
	((SemList*)Other::semaphores_list)->put(this);
	Other::unlock();
}

void KernelSem::block(Time ttw_){  //sa prezentacije predavanja
	if(Other::running != Other::idleThread){
	Other::running->state = PCB::BLOCKED;
	if(ttw_ == 0)
		ttw_ = -1;
	queue->put((PCB*)Other::running, ttw_);
	}
}

void KernelSem::unblock(){ // sa prezentacije predavanja
		PCB* p = queue->get();
		p->state = PCB::READY;
		Scheduler::put(p);
}

int KernelSem::wait(Time maxTimeToWait){
	Other::lock();
	if(maxTimeToWait < 0)
		maxTimeToWait = 0;
	int ind = 0;
	if(--value<0){
		ind = 1;
		block(maxTimeToWait);
	}

	if(ind == 1){
		Other::unlock();
		dispatch();
	}

	else{
		Other::running->blkFlag = 1;
		Other::unlock();
	}

	if(Other::running->blkFlag == 0)
		value++;

	return Other::running->blkFlag;
}

int KernelSem::signal(int n){
	Other::lock();
	if(n == 0){
		if(value++<0) unblock();
		Other::unlock();
		return 0;
	}
	else if(n > 0){
		int t = 0;
		int p = n;
		if (n > queue->threadnum)
			n = queue->threadnum;
		while(n != 0 ){
			unblock();
			n--;
			t++;
		}
		value += p;
		Other::unlock();
		return t;
	}
		Other::unlock();
		return n;
}

KernelSem::~KernelSem() {
	Other::lock();
	((SemList*)Other::semaphores_list)->remove(this);
	Other::unlock();
}

