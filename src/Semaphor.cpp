/*
 * Semaphor.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: OS1
 */

#include "Semaphor.h"
#include "KernSem.h"

Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init, this);
}

int Semaphore::wait(Time maxTimeToWait){
	int ret = myImpl->wait(maxTimeToWait);
	return ret;
}

int Semaphore::signal(int n){
	int ret = myImpl->signal(n);
	return ret;
}

int Semaphore::val() const {
	return this->myImpl->value;
}

Semaphore::~Semaphore() {
	delete myImpl;
	myImpl = 0;
}

