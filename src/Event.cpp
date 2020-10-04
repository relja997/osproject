/*
 * Event.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo) {
	this->myImpl = new KernelEv(ivtNo);

}

void Event::wait(){
	this->myImpl->wait();
}

void Event::signal(){
	this->myImpl->signal();
}

Event::~Event() {
	this->myImpl = 0;
	delete this->myImpl;
}

