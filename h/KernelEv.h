/*
 * KernelEv.h
 *
 *  Created on: Aug 9, 2019
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "PCB.h"
#include "Event.h"

class Event;

class KernelEv {
public:
	friend class Event;
	void wait();
	void signal();
	KernelEv(IVTNo ivtNo);
	~KernelEv();
private:
	IVTNo entrynum;
	int value;
	PCB* blocked;
	PCB* mythrd;
};

#endif /* KERNELEV_H_ */
