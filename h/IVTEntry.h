/*
 * IVTEntry.h
 *
 *  Created on: Aug 9, 2019
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include<iostream.h>

typedef unsigned char IVTNo;

#define PREPAREENTRY(numEntry, callOldF)\
	void interrupt inter##numEntry(...);\
	IVTEntry newEntry##numEntry(numEntry, inter##numEntry);\
	void interrupt inter##numEntry(...){\
		newEntry##numEntry.signal();\
		if(callOldF != 0)\
			newEntry##numEntry.callOld();\
	}


#define num 256

typedef void interrupt (*pInterrupt) (...);

class IVTEntry {
public:
	friend class Event;
	friend class KernelEv;

	IVTEntry(IVTNo ivtNo, pInterrupt newRout);
	~IVTEntry();

	void signal();
	void callOld();

	volatile static IVTEntry* table[num];
private:

	IVTNo ivtNo;
	KernelEv* myEvent;
	pInterrupt oldRoutine;
};

#endif /* IVTENTRY_H_ */
