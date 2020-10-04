/*
 * SemList.h
 *
 *  Created on: Aug 6, 2019
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_
#include"KernSem.h"

class SemList {
public:
	struct Elem{
		KernelSem* semaphore;
		Elem* next;
		Elem(KernelSem* semaphore_):semaphore(semaphore_), next(0){}
		~Elem(){
			semaphore = 0;
			next = 0;
		}
	};
	Elem *headsem, *tailsem;
	int semnum;
	void semListDel();
	void remove(KernelSem* semaphore_);
	void put(KernelSem* semaphore_);
	static void semListDecrement();
	SemList();
	virtual ~SemList();
};

#endif /* SEMLIST_H_ */
