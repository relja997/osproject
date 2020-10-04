/*
 * Thread.h
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#ifndef OS1VJEZB_THREAD_H_
#define OS1VJEZB_THREAD_H_
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; //time, x 55ms
const Time defaultTimeSlice = 2; //default = 2*55ms
typedef int ID;

class PCB;

class Thread {
public:
	friend class PCB;
	friend class Other;

	void start();
	void waitToComplete();
	virtual ~Thread();

	int getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);

protected:
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {};
private:
	PCB* myPCB;
};

void dispatch();

#endif /* OS1VJEZB_THREAD_H_ */
