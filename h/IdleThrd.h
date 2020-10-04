/*
 * IdleThrd.h
 *
 *  Created on: Jul 20, 2019
 *      Author: OS1
 */

#ifndef OS1VJEZB_IDLETHRD_H_
#define OS1VJEZB_IDLETHRD_H_
#include "Thread.h"

class IdleThrd : public Thread {
public:
	friend class Other;
	virtual void run();
private:
	IdleThrd(StackSize stack_size, Time timeslice);
};

#endif /* OS1VJEZB_IDLETHRD_H_ */
