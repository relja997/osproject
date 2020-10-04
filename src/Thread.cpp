/*
 * Thread.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "Other.h"
#include<iostream.h>


class PCB;
class Other;


Thread::Thread(StackSize stackSize, Time timeSlice) {
	myPCB = new PCB(stackSize, timeSlice, this);
}

void Thread::start() {
	if (this->myPCB != 0 && this->myPCB->state == PCB::CREATED) {
		Other::lock();
		this->myPCB->load_context();
		Other::unlock();
	}
}


void Thread::waitToComplete() {
	Other::lock();
	if (this->myPCB == 0 || this->myPCB->state == PCB::FINISHED
			|| this->myPCB == (PCB*) Other::running) {
		Other::unlock();
		return;
	}
	Other::running->state = PCB::BLOCKED;
	this->myPCB->wtclist->put((PCB*) Other::running);
	Other::unlock();
	PCB::dispatch();
}

int Thread::getId(){
	return this->myPCB->ID_;
}

Thread* Thread::getThreadById(ID id){
	ThrdLst::Elem *tek = PCB::thread_list->headthr;
	while(tek && tek->thr->myPCB->ID_ != id)
		tek = tek->next;
	if(tek)
		return tek->thr;
	else
		return 0;
}

ID Thread::getRunningId(){
	return Other::running->ID_;
}

void dispatch() {
	Other::running->dispatch();
}

Thread::~Thread() {
	delete myPCB;
	myPCB = 0;
}

