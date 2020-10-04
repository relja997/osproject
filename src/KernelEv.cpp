/*
 * KernelEv.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: OS1
 */

#include "KernelEv.h"
#include "Other.h"
#include "Schedule.h"
#include "IVTEntry.h"

KernelEv::KernelEv(IVTNo ivtNo) {
	this->entrynum = ivtNo;
	this->value = 0;
	this->mythrd = (PCB*)Other::running;
	this->blocked = 0;
	IVTEntry::table[ivtNo]->myEvent = this;
}

void KernelEv::wait(){
	if((PCB*)Other::running == this->mythrd){
		Other::lock();
		if(value == 0){
			mythrd->state = PCB::BLOCKED;
			blocked = mythrd;
			dispatch();
		}
		else
			value = 0;

		Other::unlock();
		}
	else
		Other::unlock();
		return;
}

void KernelEv::signal(){
	Other::lock();
	if(!blocked)
		value = 1;
	else{
		mythrd->state = PCB::READY;
		blocked = 0;
		Scheduler::put(mythrd);
		dispatch();
	}
	Other::unlock();
}


KernelEv::~KernelEv() {
	if(this->blocked){
		blocked->state = PCB::READY;
		Scheduler::put(blocked);
	}
	delete blocked;
	delete mythrd;
	this->blocked = 0;
	this->mythrd = 0;
}

