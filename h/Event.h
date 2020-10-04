/*
 * Event.h
 *
 *  Created on: Aug 9, 2019
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "IVTEntry.h"

typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();
protected:
	friend class KernelEv;
	void signal();
private:
	KernelEv* myImpl;
};

#endif /* EVENT_H_ */
