/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <dos.h>
#include "Other.h"
#include "KernelEv.h"

volatile IVTEntry* IVTEntry:: table[num]= {0};

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt newRout) {
	this->ivtNo = ivtNo;
	this->oldRoutine = 0;
	this->myEvent = 0;
	Other::lock();
#ifndef BCC_BLOCK_IGNORE
	this->oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRout);
#endif
	Other::unlock();
	table[ivtNo] = this;
}

IVTEntry::~IVTEntry() {
	Other::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldRoutine);
#endif
	Other::unlock();
	delete myEvent;
	myEvent = 0;
	oldRoutine = 0;
}

void IVTEntry::signal(){
	this->myEvent->signal();
}

void IVTEntry::callOld(){
	this->oldRoutine();
}
