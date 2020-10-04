/*
 * ThrdLst.h
 *
 *  Created on: Jul 24, 2019
 *      Author: OS1
 */
#include "PCB.h"

#ifndef THRDLST_H_
#define THRDLST_H_

class ThrdLst {
public:
	friend class PCB;
	friend class Thread;
	struct Elem{
		Thread* thr;
		Elem* next;
		Elem(Thread* thr_):thr(thr_), next(0){}
	};

	Elem *headthr , *tailthr;
	void put(Thread* thr);
	ThrdLst();
	void listDel();
	~ThrdLst();
};

#endif /* THRDLST_H_ */
