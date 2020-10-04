/*
 * KernSem.h
 *
 *  Created on: Jul 26, 2019
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_
#include "BlkQueue.h"
#include "Semaphor.h"

class KernelSem {
public:
	friend class Semaphore;
	friend class SemList;
	friend class PCB;
	KernelSem(int value_, Semaphore* sem);
	virtual ~KernelSem();
	int wait(Time maxTimeToWait);
	int signal(int n = 0);
	void block(Time ttw_);
	void unblock();
private:
	int value;
	Semaphore* mySem;
	BlkQueue* queue;
};

#endif /* KERNSEM_H_ */
